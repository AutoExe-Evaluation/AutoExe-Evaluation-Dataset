/* FILE: curl_osslq.c */
/*...*/
struct cf_osslq_ctx {
  /*...*/
  struct cf_osslq_h3conn h3;
  /*...*/

};

/*...*/
/**
 * All about the H3 internals of a stream
 */
struct h3_stream_ctx {
  struct cf_osslq_stream s;
  /*...*/

};

/*...*/
static void h3_data_done(struct Curl_cfilter *cf, struct Curl_easy *data)
{
  struct cf_osslq_ctx *ctx = cf->ctx;
  struct h3_stream_ctx *stream = H3_STREAM_CTX(ctx, data);

  (void)cf;
  if(stream) {
    /*...*/
    if(ctx->h3.conn && !stream->closed) {
      nghttp3_conn_shutdown_stream_read(ctx->h3.conn, stream->s.id); /* CRASH LOCATION */
      /*...*/

    }

    /*...*/

  }
}
