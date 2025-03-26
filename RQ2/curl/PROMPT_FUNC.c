/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/

#include "../curl_setup.h"

#include <openssl/ssl.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <nghttp3/nghttp3.h>

#include "../urldata.h"
#include "../hash.h"
#include "../sendf.h"
#include "../strdup.h"
#include "../rand.h"
#include "../multiif.h"
#include "../strcase.h"
#include "../cfilters.h"
#include "../cf-socket.h"
#include "../connect.h"
#include "../progress.h"
#include "../strerror.h"
#include "../dynbuf.h"
#include "../http1.h"
#include "../select.h"
#include "../inet_pton.h"
#include "vquic.h"
#include "vquic_int.h"
#include "vquic-tls.h"
#include "../vtls/keylog.h"
#include "../vtls/vtls.h"
#include "../vtls/openssl.h"
#include "curl_osslq.h"

#include "../warnless.h"

/* The last 3 #include files should be in this order */
#include "../curl_printf.h"
#include "../curl_memory.h"
#include "../memdebug.h"

/* A stream window is the maximum amount we need to buffer for
 * each active transfer. We use HTTP/3 flow control and only ACK
 * when we take things out of the buffer.
 * Chunk size is large enough to take a full DATA frame */
#define H3_STREAM_WINDOW_SIZE (128 * 1024)
#define H3_STREAM_CHUNK_SIZE   (16 * 1024)
/* The pool keeps spares around and half of a full stream window
 * seems good. More does not seem to improve performance.
 * The benefit of the pool is that stream buffer to not keep
 * spares. Memory consumption goes down when streams run empty,
 * have a large upload done, etc. */
#define H3_STREAM_POOL_SPARES \
          (H3_STREAM_WINDOW_SIZE / H3_STREAM_CHUNK_SIZE ) / 2
/* Receive and Send max number of chunks just follows from the
 * chunk size and window size */
#define H3_STREAM_RECV_CHUNKS \
          (H3_STREAM_WINDOW_SIZE / H3_STREAM_CHUNK_SIZE)
#define H3_STREAM_SEND_CHUNKS \
          (H3_STREAM_WINDOW_SIZE / H3_STREAM_CHUNK_SIZE)

#if defined(OPENSSL_IS_BORINGSSL) || defined(OPENSSL_IS_AWSLC)
typedef uint32_t sslerr_t;
#else
typedef unsigned long sslerr_t;
#endif


/* How to access `call_data` from a cf_osslq filter */
#undef CF_CTX_CALL_DATA
#define CF_CTX_CALL_DATA(cf)  \
  ((struct cf_osslq_ctx *)(cf)->ctx)->call_data

static CURLcode cf_progress_ingress(struct Curl_cfilter *cf,
                                    struct Curl_easy *data);

static const char *osslq_SSL_ERROR_to_str(int err)
{
  switch(err) {
  case SSL_ERROR_NONE:
    return "SSL_ERROR_NONE";
  case SSL_ERROR_SSL:
    return "SSL_ERROR_SSL";
  case SSL_ERROR_WANT_READ:
    return "SSL_ERROR_WANT_READ";
  case SSL_ERROR_WANT_WRITE:
    return "SSL_ERROR_WANT_WRITE";
  case SSL_ERROR_WANT_X509_LOOKUP:
    return "SSL_ERROR_WANT_X509_LOOKUP";
  case SSL_ERROR_SYSCALL:
    return "SSL_ERROR_SYSCALL";
  case SSL_ERROR_ZERO_RETURN:
    return "SSL_ERROR_ZERO_RETURN";
  case SSL_ERROR_WANT_CONNECT:
    return "SSL_ERROR_WANT_CONNECT";
  case SSL_ERROR_WANT_ACCEPT:
    return "SSL_ERROR_WANT_ACCEPT";
#if defined(SSL_ERROR_WANT_ASYNC)
  case SSL_ERROR_WANT_ASYNC:
    return "SSL_ERROR_WANT_ASYNC";
#endif
#if defined(SSL_ERROR_WANT_ASYNC_JOB)
  case SSL_ERROR_WANT_ASYNC_JOB:
    return "SSL_ERROR_WANT_ASYNC_JOB";
#endif
#if defined(SSL_ERROR_WANT_EARLY)
  case SSL_ERROR_WANT_EARLY:
    return "SSL_ERROR_WANT_EARLY";
#endif
  default:
    return "SSL_ERROR unknown";
  }
}

/* Return error string for last OpenSSL error */
static char *osslq_strerror(unsigned long error, char *buf, size_t size)
{
  DEBUGASSERT(size);
  *buf = '\0';

#if defined(OPENSSL_IS_BORINGSSL) || defined(OPENSSL_IS_AWSLC)
  ERR_error_string_n((uint32_t)error, buf, size);
#else
  ERR_error_string_n(error, buf, size);
#endif

  if(!*buf) {
    const char *msg = error ? "Unknown error" : "No error";
    if(strlen(msg) < size)
      strcpy(buf, msg);
  }

  return buf;
}

static CURLcode make_bio_addr(BIO_ADDR **pbio_addr,
                              const struct Curl_sockaddr_ex *addr)
{
  BIO_ADDR *ba;
  CURLcode result = CURLE_FAILED_INIT;

  ba = BIO_ADDR_new();
  if(!ba) {
    result = CURLE_OUT_OF_MEMORY;
    goto out;
  }

  switch(addr->family) {
  case AF_INET: {
    struct sockaddr_in * const sin =
      (struct sockaddr_in * const)CURL_UNCONST(&addr->curl_sa_addr);
    if(!BIO_ADDR_rawmake(ba, AF_INET, &sin->sin_addr,
                         sizeof(sin->sin_addr), sin->sin_port)) {
      goto out;
    }
    result = CURLE_OK;
    break;
  }
#ifdef USE_IPV6
  case AF_INET6: {
    struct sockaddr_in6 * const sin =
      (struct sockaddr_in6 * const)CURL_UNCONST(&addr->curl_sa_addr);
    if(!BIO_ADDR_rawmake(ba, AF_INET6, &sin->sin6_addr,
                         sizeof(sin->sin6_addr), sin->sin6_port)) {
    }
    result = CURLE_OK;
    break;
  }
#endif /* USE_IPV6 */
  default:
    /* sunsupported */
    DEBUGASSERT(0);
    break;
  }

out:
  if(result && ba) {
    BIO_ADDR_free(ba);
    ba = NULL;
  }
  *pbio_addr = ba;
  return result;
}

/* QUIC stream (not necessarily H3) */
struct cf_osslq_stream {
  curl_int64_t id;
  SSL *ssl;
  struct bufq recvbuf; /* QUIC war data recv buffer */
  BIT(recvd_eos);
  BIT(closed);
  BIT(reset);
  BIT(send_blocked);
};

static CURLcode cf_osslq_stream_open(struct cf_osslq_stream *s,
                                     SSL *conn,
                                     uint64_t flags,
                                     struct bufc_pool *bufcp,
                                     void *user_data)
{
  DEBUGASSERT(!s->ssl);
  Curl_bufq_initp(&s->recvbuf, bufcp, 1, BUFQ_OPT_NONE);
  s->ssl = SSL_new_stream(conn, flags);
  if(!s->ssl) {
    return CURLE_FAILED_INIT;
  }
  s->id = (curl_int64_t)SSL_get_stream_id(s->ssl);
  SSL_set_app_data(s->ssl, user_data);
  return CURLE_OK;
}

static void cf_osslq_stream_cleanup(struct cf_osslq_stream *s)
{
  if(s->ssl) {
    SSL_set_app_data(s->ssl, NULL);
    SSL_free(s->ssl);
  }
  Curl_bufq_free(&s->recvbuf);
  memset(s, 0, sizeof(*s));
}

static void cf_osslq_stream_close(struct cf_osslq_stream *s)
{
  if(s->ssl) {
    SSL_free(s->ssl);
    s->ssl = NULL;
  }
}

struct cf_osslq_h3conn {
  nghttp3_conn *conn;
  nghttp3_settings settings;
  struct cf_osslq_stream s_ctrl;
  struct cf_osslq_stream s_qpack_enc;
  struct cf_osslq_stream s_qpack_dec;
  struct cf_osslq_stream remote_ctrl[3]; /* uni streams opened by the peer */
  size_t remote_ctrl_n; /* number of peer streams opened */
};

static void cf_osslq_h3conn_cleanup(struct cf_osslq_h3conn *h3)
{
  size_t i;

  if(h3->conn)
    nghttp3_conn_del(h3->conn);
  cf_osslq_stream_cleanup(&h3->s_ctrl);
  cf_osslq_stream_cleanup(&h3->s_qpack_enc);
  cf_osslq_stream_cleanup(&h3->s_qpack_dec);
  for(i = 0; i < h3->remote_ctrl_n; ++i) {
    cf_osslq_stream_cleanup(&h3->remote_ctrl[i]);
  }
}

struct cf_osslq_ctx {
  struct cf_quic_ctx q;
  struct ssl_peer peer;
  struct curl_tls_ctx tls;
  struct cf_call_data call_data;
  struct cf_osslq_h3conn h3;
  struct curltime started_at;        /* time the current attempt started */
  struct curltime handshake_at;      /* time connect handshake finished */
  struct curltime first_byte_at;     /* when first byte was recvd */
  struct bufc_pool stream_bufcp;     /* chunk pool for streams */
  struct Curl_hash_offt streams;     /* hash `data->mid` to `h3_stream_ctx` */
  size_t max_stream_window;          /* max flow window for one stream */
  uint64_t max_idle_ms;              /* max idle time for QUIC connection */
  SSL_POLL_ITEM *poll_items;         /* Array for polling on writable state */
  struct Curl_easy **curl_items;     /* Array of easy objs */
  size_t items_max;                  /* max elements in poll/curl_items */
  BIT(initialized);
  BIT(got_first_byte);               /* if first byte was received */
  BIT(x509_store_setup);             /* if x509 store has been set up */
  BIT(protocol_shutdown);            /* QUIC connection is shut down */
  BIT(need_recv);                    /* QUIC connection needs to receive */
  BIT(need_send);                    /* QUIC connection needs to send */
};

static void h3_stream_hash_free(curl_off_t id, void *stream);

static void cf_osslq_ctx_init(struct cf_osslq_ctx *ctx)
{
  DEBUGASSERT(!ctx->initialized);
  Curl_bufcp_init(&ctx->stream_bufcp, H3_STREAM_CHUNK_SIZE,
                  H3_STREAM_POOL_SPARES);
  Curl_hash_offt_init(&ctx->streams, 63, h3_stream_hash_free);
  ctx->poll_items = NULL;
  ctx->curl_items = NULL;
  ctx->items_max = 0;
  ctx->initialized = TRUE;
}

static void cf_osslq_ctx_free(struct cf_osslq_ctx *ctx)
{
  if(ctx && ctx->initialized) {
    Curl_bufcp_free(&ctx->stream_bufcp);
    Curl_hash_offt_destroy(&ctx->streams);
    Curl_ssl_peer_cleanup(&ctx->peer);
    free(ctx->poll_items);
    free(ctx->curl_items);
  }
  free(ctx);
}

static void cf_osslq_ctx_close(struct cf_osslq_ctx *ctx)
{
  struct cf_call_data save = ctx->call_data;

  cf_osslq_h3conn_cleanup(&ctx->h3);
  Curl_vquic_tls_cleanup(&ctx->tls);
  vquic_ctx_free(&ctx->q);
  ctx->call_data = save;
}

static CURLcode cf_osslq_shutdown(struct Curl_cfilter *cf,
                                  struct Curl_easy *data, bool *done)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  struct cf_call_data save;
  CURLcode result = CURLE_OK;
  int rc;

  CF_DATA_SAVE(save, cf, data);

  if(cf->shutdown || ctx->protocol_shutdown) {
    *done = TRUE;
    return CURLE_OK;
  }

  CF_DATA_SAVE(save, cf, data);
  *done = FALSE;
  ctx->need_send = FALSE;
  ctx->need_recv = FALSE;

  rc = SSL_shutdown_ex(ctx->tls.ossl.ssl,
                       SSL_SHUTDOWN_FLAG_NO_BLOCK, NULL, 0);
  if(rc == 0) {  /* ongoing */
    CURL_TRC_CF(data, cf, "shutdown ongoing");
    ctx->need_recv = TRUE;
    goto out;
  }
  else if(rc == 1) {  /* done */
    CURL_TRC_CF(data, cf, "shutdown finished");
    *done = TRUE;
    goto out;
  }
  else {
    long sslerr;
    char err_buffer[256];
    int err = SSL_get_error(ctx->tls.ossl.ssl, rc);

    switch(err) {
    case SSL_ERROR_NONE:
    case SSL_ERROR_ZERO_RETURN:
      CURL_TRC_CF(data, cf, "shutdown not received, but closed");
      *done = TRUE;
      goto out;
    case SSL_ERROR_WANT_READ:
      /* SSL has send its notify and now wants to read the reply
       * from the server. We are not really interested in that. */
      CURL_TRC_CF(data, cf, "shutdown sent, want receive");
      ctx->need_recv = TRUE;
      goto out;
    case SSL_ERROR_WANT_WRITE:
      CURL_TRC_CF(data, cf, "shutdown send blocked");
      ctx->need_send = TRUE;
      goto out;
    default:
      /* We give up on this. */
      sslerr = ERR_get_error();
      CURL_TRC_CF(data, cf, "shutdown, ignore recv error: '%s', errno %d",
                  (sslerr ?
                   osslq_strerror(sslerr, err_buffer, sizeof(err_buffer)) :
                   osslq_SSL_ERROR_to_str(err)),
                  SOCKERRNO);
      *done = TRUE;
      result = CURLE_OK;
      goto out;
    }
  }
out:
  CF_DATA_RESTORE(cf, save);
  return result;
}

static void cf_osslq_close(struct Curl_cfilter *cf, struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  struct cf_call_data save;

  CF_DATA_SAVE(save, cf, data);
  if(ctx && ctx->tls.ossl.ssl) {
    CURL_TRC_CF(data, cf, "cf_osslq_close()");
    if(!cf->shutdown && !ctx->protocol_shutdown) {
      /* last best effort, which OpenSSL calls a "rapid" shutdown. */
      SSL_shutdown_ex(ctx->tls.ossl.ssl,
                      (SSL_SHUTDOWN_FLAG_NO_BLOCK | SSL_SHUTDOWN_FLAG_RAPID),
                      NULL, 0);
    }
    cf_osslq_ctx_close(ctx);
  }

  cf->connected = FALSE;
  CF_DATA_RESTORE(cf, save);
}

static void cf_osslq_destroy(struct Curl_cfilter *cf, struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  struct cf_call_data save;

  CF_DATA_SAVE(save, cf, data);
  CURL_TRC_CF(data, cf, "destroy");
  if(ctx) {
    CURL_TRC_CF(data, cf, "cf_osslq_destroy()");
    if(ctx->tls.ossl.ssl)
      cf_osslq_ctx_close(ctx);
    cf_osslq_ctx_free(ctx);
  }
  cf->ctx = NULL;
  /* No CF_DATA_RESTORE(cf, save) possible */
  (void)save;
}

static CURLcode cf_osslq_h3conn_add_stream(struct cf_osslq_h3conn *h3,
                                           SSL *stream_ssl,
                                           struct Curl_cfilter *cf,
                                           struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  curl_int64_t stream_id = (curl_int64_t)SSL_get_stream_id(stream_ssl);

  if(h3->remote_ctrl_n >= CURL_ARRAYSIZE(h3->remote_ctrl)) {
    /* rejected, we are full */
    CURL_TRC_CF(data, cf, "[%" FMT_PRId64 "] rejecting remote stream",
                stream_id);
    SSL_free(stream_ssl);
    return CURLE_FAILED_INIT;
  }
  switch(SSL_get_stream_type(stream_ssl)) {
    case SSL_STREAM_TYPE_READ: {
      struct cf_osslq_stream *nstream = &h3->remote_ctrl[h3->remote_ctrl_n++];
      nstream->id = stream_id;
      nstream->ssl = stream_ssl;
      Curl_bufq_initp(&nstream->recvbuf, &ctx->stream_bufcp, 1, BUFQ_OPT_NONE);
      CURL_TRC_CF(data, cf, "[%" FMT_PRId64 "] accepted remote uni stream",
                  stream_id);
      break;
    }
    default:
      CURL_TRC_CF(data, cf, "[%" FMT_PRId64 "] reject remote non-uni-read"
                  " stream", stream_id);
      SSL_free(stream_ssl);
      return CURLE_FAILED_INIT;
  }
  return CURLE_OK;

}

static CURLcode cf_osslq_ssl_err(struct Curl_cfilter *cf,
                                 struct Curl_easy *data,
                                 int detail, CURLcode def_result)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  CURLcode result = def_result;
  sslerr_t errdetail;
  char ebuf[256] = "unknown";
  const char *err_descr = ebuf;
  long lerr;
  int lib;
  int reason;
  struct ssl_config_data *ssl_config = Curl_ssl_cf_get_config(cf, data);

  errdetail = ERR_get_error();
  lib = ERR_GET_LIB(errdetail);
  reason = ERR_GET_REASON(errdetail);

  if((lib == ERR_LIB_SSL) &&
     ((reason == SSL_R_CERTIFICATE_VERIFY_FAILED) ||
      (reason == SSL_R_SSLV3_ALERT_CERTIFICATE_EXPIRED))) {
    result = CURLE_PEER_FAILED_VERIFICATION;

    lerr = SSL_get_verify_result(ctx->tls.ossl.ssl);
    if(lerr != X509_V_OK) {
      ssl_config->certverifyresult = lerr;
      msnprintf(ebuf, sizeof(ebuf),
                "SSL certificate problem: %s",
                X509_verify_cert_error_string(lerr));
    }
    else
      err_descr = "SSL certificate verification failed";
  }
#if defined(SSL_R_TLSV13_ALERT_CERTIFICATE_REQUIRED)
  /* SSL_R_TLSV13_ALERT_CERTIFICATE_REQUIRED is only available on
     OpenSSL version above v1.1.1, not LibreSSL, BoringSSL, or AWS-LC */
  else if((lib == ERR_LIB_SSL) &&
          (reason == SSL_R_TLSV13_ALERT_CERTIFICATE_REQUIRED)) {
    /* If client certificate is required, communicate the
       error to client */
    result = CURLE_SSL_CLIENTCERT;
    osslq_strerror(errdetail, ebuf, sizeof(ebuf));
  }
#endif
  else if((lib == ERR_LIB_SSL) && (reason == SSL_R_PROTOCOL_IS_SHUTDOWN)) {
    ctx->protocol_shutdown = TRUE;
    err_descr = "QUIC connection has been shut down";
    result = def_result;
  }
  else {
    result = def_result;
    osslq_strerror(errdetail, ebuf, sizeof(ebuf));
  }

  /* detail is already set to the SSL error above */

  /* If we e.g. use SSLv2 request-method and the server does not like us
   * (RST connection, etc.), OpenSSL gives no explanation whatsoever and
   * the SO_ERROR is also lost.
   */
  if(CURLE_SSL_CONNECT_ERROR == result && errdetail == 0) {
    char extramsg[80]="";
    int sockerr = SOCKERRNO;
    struct ip_quadruple ip;

    Curl_cf_socket_peek(cf->next, data, NULL, NULL, &ip);
    if(sockerr && detail == SSL_ERROR_SYSCALL)
      Curl_strerror(sockerr, extramsg, sizeof(extramsg));
    failf(data, "QUIC connect: %s in connection to %s:%d (%s)",
          extramsg[0] ? extramsg : osslq_SSL_ERROR_to_str(detail),
          ctx->peer.dispname, ip.remote_port, ip.remote_ip);
  }
  else {
    /* Could be a CERT problem */
    failf(data, "%s", err_descr);
  }
  return result;
}

static CURLcode cf_osslq_verify_peer(struct Curl_cfilter *cf,
                                  struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;

  cf->conn->bits.multiplex = TRUE; /* at least potentially multiplexed */

  return Curl_vquic_tls_verify_peer(&ctx->tls, cf, data, &ctx->peer);
}

/**
 * All about the H3 internals of a stream
 */
struct h3_stream_ctx {
  struct cf_osslq_stream s;
  struct bufq sendbuf;   /* h3 request body */
  struct bufq recvbuf;   /* h3 response body */
  struct h1_req_parser h1; /* h1 request parsing */
  size_t sendbuf_len_in_flight; /* sendbuf amount "in flight" */
  size_t recv_buf_nonflow; /* buffered bytes, not counting for flow control */
  curl_uint64_t error3; /* HTTP/3 stream error code */
  curl_off_t upload_left; /* number of request bytes left to upload */
  curl_off_t download_recvd; /* number of response DATA bytes received */
  int status_code; /* HTTP status code */
  bool resp_hds_complete; /* we have a complete, final response */
  bool closed; /* TRUE on stream close */
  bool reset;  /* TRUE on stream reset */
  bool send_closed; /* stream is local closed */
  BIT(quic_flow_blocked); /* stream is blocked by QUIC flow control */
};

#define H3_STREAM_CTX(ctx,data)   ((struct h3_stream_ctx *)(\
            data? Curl_hash_offt_get(&(ctx)->streams, (data)->mid) : NULL))

static void h3_stream_ctx_free(struct h3_stream_ctx *stream)
{
  cf_osslq_stream_cleanup(&stream->s);
  Curl_bufq_free(&stream->sendbuf);
  Curl_bufq_free(&stream->recvbuf);
  Curl_h1_req_parse_free(&stream->h1);
  free(stream);
}

static void h3_stream_hash_free(curl_off_t id, void *stream)
{
  (void)id;
  DEBUGASSERT(stream);
  h3_stream_ctx_free((struct h3_stream_ctx *)stream);
}

static CURLcode h3_data_setup(struct Curl_cfilter *cf,
                              struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  struct h3_stream_ctx *stream = H3_STREAM_CTX(ctx, data);

  if(!data)
    return CURLE_FAILED_INIT;

  if(stream)
    return CURLE_OK;

  stream = calloc(1, sizeof(*stream));
  if(!stream)
    return CURLE_OUT_OF_MEMORY;

  stream->s.id = -1;
  /* on send, we control how much we put into the buffer */
  Curl_bufq_initp(&stream->sendbuf, &ctx->stream_bufcp,
                  H3_STREAM_SEND_CHUNKS, BUFQ_OPT_NONE);
  stream->sendbuf_len_in_flight = 0;
  /* on recv, we need a flexible buffer limit since we also write
   * headers to it that are not counted against the nghttp3 flow limits. */
  Curl_bufq_initp(&stream->recvbuf, &ctx->stream_bufcp,
                  H3_STREAM_RECV_CHUNKS, BUFQ_OPT_SOFT_LIMIT);
  stream->recv_buf_nonflow = 0;
  Curl_h1_req_parse_init(&stream->h1, H1_PARSE_DEFAULT_MAX_LINE_LEN);

  if(!Curl_hash_offt_set(&ctx->streams, data->mid, stream)) {
    h3_stream_ctx_free(stream);
    return CURLE_OUT_OF_MEMORY;
  }

  return CURLE_OK;
}

static void h3_data_done(struct Curl_cfilter *cf, struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  struct h3_stream_ctx *stream = H3_STREAM_CTX(ctx, data);

  (void)cf;
  if(stream) {
    CURL_TRC_CF(data, cf, "[%"FMT_PRId64"] easy handle is done",
                stream->s.id);
    if(ctx->h3.conn && !stream->closed) {
      nghttp3_conn_shutdown_stream_read(ctx->h3.conn, stream->s.id);
      nghttp3_conn_close_stream(ctx->h3.conn, stream->s.id,
                                NGHTTP3_H3_REQUEST_CANCELLED);
      nghttp3_conn_set_stream_user_data(ctx->h3.conn, stream->s.id, NULL);
      stream->closed = TRUE;
    }

    Curl_hash_offt_remove(&ctx->streams, data->mid);
  }
}
