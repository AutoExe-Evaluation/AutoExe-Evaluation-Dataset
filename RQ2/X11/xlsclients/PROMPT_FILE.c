/* Copyright (C) 2001-2004 Bart Massey and Jamey Sharp.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * Except as contained in this notice, the names of the authors or their
 * institutions shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization from the authors.
 */

/* Stuff that reads stuff from the server. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#if USE_POLL
#include <poll.h>
#endif
#ifndef _WIN32
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#endif

#ifdef _WIN32
#include "xcb_windefs.h"
#endif /* _WIN32 */

#include "xcb.h"
#include "xcbext.h"
#include "xcbint.h"

#define XCB_ERROR 0
#define XCB_REPLY 1
#define XCB_XGE_EVENT 35

struct event_list {
    xcb_generic_event_t *event;
    struct event_list *next;
};

struct xcb_special_event {

    struct xcb_special_event *next;

    /* Match XGE events for the specific extension and event ID (the
     * first 32 bit word after evtype)
     */
    uint8_t     extension;
    uint32_t    eid;
    uint32_t    *stamp;

    struct event_list   *events;
    struct event_list   **events_tail;

    pthread_cond_t special_event_cond;
};

struct reply_list {
    void *reply;
    struct reply_list *next;
};

typedef struct pending_reply {
    uint64_t first_request;
    uint64_t last_request;
    enum workarounds workaround;
    int flags;
    struct pending_reply *next;
} pending_reply;

typedef struct reader_list {
    uint64_t request;
    pthread_cond_t *data;
    struct reader_list *next;
} reader_list;

typedef struct special_list {
    xcb_special_event_t *se;
    struct special_list *next;
} special_list;

static void remove_finished_readers(reader_list **prev_reader, uint64_t completed)
{
    while(*prev_reader && XCB_SEQUENCE_COMPARE((*prev_reader)->request, <=, completed))
    {
        /* If you don't have what you're looking for now, you never
         * will. Wake up and leave me alone. */
        pthread_cond_signal((*prev_reader)->data);
        *prev_reader = (*prev_reader)->next;
    }
}

#if HAVE_SENDMSG
static int read_fds(xcb_connection_t *c, int *fds, int nfd)
{
    int *ifds = &c->in.in_fd.fd[c->in.in_fd.ifd];
    int infd = c->in.in_fd.nfd - c->in.in_fd.ifd;

    if (nfd > infd)
        return 0;
    memcpy(fds, ifds, nfd * sizeof (int));
    c->in.in_fd.ifd += nfd;
    return 1;
}
#endif

typedef struct xcb_ge_special_event_t {
    uint8_t  response_type; /**<  */
    uint8_t  extension; /**<  */
    uint16_t sequence; /**<  */
    uint32_t length; /**<  */
    uint16_t evtype; /**<  */
    uint8_t  pad0[2]; /**< */
    uint32_t eid; /**< */
    uint8_t  pad1[16]; /**<  */
} xcb_ge_special_event_t;

static int event_special(xcb_connection_t *c,
                         struct event_list *event)
{
    struct xcb_special_event *special_event;
    struct xcb_ge_special_event_t *ges = (void *) event->event;

    /* Special events are always XGE events */
    if ((ges->response_type & 0x7f) != XCB_XGE_EVENT)
        return 0;

    for (special_event = c->in.special_events;
         special_event;
         special_event = special_event->next)
    {
        if (ges->extension == special_event->extension &&
            ges->eid == special_event->eid)
        {
            *special_event->events_tail = event;
            special_event->events_tail = &event->next;
            if (special_event->stamp)
                ++(*special_event->stamp);
            pthread_cond_signal(&special_event->special_event_cond);
            return 1;
        }
    }

    return 0;
}

static int read_packet(xcb_connection_t *c)
{
    xcb_generic_reply_t genrep;
    uint64_t length = 32;
    uint64_t eventlength = 0; /* length after first 32 bytes for GenericEvents */
    int nfd = 0;         /* Number of file descriptors attached to the reply */
    uint64_t bufsize;
    void *buf;
    pending_reply *pend = 0;
    struct event_list *event;

    /* Wait for there to be enough data for us to read a whole packet */
    if(c->in.queue_len < length)
        return 0;

    /* Get the response type, length, and sequence number. */
    memcpy(&genrep, c->in.queue, sizeof(genrep));

    /* Compute 32-bit sequence number of this packet. */
    if((genrep.response_type & 0x7f) != XCB_KEYMAP_NOTIFY)
    {
        uint64_t lastread = c->in.request_read;
        c->in.request_read = (lastread & UINT64_C(0xffffffffffff0000)) | genrep.sequence;
        if(XCB_SEQUENCE_COMPARE(c->in.request_read, <, lastread))
            c->in.request_read += 0x10000;
        if(XCB_SEQUENCE_COMPARE(c->in.request_read, >, c->in.request_expected))
            c->in.request_expected = c->in.request_read;

        if(c->in.request_read != lastread)
        {
            if(c->in.current_reply)
            {
                _xcb_map_put(c->in.replies, lastread, c->in.current_reply);
                c->in.current_reply = 0;
                c->in.current_reply_tail = &c->in.current_reply;
            }
            c->in.request_completed = c->in.request_read - 1;
        }

        while(c->in.pending_replies &&
              c->in.pending_replies->workaround != WORKAROUND_EXTERNAL_SOCKET_OWNER &&
              XCB_SEQUENCE_COMPARE (c->in.pending_replies->last_request, <=, c->in.request_completed))
        {
            pending_reply *oldpend = c->in.pending_replies;
            c->in.pending_replies = oldpend->next;
            if(!oldpend->next)
                c->in.pending_replies_tail = &c->in.pending_replies;
            free(oldpend);
        }

        if(genrep.response_type == XCB_ERROR)
            c->in.request_completed = c->in.request_read;

        remove_finished_readers(&c->in.readers, c->in.request_completed);
    }

    if(genrep.response_type == XCB_ERROR || genrep.response_type == XCB_REPLY)
    {
        pend = c->in.pending_replies;
        if(pend &&
           !(XCB_SEQUENCE_COMPARE(pend->first_request, <=, c->in.request_read) &&
             (pend->workaround == WORKAROUND_EXTERNAL_SOCKET_OWNER ||
              XCB_SEQUENCE_COMPARE(c->in.request_read, <=, pend->last_request))))
            pend = 0;
    }

    /* For reply packets, check that the entire packet is available. */
    if(genrep.response_type == XCB_REPLY)
    {
        if(pend && pend->workaround == WORKAROUND_GLX_GET_FB_CONFIGS_BUG)
        {
            uint32_t *p = (uint32_t *) c->in.queue;
            uint64_t new_length = ((uint64_t)p[2]) * ((uint64_t)p[3]);
            if(new_length >= (UINT32_MAX / UINT32_C(16)))
            {
                _xcb_conn_shutdown(c, XCB_CONN_CLOSED_MEM_INSUFFICIENT);
                return 0;
            }
            genrep.length = (uint32_t)(new_length * UINT64_C(2));
        }
        length += genrep.length * UINT64_C(4);

        /* XXX a bit of a hack -- we "know" that all FD replys place
         * the number of fds in the pad0 byte */
        if (pend && pend->flags & XCB_REQUEST_REPLY_FDS)
            nfd = genrep.pad0;
    }

    /* XGE events may have sizes > 32 */
    if ((genrep.response_type & 0x7f) == XCB_XGE_EVENT)
        eventlength = genrep.length * UINT64_C(4);

    bufsize = length + eventlength + nfd * sizeof(int)  +
        (genrep.response_type == XCB_REPLY ? 0 : sizeof(uint32_t));
    if (bufsize < INT32_MAX)
        buf = malloc((size_t) bufsize);
    else
        buf = NULL;
    if(!buf)
    {
        _xcb_conn_shutdown(c, XCB_CONN_CLOSED_MEM_INSUFFICIENT);
        return 0;
    }

    if(_xcb_in_read_block(c, buf, length) <= 0)
    {
        free(buf);
        return 0;
    }

    /* pull in XGE event data if available, append after event struct */
    if (eventlength)
    {
        if(_xcb_in_read_block(c, &((xcb_generic_event_t*)buf)[1], eventlength) <= 0)
        {
            free(buf);
            return 0;
        }
    }

#if HAVE_SENDMSG
    if (nfd)
    {
        if (!read_fds(c, (int *) &((char *) buf)[length], nfd))
        {
            free(buf);
            return 0;
        }
    }
#endif

    if(pend && (pend->flags & XCB_REQUEST_DISCARD_REPLY))
    {
        free(buf);
        return 1;
    }

    if(genrep.response_type != XCB_REPLY)
        ((xcb_generic_event_t *) buf)->full_sequence = c->in.request_read;

    /* reply, or checked error */
    if( genrep.response_type == XCB_REPLY ||
       (genrep.response_type == XCB_ERROR && pend && (pend->flags & XCB_REQUEST_CHECKED)))
    {
        struct reply_list *cur = malloc(sizeof(struct reply_list));
        if(!cur)
        {
            _xcb_conn_shutdown(c, XCB_CONN_CLOSED_MEM_INSUFFICIENT);
            free(buf);
            return 0;
        }
        cur->reply = buf;
        cur->next = 0;
        *c->in.current_reply_tail = cur;
        c->in.current_reply_tail = &cur->next;
        if(c->in.readers && c->in.readers->request == c->in.request_read)
            pthread_cond_signal(c->in.readers->data);
        return 1;
    }

    /* event, or unchecked error */
    event = malloc(sizeof(struct event_list));
    if(!event)
    {
        _xcb_conn_shutdown(c, XCB_CONN_CLOSED_MEM_INSUFFICIENT);
        free(buf);
        return 0;
    }
    event->event = buf;
    event->next = 0;

    if (!event_special(c, event)) {
        *c->in.events_tail = event;
        c->in.events_tail = &event->next;
        pthread_cond_signal(&c->in.event_cond);
    }
    return 1; /* I have something for you... */
}

static xcb_generic_event_t *get_event(xcb_connection_t *c)
{
    struct event_list *cur = c->in.events;
    xcb_generic_event_t *ret;
    if(!c->in.events)
        return 0;
    ret = cur->event;
    c->in.events = cur->next;
    if(!cur->next)
        c->in.events_tail = &c->in.events;
    free(cur);
    return ret;
}

static void free_reply_list(struct reply_list *head)
{
    while(head)
    {
        struct reply_list *cur = head;
        head = cur->next;
        free(cur->reply);
        free(cur);
    }
}

static int read_block(const int fd, void *buf, const intptr_t len)
{
    int done = 0;
    while(done < len)
    {
        int ret = recv(fd, ((char *) buf) + done, len - done, 0);
        if(ret > 0)
            done += ret;
#ifndef _WIN32
        if(ret < 0 && errno == EAGAIN)
#else
        if(ret == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK)
#endif /* !_Win32 */
        {
#if USE_POLL
            struct pollfd pfd;
            pfd.fd = fd;
            pfd.events = POLLIN;
            pfd.revents = 0;
            do {
                ret = poll(&pfd, 1, -1);
            } while (ret == -1 && errno == EINTR);
#else
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(fd, &fds);

            /* Initializing errno here makes sure that for Win32 this loop will execute only once */
            errno = 0;
            do {
                ret = select(fd + 1, &fds, 0, 0, 0);
            } while (ret == -1 && errno == EINTR);
#endif /* USE_POLL */
        }
        if(ret <= 0)
            return ret;
    }
    return len;
}

static int poll_for_reply(xcb_connection_t *c, uint64_t request, void **reply, xcb_generic_error_t **error)
{
    struct reply_list *head;

    /* If an error occurred when issuing the request, fail immediately. */
    if(!request)
        head = 0;
    /* We've read requests past the one we want, so if it has replies we have
     * them all and they're in the replies map. */
    else if(XCB_SEQUENCE_COMPARE(request, <, c->in.request_read))
    {
        head = _xcb_map_remove(c->in.replies, request);
        if(head && head->next)
            _xcb_map_put(c->in.replies, request, head->next);
    }
    /* We're currently processing the responses to the request we want, and we
     * have a reply ready to return. So just return it without blocking. */
    else if(request == c->in.request_read && c->in.current_reply)
    {
        head = c->in.current_reply;
        c->in.current_reply = head->next;
        if(!head->next)
            c->in.current_reply_tail = &c->in.current_reply;
    }
    /* We know this request can't have any more replies, and we've already
     * established it doesn't have a reply now. Don't bother blocking. */
    else if(request == c->in.request_completed)
        head = 0;
    /* We may have more replies on the way for this request: block until we're
     * sure. */
    else
        return 0;

    if(error)
        *error = 0;
    *reply = 0;

    if(head)
    {
        if(((xcb_generic_reply_t *) head->reply)->response_type == XCB_ERROR)
        {
            if(error)
                *error = head->reply;
            else
                free(head->reply);
        }
        else
            *reply = head->reply;

        free(head);
    }

    return 1;
}

static void insert_reader(reader_list **prev_reader, reader_list *reader, uint64_t request, pthread_cond_t *cond)
{
    while(*prev_reader && XCB_SEQUENCE_COMPARE((*prev_reader)->request, <=, request))
        prev_reader = &(*prev_reader)->next;
    reader->request = request;
    reader->data = cond;
    reader->next = *prev_reader;
    *prev_reader = reader;
}

static void remove_reader(reader_list **prev_reader, reader_list *reader)
{
    while(*prev_reader && XCB_SEQUENCE_COMPARE((*prev_reader)->request, <=, reader->request))
        if(*prev_reader == reader)
        {
            *prev_reader = (*prev_reader)->next;
            break;
        }
}

static void insert_special(special_list **prev_special, special_list *special, xcb_special_event_t *se)
{
    special->se = se;
    special->next = *prev_special;
    *prev_special = special;
}

static void remove_special(special_list **prev_special, special_list *special)
{
    while(*prev_special)
    {
        if(*prev_special == special)
        {
            *prev_special = (*prev_special)->next;
            break;
        }
        prev_special = &(*prev_special)->next;
    }
}

static void *wait_for_reply(xcb_connection_t *c, uint64_t request, xcb_generic_error_t **e)
{
    void *ret = 0;

    /* If this request has not been written yet, write it. */
    if(c->out.return_socket || _xcb_out_flush_to(c, request))
    {
        pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
        reader_list reader;

        insert_reader(&c->in.readers, &reader, request, &cond);

        while(!poll_for_reply(c, request, &ret, e))
            if(!_xcb_conn_wait(c, &cond, 0, 0))
                break;

        remove_reader(&c->in.readers, &reader);
        pthread_cond_destroy(&cond);
    }

    _xcb_in_wake_up_next_reader(c);
    return ret;
}

static uint64_t widen(xcb_connection_t *c, unsigned int request)
{
    uint64_t widened_request = (c->out.request & UINT64_C(0xffffffff00000000)) | request;
    if(widened_request > c->out.request)
        widened_request -= UINT64_C(1) << 32;
    return widened_request;
}

/* Public interface */

void *xcb_wait_for_reply(xcb_connection_t *c, unsigned int request, xcb_generic_error_t **e)
{
    void *ret;
    if(e)
        *e = 0;
    if(c->has_error)
        return 0;

    pthread_mutex_lock(&c->iolock);
    ret = wait_for_reply(c, widen(c, request), e);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

void *xcb_wait_for_reply64(xcb_connection_t *c, uint64_t request, xcb_generic_error_t **e)
{
    void *ret;
    if(e)
        *e = 0;
    if(c->has_error)
        return 0;

    pthread_mutex_lock(&c->iolock);
    ret = wait_for_reply(c, request, e);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

int *xcb_get_reply_fds(xcb_connection_t *c, void *reply, size_t reply_size)
{
    return (int *) (&((char *) reply)[reply_size]);
}

static void insert_pending_discard(xcb_connection_t *c, pending_reply **prev_next, uint64_t seq)
{
    pending_reply *pend;
    pend = malloc(sizeof(*pend));
    if(!pend)
    {
        _xcb_conn_shutdown(c, XCB_CONN_CLOSED_MEM_INSUFFICIENT);
        return;
    }

    pend->first_request = seq;
    pend->last_request = seq;
    pend->workaround = 0;
    pend->flags = XCB_REQUEST_DISCARD_REPLY;
    pend->next = *prev_next;
    *prev_next = pend;

    if(!pend->next)
        c->in.pending_replies_tail = &pend->next;
}

static void discard_reply(xcb_connection_t *c, uint64_t request)
{
    void *reply;
    pending_reply **prev_pend;

    /* Free any replies or errors that we've already read. Stop if
     * xcb_wait_for_reply would block or we've run out of replies. */
    while(poll_for_reply(c, request, &reply, 0) && reply)
        free(reply);

    /* If we've proven there are no more responses coming, we're done. */
    if(XCB_SEQUENCE_COMPARE(request, <=, c->in.request_completed))
        return;

    /* Walk the list of pending requests. Mark the first match for deletion. */
    for(prev_pend = &c->in.pending_replies; *prev_pend; prev_pend = &(*prev_pend)->next)
    {
        if(XCB_SEQUENCE_COMPARE((*prev_pend)->first_request, >, request))
            break;

        if((*prev_pend)->first_request == request)
        {
            /* Pending reply found. Mark for discard: */
            (*prev_pend)->flags |= XCB_REQUEST_DISCARD_REPLY;
            return;
        }
    }

    /* Pending reply not found (likely due to _unchecked request). Create one: */
    insert_pending_discard(c, prev_pend, request);
}

void xcb_discard_reply(xcb_connection_t *c, unsigned int sequence)
{
    if(c->has_error)
        return;

    /* If an error occurred when issuing the request, fail immediately. */
    if(!sequence)
        return;

    pthread_mutex_lock(&c->iolock);
    discard_reply(c, widen(c, sequence));
    pthread_mutex_unlock(&c->iolock);
}

void xcb_discard_reply64(xcb_connection_t *c, uint64_t sequence)
{
    if(c->has_error)
        return;

    /* If an error occurred when issuing the request, fail immediately. */
    if(!sequence)
        return;

    pthread_mutex_lock(&c->iolock);
    discard_reply(c, sequence);
    pthread_mutex_unlock(&c->iolock);
}

int xcb_poll_for_reply(xcb_connection_t *c, unsigned int request, void **reply, xcb_generic_error_t **error)
{
    int ret;
    if(c->has_error)
    {
        *reply = 0;
        if(error)
            *error = 0;
        return 1; /* would not block */
    }
    assert(reply != 0);
    pthread_mutex_lock(&c->iolock);
    ret = poll_for_reply(c, widen(c, request), reply, error);
    if(!ret && c->in.reading == 0 && _xcb_in_read(c)) /* _xcb_in_read shuts down the connection on error */
        ret = poll_for_reply(c, widen(c, request), reply, error);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

int xcb_poll_for_reply64(xcb_connection_t *c, uint64_t request, void **reply, xcb_generic_error_t **error)
{
    int ret;
    if(c->has_error)
    {
        *reply = 0;
        if(error)
            *error = 0;
        return 1; /* would not block */
    }
    assert(reply != 0);
    pthread_mutex_lock(&c->iolock);
    ret = poll_for_reply(c, request, reply, error);
    if(!ret && c->in.reading == 0 && _xcb_in_read(c)) /* _xcb_in_read shuts down the connection on error */
        ret = poll_for_reply(c, request, reply, error);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

xcb_generic_event_t *xcb_wait_for_event(xcb_connection_t *c)
{
    xcb_generic_event_t *ret;
    if(c->has_error)
        return 0;
    pthread_mutex_lock(&c->iolock);
    /* get_event returns 0 on empty list. */
    while(!(ret = get_event(c)))
        if(!_xcb_conn_wait(c, &c->in.event_cond, 0, 0))
            break;

    _xcb_in_wake_up_next_reader(c);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

static xcb_generic_event_t *poll_for_next_event(xcb_connection_t *c, int queued)
{
    xcb_generic_event_t *ret = 0;
    if(!c->has_error)
    {
        pthread_mutex_lock(&c->iolock);
        /* FIXME: follow X meets Z architecture changes. */
        ret = get_event(c);
        if(!ret && !queued && c->in.reading == 0 && _xcb_in_read(c)) /* _xcb_in_read shuts down the connection on error */
            ret = get_event(c);
        pthread_mutex_unlock(&c->iolock);
    }
    return ret;
}

xcb_generic_event_t *xcb_poll_for_event(xcb_connection_t *c)
{
    return poll_for_next_event(c, 0);
}

xcb_generic_event_t *xcb_poll_for_queued_event(xcb_connection_t *c)
{
    return poll_for_next_event(c, 1);
}

xcb_generic_error_t *xcb_request_check(xcb_connection_t *c, xcb_void_cookie_t cookie)
{
    uint64_t request;
    xcb_generic_error_t *ret = 0;
    void *reply;
    if(c->has_error)
        return 0;
    pthread_mutex_lock(&c->iolock);
    request = widen(c, cookie.sequence);
    if (XCB_SEQUENCE_COMPARE(request, >, c->in.request_completed))
    {
        if(XCB_SEQUENCE_COMPARE(request, >=, c->in.request_expected))
        {
            _xcb_out_send_sync(c);
        }
        if (XCB_SEQUENCE_COMPARE(request, >=, c->out.request_expected_written))
        {
            _xcb_out_flush_to(c, c->out.request);
        }
    }
    reply = wait_for_reply(c, request, &ret);
    assert(!reply);
    pthread_mutex_unlock(&c->iolock);
    return ret;
}

static xcb_generic_event_t *get_special_event(xcb_connection_t *c,
                                              xcb_special_event_t *se)
{
    xcb_generic_event_t *event = NULL;
    struct event_list *events;

    if ((events = se->events) != NULL) {
        event = events->event;
        if (!(se->events = events->next))
            se->events_tail = &se->events;
        free (events);
    }
    return event;
}

xcb_generic_event_t *xcb_poll_for_special_event(xcb_connection_t *c,
                                                xcb_special_event_t *se)
{
    xcb_generic_event_t *event;

    if(c->has_error)
        return 0;
    pthread_mutex_lock(&c->iolock);
    event = get_special_event(c, se);
    if(!event && c->in.reading == 0 && _xcb_in_read(c)) /* _xcb_in_read shuts down the connection on error */
        event = get_special_event(c, se);
    pthread_mutex_unlock(&c->iolock);
    return event;
}

xcb_generic_event_t *xcb_wait_for_special_event(xcb_connection_t *c,
                                                xcb_special_event_t *se)
{
    special_list special;
    xcb_generic_event_t *event;

    if(c->has_error)
        return 0;
    pthread_mutex_lock(&c->iolock);

    insert_special(&c->in.special_waiters, &special, se);

    /* get_special_event returns 0 on empty list. */
    while(!(event = get_special_event(c, se)))
        if(!_xcb_conn_wait(c, &se->special_event_cond, 0, 0))
            break;

    remove_special(&c->in.special_waiters, &special);

    _xcb_in_wake_up_next_reader(c);
    pthread_mutex_unlock(&c->iolock);
    return event;
}

xcb_special_event_t *
xcb_register_for_special_xge(xcb_connection_t *c,
                             xcb_extension_t *ext,
                             uint32_t eid,
                             uint32_t *stamp)
{
    xcb_special_event_t *se;
    const xcb_query_extension_reply_t   *ext_reply;

    if(c->has_error)
        return NULL;
    ext_reply = xcb_get_extension_data(c, ext);
    if (!ext_reply)
        return NULL;
    pthread_mutex_lock(&c->iolock);
    for (se = c->in.special_events; se; se = se->next) {
        if (se->extension == ext_reply->major_opcode &&
            se->eid == eid) {
            pthread_mutex_unlock(&c->iolock);
            return NULL;
        }
    }
    se = calloc(1, sizeof(xcb_special_event_t));
    if (!se) {
        pthread_mutex_unlock(&c->iolock);
        return NULL;
    }

    se->extension = ext_reply->major_opcode;
    se->eid = eid;

    se->events = NULL;
    se->events_tail = &se->events;
    se->stamp = stamp;

    pthread_cond_init(&se->special_event_cond, 0);

    se->next = c->in.special_events;
    c->in.special_events = se;
    pthread_mutex_unlock(&c->iolock);
    return se;
}

void
xcb_unregister_for_special_event(xcb_connection_t *c,
                                 xcb_special_event_t *se)
{
    xcb_special_event_t *s, **prev;
    struct event_list   *events, *next;

    if (!se)
        return;

    if (c->has_error)
        return;

    pthread_mutex_lock(&c->iolock);

    for (prev = &c->in.special_events; (s = *prev) != NULL; prev = &(s->next)) {
        if (s == se) {
            *prev = se->next;
            for (events = se->events; events; events = next) {
                next = events->next;
                free (events->event);
                free (events);
            }
            pthread_cond_destroy(&se->special_event_cond);
            free (se);
            break;
        }
    }
    pthread_mutex_unlock(&c->iolock);
}

/* Private interface */

int _xcb_in_init(_xcb_in *in)
{
    if(pthread_cond_init(&in->event_cond, 0))
        return 0;
    in->reading = 0;

    in->queue_len = 0;

    in->request_read = 0;
    in->request_completed = 0;

    in->replies = _xcb_map_new();
    if(!in->replies)
        return 0;

    in->current_reply_tail = &in->current_reply;
    in->events_tail = &in->events;
    in->pending_replies_tail = &in->pending_replies;

    return 1;
}

void _xcb_in_destroy(_xcb_in *in)
{
    pthread_cond_destroy(&in->event_cond);
    free_reply_list(in->current_reply);
    _xcb_map_delete(in->replies, (void (*)(void *)) free_reply_list);
    while(in->events)
    {
        struct event_list *e = in->events;
        in->events = e->next;
        free(e->event);
        free(e);
    }
    while(in->pending_replies)
    {
        pending_reply *pend = in->pending_replies;
        in->pending_replies = pend->next;
        free(pend);
    }
}

void _xcb_in_wake_up_next_reader(xcb_connection_t *c)
{
    int pthreadret;
    if(c->in.readers)
        pthreadret = pthread_cond_signal(c->in.readers->data);
    else if(c->in.special_waiters)
        pthreadret = pthread_cond_signal(&c->in.special_waiters->se->special_event_cond);
    else
        pthreadret = pthread_cond_signal(&c->in.event_cond);
    assert(pthreadret == 0);
}

int _xcb_in_expect_reply(xcb_connection_t *c, uint64_t request, enum workarounds workaround, int flags)
{
    pending_reply *pend = malloc(sizeof(pending_reply));
    assert(workaround != WORKAROUND_NONE || flags != 0);
    if(!pend)
    {
        _xcb_conn_shutdown(c, XCB_CONN_CLOSED_MEM_INSUFFICIENT);
        return 0;
    }
    pend->first_request = pend->last_request = request;
    pend->workaround = workaround;
    pend->flags = flags;
    pend->next = 0;
    *c->in.pending_replies_tail = pend;
    c->in.pending_replies_tail = &pend->next;
    return 1;
}

void _xcb_in_replies_done(xcb_connection_t *c)
{
    struct pending_reply *pend;
    if (c->in.pending_replies_tail != &c->in.pending_replies)
    {
        pend = container_of(c->in.pending_replies_tail, struct pending_reply, next);
        if(pend->workaround == WORKAROUND_EXTERNAL_SOCKET_OWNER)
        {
            if (XCB_SEQUENCE_COMPARE(pend->first_request, <=, c->out.request)) {
                pend->last_request = c->out.request;
                pend->workaround = WORKAROUND_NONE;
            } else {
                /* The socket was taken, but no requests were actually sent
                 * so just discard the pending_reply that was created.
                 */
                struct pending_reply **prev_next = &c->in.pending_replies;
                while (*prev_next != pend)
                    prev_next = &(*prev_next)->next;
                *prev_next = NULL;
                c->in.pending_replies_tail = prev_next;
                free(pend);
            }
        }
    }
}

int _xcb_in_read(xcb_connection_t *c)
{
    int n;

#if HAVE_SENDMSG
    struct iovec    iov = {
        .iov_base = c->in.queue + c->in.queue_len,
        .iov_len = sizeof(c->in.queue) - c->in.queue_len,
    };
    union {
        struct cmsghdr cmsghdr;
        char buf[CMSG_SPACE(XCB_MAX_PASS_FD * sizeof(int))];
    } cmsgbuf;
    struct msghdr msg = {
        .msg_name = NULL,
        .msg_namelen = 0,
        .msg_iov = &iov,
        .msg_iovlen = 1,
        .msg_control = cmsgbuf.buf,
        .msg_controllen = CMSG_SPACE(sizeof(int) * (XCB_MAX_PASS_FD - c->in.in_fd.nfd)),
    };
    n = recvmsg(c->fd, &msg, 0);

    /* Check for truncation errors. Only MSG_CTRUNC is
     * probably possible here, which would indicate that
     * the sender tried to transmit more than XCB_MAX_PASS_FD
     * file descriptors.
     */
    if (msg.msg_flags & (MSG_TRUNC|MSG_CTRUNC)) {
        _xcb_conn_shutdown(c, XCB_CONN_CLOSED_FDPASSING_FAILED);
        return 0;
    }
#else
    n = recv(c->fd, c->in.queue + c->in.queue_len, sizeof(c->in.queue) - c->in.queue_len, 0);
#endif
    if(n > 0) {
#if HAVE_SENDMSG
        struct cmsghdr *hdr;

        if (msg.msg_controllen >= sizeof (struct cmsghdr)) {
            for (hdr = CMSG_FIRSTHDR(&msg); hdr; hdr = CMSG_NXTHDR(&msg, hdr)) {
                if (hdr->cmsg_level == SOL_SOCKET && hdr->cmsg_type == SCM_RIGHTS) {
                    int nfd = (hdr->cmsg_len - CMSG_LEN(0)) / sizeof (int);
                    memcpy(&c->in.in_fd.fd[c->in.in_fd.nfd], CMSG_DATA(hdr), nfd * sizeof (int));
                    c->in.in_fd.nfd += nfd;
                }
            }
        }
#endif
        c->in.total_read += n;
        c->in.queue_len += n;
    }
    while(read_packet(c))
        /* empty */;
#if HAVE_SENDMSG
    if (c->in.in_fd.nfd) {
        c->in.in_fd.nfd -= c->in.in_fd.ifd;
        memmove(&c->in.in_fd.fd[0],
                &c->in.in_fd.fd[c->in.in_fd.ifd],
                c->in.in_fd.nfd * sizeof (int));
        c->in.in_fd.ifd = 0;

        /* If we have any left-over file descriptors after emptying
         * the input buffer, then the server sent some that we weren't
         * expecting.  Close them and mark the connection as broken;
         */
        if (c->in.queue_len == 0 && c->in.in_fd.nfd != 0) {
            int i;
            for (i = 0; i < c->in.in_fd.nfd; i++)
                close(c->in.in_fd.fd[i]);
            _xcb_conn_shutdown(c, XCB_CONN_CLOSED_FDPASSING_FAILED);
            return 0;
        }
    }
#endif
#ifndef _WIN32
    if((n > 0) || (n < 0 && (errno == EAGAIN || errno == EINTR)))
#else
    if((n > 0) || (n < 0 && WSAGetLastError() == WSAEWOULDBLOCK))
#endif /* !_WIN32 */
        return 1;
    _xcb_conn_shutdown(c, XCB_CONN_ERROR);
    return 0;
}

int _xcb_in_read_block(xcb_connection_t *c, void *buf, int len)
{
    int done = c->in.queue_len;
    if(len < done)
        done = len;

    memcpy(buf, c->in.queue, done);
    c->in.queue_len -= done;
    memmove(c->in.queue, c->in.queue + done, c->in.queue_len);

    if(len > done)
    {
        int ret = read_block(c->fd, (char *) buf + done, len - done);
        if(ret <= 0)
        {
            _xcb_conn_shutdown(c, XCB_CONN_ERROR);
            return ret;
        }
    }

    return len;
}

/*
 * This file generated automatically from xproto.xml by c_client.py.
 * Edit at your peril.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>  /* for offsetof() */
#include "xcbext.h"
#include "xproto.h"

#define ALIGNOF(type) offsetof(struct { char dummy; type member; }, member)

void
xcb_char2b_next (xcb_char2b_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_char2b_t);
}

xcb_generic_iterator_t
xcb_char2b_end (xcb_char2b_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_window_next (xcb_window_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_window_t);
}

xcb_generic_iterator_t
xcb_window_end (xcb_window_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_pixmap_next (xcb_pixmap_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_pixmap_t);
}

xcb_generic_iterator_t
xcb_pixmap_end (xcb_pixmap_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_cursor_next (xcb_cursor_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_cursor_t);
}

xcb_generic_iterator_t
xcb_cursor_end (xcb_cursor_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_font_next (xcb_font_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_font_t);
}

xcb_generic_iterator_t
xcb_font_end (xcb_font_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_gcontext_next (xcb_gcontext_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_gcontext_t);
}

xcb_generic_iterator_t
xcb_gcontext_end (xcb_gcontext_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_colormap_next (xcb_colormap_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_colormap_t);
}

xcb_generic_iterator_t
xcb_colormap_end (xcb_colormap_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_atom_next (xcb_atom_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_atom_t);
}

xcb_generic_iterator_t
xcb_atom_end (xcb_atom_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_drawable_next (xcb_drawable_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_drawable_t);
}

xcb_generic_iterator_t
xcb_drawable_end (xcb_drawable_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_fontable_next (xcb_fontable_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_fontable_t);
}

xcb_generic_iterator_t
xcb_fontable_end (xcb_fontable_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_bool32_next (xcb_bool32_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_bool32_t);
}

xcb_generic_iterator_t
xcb_bool32_end (xcb_bool32_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_visualid_next (xcb_visualid_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_visualid_t);
}

xcb_generic_iterator_t
xcb_visualid_end (xcb_visualid_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_timestamp_next (xcb_timestamp_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_timestamp_t);
}

xcb_generic_iterator_t
xcb_timestamp_end (xcb_timestamp_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_keysym_next (xcb_keysym_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_keysym_t);
}

xcb_generic_iterator_t
xcb_keysym_end (xcb_keysym_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_keycode_next (xcb_keycode_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_keycode_t);
}

xcb_generic_iterator_t
xcb_keycode_end (xcb_keycode_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_keycode32_next (xcb_keycode32_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_keycode32_t);
}

xcb_generic_iterator_t
xcb_keycode32_end (xcb_keycode32_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_button_next (xcb_button_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_button_t);
}

xcb_generic_iterator_t
xcb_button_end (xcb_button_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_point_next (xcb_point_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_point_t);
}

xcb_generic_iterator_t
xcb_point_end (xcb_point_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_rectangle_next (xcb_rectangle_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_rectangle_t);
}

xcb_generic_iterator_t
xcb_rectangle_end (xcb_rectangle_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_arc_next (xcb_arc_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_arc_t);
}

xcb_generic_iterator_t
xcb_arc_end (xcb_arc_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_format_next (xcb_format_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_format_t);
}

xcb_generic_iterator_t
xcb_format_end (xcb_format_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_visualtype_next (xcb_visualtype_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_visualtype_t);
}

xcb_generic_iterator_t
xcb_visualtype_end (xcb_visualtype_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_depth_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_depth_t *_aux = (xcb_depth_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_depth_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* visuals */
    xcb_block_len += _aux->visuals_len * sizeof(xcb_visualtype_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_visualtype_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_visualtype_t *
xcb_depth_visuals (const xcb_depth_t *R)
{
    return (xcb_visualtype_t *) (R + 1);
}

int
xcb_depth_visuals_length (const xcb_depth_t *R)
{
    return R->visuals_len;
}

xcb_visualtype_iterator_t
xcb_depth_visuals_iterator (const xcb_depth_t *R)
{
    xcb_visualtype_iterator_t i;
    i.data = (xcb_visualtype_t *) (R + 1);
    i.rem = R->visuals_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_depth_next (xcb_depth_iterator_t *i)
{
    xcb_depth_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_depth_t *)(((char *)R) + xcb_depth_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_depth_t *) child.data;
}

xcb_generic_iterator_t
xcb_depth_end (xcb_depth_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_depth_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_screen_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_screen_t *_aux = (xcb_screen_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;

    unsigned int i;
    unsigned int xcb_tmp_len;

    xcb_block_len += sizeof(xcb_screen_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* allowed_depths */
    for(i=0; i<_aux->allowed_depths_len; i++) {
        xcb_tmp_len = xcb_depth_sizeof(xcb_tmp);
        xcb_block_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_align_to = ALIGNOF(xcb_depth_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

int
xcb_screen_allowed_depths_length (const xcb_screen_t *R)
{
    return R->allowed_depths_len;
}

xcb_depth_iterator_t
xcb_screen_allowed_depths_iterator (const xcb_screen_t *R)
{
    xcb_depth_iterator_t i;
    i.data = (xcb_depth_t *) (R + 1);
    i.rem = R->allowed_depths_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_screen_next (xcb_screen_iterator_t *i)
{
    xcb_screen_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_screen_t *)(((char *)R) + xcb_screen_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_screen_t *) child.data;
}

xcb_generic_iterator_t
xcb_screen_end (xcb_screen_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_screen_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_setup_request_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_setup_request_t *_aux = (xcb_setup_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_setup_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* authorization_protocol_name */
    xcb_block_len += _aux->authorization_protocol_name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    xcb_align_to = 4;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* authorization_protocol_data */
    xcb_block_len += _aux->authorization_protocol_data_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    xcb_align_to = 4;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

char *
xcb_setup_request_authorization_protocol_name (const xcb_setup_request_t *R)
{
    return (char *) (R + 1);
}

int
xcb_setup_request_authorization_protocol_name_length (const xcb_setup_request_t *R)
{
    return R->authorization_protocol_name_len;
}

xcb_generic_iterator_t
xcb_setup_request_authorization_protocol_name_end (const xcb_setup_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->authorization_protocol_name_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

char *
xcb_setup_request_authorization_protocol_data (const xcb_setup_request_t *R)
{
    xcb_generic_iterator_t prev = xcb_setup_request_authorization_protocol_name_end(R);
    return (char *) ((char *) prev.data + ((-prev.index) & (4 - 1)) + 0);
}

int
xcb_setup_request_authorization_protocol_data_length (const xcb_setup_request_t *R)
{
    return R->authorization_protocol_data_len;
}

xcb_generic_iterator_t
xcb_setup_request_authorization_protocol_data_end (const xcb_setup_request_t *R)
{
    xcb_generic_iterator_t i;
    xcb_generic_iterator_t prev = xcb_setup_request_authorization_protocol_name_end(R);
    i.data = ((char *) ((char*) prev.data + ((-prev.index) & (4 - 1)))) + (R->authorization_protocol_data_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_setup_request_next (xcb_setup_request_iterator_t *i)
{
    xcb_setup_request_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_setup_request_t *)(((char *)R) + xcb_setup_request_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_setup_request_t *) child.data;
}

xcb_generic_iterator_t
xcb_setup_request_end (xcb_setup_request_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_setup_request_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_setup_failed_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_setup_failed_t *_aux = (xcb_setup_failed_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_setup_failed_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* reason */
    xcb_block_len += _aux->reason_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

char *
xcb_setup_failed_reason (const xcb_setup_failed_t *R)
{
    return (char *) (R + 1);
}

int
xcb_setup_failed_reason_length (const xcb_setup_failed_t *R)
{
    return R->reason_len;
}

xcb_generic_iterator_t
xcb_setup_failed_reason_end (const xcb_setup_failed_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->reason_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_setup_failed_next (xcb_setup_failed_iterator_t *i)
{
    xcb_setup_failed_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_setup_failed_t *)(((char *)R) + xcb_setup_failed_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_setup_failed_t *) child.data;
}

xcb_generic_iterator_t
xcb_setup_failed_end (xcb_setup_failed_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_setup_failed_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_setup_authenticate_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_setup_authenticate_t *_aux = (xcb_setup_authenticate_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_setup_authenticate_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* reason */
    xcb_block_len += (_aux->length * 4) * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

char *
xcb_setup_authenticate_reason (const xcb_setup_authenticate_t *R)
{
    return (char *) (R + 1);
}

int
xcb_setup_authenticate_reason_length (const xcb_setup_authenticate_t *R)
{
    return (R->length * 4);
}

xcb_generic_iterator_t
xcb_setup_authenticate_reason_end (const xcb_setup_authenticate_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + ((R->length * 4));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_setup_authenticate_next (xcb_setup_authenticate_iterator_t *i)
{
    xcb_setup_authenticate_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_setup_authenticate_t *)(((char *)R) + xcb_setup_authenticate_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_setup_authenticate_t *) child.data;
}

xcb_generic_iterator_t
xcb_setup_authenticate_end (xcb_setup_authenticate_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_setup_authenticate_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_setup_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_setup_t *_aux = (xcb_setup_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;

    unsigned int i;
    unsigned int xcb_tmp_len;

    xcb_block_len += sizeof(xcb_setup_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* vendor */
    xcb_block_len += _aux->vendor_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    xcb_align_to = 4;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* pixmap_formats */
    xcb_block_len += _aux->pixmap_formats_len * sizeof(xcb_format_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_format_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* roots */
    for(i=0; i<_aux->roots_len; i++) {
        xcb_tmp_len = xcb_screen_sizeof(xcb_tmp);
        xcb_block_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_align_to = ALIGNOF(xcb_screen_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

char *
xcb_setup_vendor (const xcb_setup_t *R)
{
    return (char *) (R + 1);
}

int
xcb_setup_vendor_length (const xcb_setup_t *R)
{
    return R->vendor_len;
}

xcb_generic_iterator_t
xcb_setup_vendor_end (const xcb_setup_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->vendor_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_format_t *
xcb_setup_pixmap_formats (const xcb_setup_t *R)
{
    xcb_generic_iterator_t prev = xcb_setup_vendor_end(R);
    return (xcb_format_t *) ((char *) prev.data + ((-prev.index) & (4 - 1)) + 0);
}

int
xcb_setup_pixmap_formats_length (const xcb_setup_t *R)
{
    return R->pixmap_formats_len;
}

xcb_format_iterator_t
xcb_setup_pixmap_formats_iterator (const xcb_setup_t *R)
{
    xcb_format_iterator_t i;
    xcb_generic_iterator_t prev = xcb_setup_vendor_end(R);
    i.data = (xcb_format_t *) ((char *) prev.data + ((-prev.index) & (4 - 1)));
    i.rem = R->pixmap_formats_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_setup_roots_length (const xcb_setup_t *R)
{
    return R->roots_len;
}

xcb_screen_iterator_t
xcb_setup_roots_iterator (const xcb_setup_t *R)
{
    xcb_screen_iterator_t i;
    xcb_generic_iterator_t prev = xcb_format_end(xcb_setup_pixmap_formats_iterator(R));
    i.data = (xcb_screen_t *) ((char *) prev.data + XCB_TYPE_PAD(xcb_screen_t, prev.index));
    i.rem = R->roots_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_setup_next (xcb_setup_iterator_t *i)
{
    xcb_setup_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_setup_t *)(((char *)R) + xcb_setup_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_setup_t *) child.data;
}

xcb_generic_iterator_t
xcb_setup_end (xcb_setup_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_setup_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

void
xcb_client_message_data_next (xcb_client_message_data_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_client_message_data_t);
}

xcb_generic_iterator_t
xcb_client_message_data_end (xcb_client_message_data_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_create_window_value_list_serialize (void                                 **_buffer,
                                        uint32_t                               value_mask,
                                        const xcb_create_window_value_list_t  *_aux)
{
    char *xcb_out = *_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;

    unsigned int xcb_pad = 0;
    char xcb_pad0[3] = {0, 0, 0};
    struct iovec xcb_parts[16];
    unsigned int xcb_parts_idx = 0;
    unsigned int xcb_block_len = 0;
    unsigned int i;
    char *xcb_tmp;

    if(value_mask & XCB_CW_BACK_PIXMAP) {
        /* xcb_create_window_value_list_t.background_pixmap */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->background_pixmap;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BACK_PIXEL) {
        /* xcb_create_window_value_list_t.background_pixel */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->background_pixel;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXMAP) {
        /* xcb_create_window_value_list_t.border_pixmap */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->border_pixmap;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXEL) {
        /* xcb_create_window_value_list_t.border_pixel */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->border_pixel;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BIT_GRAVITY) {
        /* xcb_create_window_value_list_t.bit_gravity */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->bit_gravity;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_WIN_GRAVITY) {
        /* xcb_create_window_value_list_t.win_gravity */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->win_gravity;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_STORE) {
        /* xcb_create_window_value_list_t.backing_store */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->backing_store;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PLANES) {
        /* xcb_create_window_value_list_t.backing_planes */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->backing_planes;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PIXEL) {
        /* xcb_create_window_value_list_t.backing_pixel */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->backing_pixel;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_OVERRIDE_REDIRECT) {
        /* xcb_create_window_value_list_t.override_redirect */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->override_redirect;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_bool32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_SAVE_UNDER) {
        /* xcb_create_window_value_list_t.save_under */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->save_under;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_bool32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_EVENT_MASK) {
        /* xcb_create_window_value_list_t.event_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->event_mask;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_DONT_PROPAGATE) {
        /* xcb_create_window_value_list_t.do_not_propogate_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->do_not_propogate_mask;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_COLORMAP) {
        /* xcb_create_window_value_list_t.colormap */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->colormap;
        xcb_block_len += sizeof(xcb_colormap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_colormap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_colormap_t);
    }
    if(value_mask & XCB_CW_CURSOR) {
        /* xcb_create_window_value_list_t.cursor */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->cursor;
        xcb_block_len += sizeof(xcb_cursor_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_cursor_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_cursor_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_parts[xcb_parts_idx].iov_base = xcb_pad0;
        xcb_parts[xcb_parts_idx].iov_len = xcb_pad;
        xcb_parts_idx++;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    if (NULL == xcb_out) {
        /* allocate memory */
        xcb_out = malloc(xcb_buffer_len);
        *_buffer = xcb_out;
    }

    xcb_tmp = xcb_out;
    for(i=0; i<xcb_parts_idx; i++) {
        if (0 != xcb_parts[i].iov_base && 0 != xcb_parts[i].iov_len)
            memcpy(xcb_tmp, xcb_parts[i].iov_base, xcb_parts[i].iov_len);
        if (0 != xcb_parts[i].iov_len)
            xcb_tmp += xcb_parts[i].iov_len;
    }

    return xcb_buffer_len;
}

int
xcb_create_window_value_list_unpack (const void                      *_buffer,
                                     uint32_t                         value_mask,
                                     xcb_create_window_value_list_t  *_aux)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;


    if(value_mask & XCB_CW_BACK_PIXMAP) {
        /* xcb_create_window_value_list_t.background_pixmap */
        _aux->background_pixmap = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BACK_PIXEL) {
        /* xcb_create_window_value_list_t.background_pixel */
        _aux->background_pixel = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXMAP) {
        /* xcb_create_window_value_list_t.border_pixmap */
        _aux->border_pixmap = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXEL) {
        /* xcb_create_window_value_list_t.border_pixel */
        _aux->border_pixel = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BIT_GRAVITY) {
        /* xcb_create_window_value_list_t.bit_gravity */
        _aux->bit_gravity = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_WIN_GRAVITY) {
        /* xcb_create_window_value_list_t.win_gravity */
        _aux->win_gravity = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_STORE) {
        /* xcb_create_window_value_list_t.backing_store */
        _aux->backing_store = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PLANES) {
        /* xcb_create_window_value_list_t.backing_planes */
        _aux->backing_planes = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PIXEL) {
        /* xcb_create_window_value_list_t.backing_pixel */
        _aux->backing_pixel = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_OVERRIDE_REDIRECT) {
        /* xcb_create_window_value_list_t.override_redirect */
        _aux->override_redirect = *(xcb_bool32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_tmp += sizeof(xcb_bool32_t);
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_SAVE_UNDER) {
        /* xcb_create_window_value_list_t.save_under */
        _aux->save_under = *(xcb_bool32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_tmp += sizeof(xcb_bool32_t);
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_EVENT_MASK) {
        /* xcb_create_window_value_list_t.event_mask */
        _aux->event_mask = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_DONT_PROPAGATE) {
        /* xcb_create_window_value_list_t.do_not_propogate_mask */
        _aux->do_not_propogate_mask = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_COLORMAP) {
        /* xcb_create_window_value_list_t.colormap */
        _aux->colormap = *(xcb_colormap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_colormap_t);
        xcb_tmp += sizeof(xcb_colormap_t);
        xcb_align_to = ALIGNOF(xcb_colormap_t);
    }
    if(value_mask & XCB_CW_CURSOR) {
        /* xcb_create_window_value_list_t.cursor */
        _aux->cursor = *(xcb_cursor_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_cursor_t);
        xcb_tmp += sizeof(xcb_cursor_t);
        xcb_align_to = ALIGNOF(xcb_cursor_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    return xcb_buffer_len;
}

int
xcb_create_window_value_list_sizeof (const void  *_buffer,
                                     uint32_t     value_mask)
{
    xcb_create_window_value_list_t _aux;
    return xcb_create_window_value_list_unpack(_buffer, value_mask, &_aux);
}

int
xcb_create_window_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_create_window_request_t *_aux = (xcb_create_window_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_create_window_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value_list */
    xcb_block_len += xcb_create_window_value_list_sizeof(xcb_tmp, _aux->value_mask);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_create_window_checked (xcb_connection_t *c,
                           uint8_t           depth,
                           xcb_window_t      wid,
                           xcb_window_t      parent,
                           int16_t           x,
                           int16_t           y,
                           uint16_t          width,
                           uint16_t          height,
                           uint16_t          border_width,
                           uint16_t          _class,
                           xcb_visualid_t    visual,
                           uint32_t          value_mask,
                           const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_window_request_t xcb_out;

    xcb_out.depth = depth;
    xcb_out.wid = wid;
    xcb_out.parent = parent;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.border_width = border_width;
    xcb_out._class = _class;
    xcb_out.visual = visual;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_window_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_create_window_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_window (xcb_connection_t *c,
                   uint8_t           depth,
                   xcb_window_t      wid,
                   xcb_window_t      parent,
                   int16_t           x,
                   int16_t           y,
                   uint16_t          width,
                   uint16_t          height,
                   uint16_t          border_width,
                   uint16_t          _class,
                   xcb_visualid_t    visual,
                   uint32_t          value_mask,
                   const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_window_request_t xcb_out;

    xcb_out.depth = depth;
    xcb_out.wid = wid;
    xcb_out.parent = parent;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.border_width = border_width;
    xcb_out._class = _class;
    xcb_out.visual = visual;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_window_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_create_window_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_window_aux_checked (xcb_connection_t                     *c,
                               uint8_t                               depth,
                               xcb_window_t                          wid,
                               xcb_window_t                          parent,
                               int16_t                               x,
                               int16_t                               y,
                               uint16_t                              width,
                               uint16_t                              height,
                               uint16_t                              border_width,
                               uint16_t                              _class,
                               xcb_visualid_t                        visual,
                               uint32_t                              value_mask,
                               const xcb_create_window_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_window_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.depth = depth;
    xcb_out.wid = wid;
    xcb_out.parent = parent;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.border_width = border_width;
    xcb_out._class = _class;
    xcb_out.visual = visual;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_window_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_create_window_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_window_aux (xcb_connection_t                     *c,
                       uint8_t                               depth,
                       xcb_window_t                          wid,
                       xcb_window_t                          parent,
                       int16_t                               x,
                       int16_t                               y,
                       uint16_t                              width,
                       uint16_t                              height,
                       uint16_t                              border_width,
                       uint16_t                              _class,
                       xcb_visualid_t                        visual,
                       uint32_t                              value_mask,
                       const xcb_create_window_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_window_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.depth = depth;
    xcb_out.wid = wid;
    xcb_out.parent = parent;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.border_width = border_width;
    xcb_out._class = _class;
    xcb_out.visual = visual;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_window_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_create_window_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

void *
xcb_create_window_value_list (const xcb_create_window_request_t *R)
{
    return (void *) (R + 1);
}

int
xcb_change_window_attributes_value_list_serialize (void                                            **_buffer,
                                                   uint32_t                                          value_mask,
                                                   const xcb_change_window_attributes_value_list_t  *_aux)
{
    char *xcb_out = *_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;

    unsigned int xcb_pad = 0;
    char xcb_pad0[3] = {0, 0, 0};
    struct iovec xcb_parts[16];
    unsigned int xcb_parts_idx = 0;
    unsigned int xcb_block_len = 0;
    unsigned int i;
    char *xcb_tmp;

    if(value_mask & XCB_CW_BACK_PIXMAP) {
        /* xcb_change_window_attributes_value_list_t.background_pixmap */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->background_pixmap;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BACK_PIXEL) {
        /* xcb_change_window_attributes_value_list_t.background_pixel */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->background_pixel;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXMAP) {
        /* xcb_change_window_attributes_value_list_t.border_pixmap */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->border_pixmap;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXEL) {
        /* xcb_change_window_attributes_value_list_t.border_pixel */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->border_pixel;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BIT_GRAVITY) {
        /* xcb_change_window_attributes_value_list_t.bit_gravity */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->bit_gravity;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_WIN_GRAVITY) {
        /* xcb_change_window_attributes_value_list_t.win_gravity */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->win_gravity;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_STORE) {
        /* xcb_change_window_attributes_value_list_t.backing_store */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->backing_store;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PLANES) {
        /* xcb_change_window_attributes_value_list_t.backing_planes */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->backing_planes;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PIXEL) {
        /* xcb_change_window_attributes_value_list_t.backing_pixel */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->backing_pixel;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_OVERRIDE_REDIRECT) {
        /* xcb_change_window_attributes_value_list_t.override_redirect */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->override_redirect;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_bool32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_SAVE_UNDER) {
        /* xcb_change_window_attributes_value_list_t.save_under */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->save_under;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_bool32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_EVENT_MASK) {
        /* xcb_change_window_attributes_value_list_t.event_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->event_mask;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_DONT_PROPAGATE) {
        /* xcb_change_window_attributes_value_list_t.do_not_propogate_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->do_not_propogate_mask;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_COLORMAP) {
        /* xcb_change_window_attributes_value_list_t.colormap */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->colormap;
        xcb_block_len += sizeof(xcb_colormap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_colormap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_colormap_t);
    }
    if(value_mask & XCB_CW_CURSOR) {
        /* xcb_change_window_attributes_value_list_t.cursor */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->cursor;
        xcb_block_len += sizeof(xcb_cursor_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_cursor_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_cursor_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_parts[xcb_parts_idx].iov_base = xcb_pad0;
        xcb_parts[xcb_parts_idx].iov_len = xcb_pad;
        xcb_parts_idx++;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    if (NULL == xcb_out) {
        /* allocate memory */
        xcb_out = malloc(xcb_buffer_len);
        *_buffer = xcb_out;
    }

    xcb_tmp = xcb_out;
    for(i=0; i<xcb_parts_idx; i++) {
        if (0 != xcb_parts[i].iov_base && 0 != xcb_parts[i].iov_len)
            memcpy(xcb_tmp, xcb_parts[i].iov_base, xcb_parts[i].iov_len);
        if (0 != xcb_parts[i].iov_len)
            xcb_tmp += xcb_parts[i].iov_len;
    }

    return xcb_buffer_len;
}

int
xcb_change_window_attributes_value_list_unpack (const void                                 *_buffer,
                                                uint32_t                                    value_mask,
                                                xcb_change_window_attributes_value_list_t  *_aux)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;


    if(value_mask & XCB_CW_BACK_PIXMAP) {
        /* xcb_change_window_attributes_value_list_t.background_pixmap */
        _aux->background_pixmap = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BACK_PIXEL) {
        /* xcb_change_window_attributes_value_list_t.background_pixel */
        _aux->background_pixel = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXMAP) {
        /* xcb_change_window_attributes_value_list_t.border_pixmap */
        _aux->border_pixmap = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_CW_BORDER_PIXEL) {
        /* xcb_change_window_attributes_value_list_t.border_pixel */
        _aux->border_pixel = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BIT_GRAVITY) {
        /* xcb_change_window_attributes_value_list_t.bit_gravity */
        _aux->bit_gravity = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_WIN_GRAVITY) {
        /* xcb_change_window_attributes_value_list_t.win_gravity */
        _aux->win_gravity = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_STORE) {
        /* xcb_change_window_attributes_value_list_t.backing_store */
        _aux->backing_store = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PLANES) {
        /* xcb_change_window_attributes_value_list_t.backing_planes */
        _aux->backing_planes = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_BACKING_PIXEL) {
        /* xcb_change_window_attributes_value_list_t.backing_pixel */
        _aux->backing_pixel = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_OVERRIDE_REDIRECT) {
        /* xcb_change_window_attributes_value_list_t.override_redirect */
        _aux->override_redirect = *(xcb_bool32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_tmp += sizeof(xcb_bool32_t);
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_SAVE_UNDER) {
        /* xcb_change_window_attributes_value_list_t.save_under */
        _aux->save_under = *(xcb_bool32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_tmp += sizeof(xcb_bool32_t);
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_CW_EVENT_MASK) {
        /* xcb_change_window_attributes_value_list_t.event_mask */
        _aux->event_mask = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_DONT_PROPAGATE) {
        /* xcb_change_window_attributes_value_list_t.do_not_propogate_mask */
        _aux->do_not_propogate_mask = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CW_COLORMAP) {
        /* xcb_change_window_attributes_value_list_t.colormap */
        _aux->colormap = *(xcb_colormap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_colormap_t);
        xcb_tmp += sizeof(xcb_colormap_t);
        xcb_align_to = ALIGNOF(xcb_colormap_t);
    }
    if(value_mask & XCB_CW_CURSOR) {
        /* xcb_change_window_attributes_value_list_t.cursor */
        _aux->cursor = *(xcb_cursor_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_cursor_t);
        xcb_tmp += sizeof(xcb_cursor_t);
        xcb_align_to = ALIGNOF(xcb_cursor_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    return xcb_buffer_len;
}

int
xcb_change_window_attributes_value_list_sizeof (const void  *_buffer,
                                                uint32_t     value_mask)
{
    xcb_change_window_attributes_value_list_t _aux;
    return xcb_change_window_attributes_value_list_unpack(_buffer, value_mask, &_aux);
}

int
xcb_change_window_attributes_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_change_window_attributes_request_t *_aux = (xcb_change_window_attributes_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_change_window_attributes_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value_list */
    xcb_block_len += xcb_change_window_attributes_value_list_sizeof(xcb_tmp, _aux->value_mask);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_change_window_attributes_checked (xcb_connection_t *c,
                                      xcb_window_t      window,
                                      uint32_t          value_mask,
                                      const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_WINDOW_ATTRIBUTES,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_window_attributes_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_window_attributes_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_change_window_attributes_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_window_attributes (xcb_connection_t *c,
                              xcb_window_t      window,
                              uint32_t          value_mask,
                              const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_WINDOW_ATTRIBUTES,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_window_attributes_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_window_attributes_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_change_window_attributes_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_window_attributes_aux_checked (xcb_connection_t                                *c,
                                          xcb_window_t                                     window,
                                          uint32_t                                         value_mask,
                                          const xcb_change_window_attributes_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_WINDOW_ATTRIBUTES,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_window_attributes_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_window_attributes_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_change_window_attributes_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_window_attributes_aux (xcb_connection_t                                *c,
                                  xcb_window_t                                     window,
                                  uint32_t                                         value_mask,
                                  const xcb_change_window_attributes_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_WINDOW_ATTRIBUTES,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_window_attributes_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_window_attributes_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_change_window_attributes_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

void *
xcb_change_window_attributes_value_list (const xcb_change_window_attributes_request_t *R)
{
    return (void *) (R + 1);
}

xcb_get_window_attributes_cookie_t
xcb_get_window_attributes (xcb_connection_t *c,
                           xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_WINDOW_ATTRIBUTES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_window_attributes_cookie_t xcb_ret;
    xcb_get_window_attributes_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_window_attributes_cookie_t
xcb_get_window_attributes_unchecked (xcb_connection_t *c,
                                     xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_WINDOW_ATTRIBUTES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_window_attributes_cookie_t xcb_ret;
    xcb_get_window_attributes_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_window_attributes_reply_t *
xcb_get_window_attributes_reply (xcb_connection_t                    *c,
                                 xcb_get_window_attributes_cookie_t   cookie  /**< */,
                                 xcb_generic_error_t                **e)
{
    return (xcb_get_window_attributes_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_destroy_window_checked (xcb_connection_t *c,
                            xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_DESTROY_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_destroy_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_destroy_window (xcb_connection_t *c,
                    xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_DESTROY_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_destroy_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_destroy_subwindows_checked (xcb_connection_t *c,
                                xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_DESTROY_SUBWINDOWS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_destroy_subwindows_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_destroy_subwindows (xcb_connection_t *c,
                        xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_DESTROY_SUBWINDOWS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_destroy_subwindows_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_save_set_checked (xcb_connection_t *c,
                             uint8_t           mode,
                             xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CHANGE_SAVE_SET,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_change_save_set_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_save_set (xcb_connection_t *c,
                     uint8_t           mode,
                     xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CHANGE_SAVE_SET,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_change_save_set_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_reparent_window_checked (xcb_connection_t *c,
                             xcb_window_t      window,
                             xcb_window_t      parent,
                             int16_t           x,
                             int16_t           y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_REPARENT_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_reparent_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.parent = parent;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_reparent_window (xcb_connection_t *c,
                     xcb_window_t      window,
                     xcb_window_t      parent,
                     int16_t           x,
                     int16_t           y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_REPARENT_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_reparent_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.parent = parent;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_map_window_checked (xcb_connection_t *c,
                        xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_MAP_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_map_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_map_window (xcb_connection_t *c,
                xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_MAP_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_map_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_map_subwindows_checked (xcb_connection_t *c,
                            xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_MAP_SUBWINDOWS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_map_subwindows_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_map_subwindows (xcb_connection_t *c,
                    xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_MAP_SUBWINDOWS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_map_subwindows_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_unmap_window_checked (xcb_connection_t *c,
                          xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNMAP_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_unmap_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_unmap_window (xcb_connection_t *c,
                  xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNMAP_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_unmap_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_unmap_subwindows_checked (xcb_connection_t *c,
                              xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNMAP_SUBWINDOWS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_unmap_subwindows_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_unmap_subwindows (xcb_connection_t *c,
                      xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNMAP_SUBWINDOWS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_unmap_subwindows_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_configure_window_value_list_serialize (void                                    **_buffer,
                                           uint16_t                                  value_mask,
                                           const xcb_configure_window_value_list_t  *_aux)
{
    char *xcb_out = *_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;

    unsigned int xcb_pad = 0;
    char xcb_pad0[3] = {0, 0, 0};
    struct iovec xcb_parts[8];
    unsigned int xcb_parts_idx = 0;
    unsigned int xcb_block_len = 0;
    unsigned int i;
    char *xcb_tmp;

    if(value_mask & XCB_CONFIG_WINDOW_X) {
        /* xcb_configure_window_value_list_t.x */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->x;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_Y) {
        /* xcb_configure_window_value_list_t.y */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->y;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_WIDTH) {
        /* xcb_configure_window_value_list_t.width */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->width;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_HEIGHT) {
        /* xcb_configure_window_value_list_t.height */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->height;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_BORDER_WIDTH) {
        /* xcb_configure_window_value_list_t.border_width */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->border_width;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_SIBLING) {
        /* xcb_configure_window_value_list_t.sibling */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->sibling;
        xcb_block_len += sizeof(xcb_window_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_window_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_window_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_STACK_MODE) {
        /* xcb_configure_window_value_list_t.stack_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->stack_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_parts[xcb_parts_idx].iov_base = xcb_pad0;
        xcb_parts[xcb_parts_idx].iov_len = xcb_pad;
        xcb_parts_idx++;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    if (NULL == xcb_out) {
        /* allocate memory */
        xcb_out = malloc(xcb_buffer_len);
        *_buffer = xcb_out;
    }

    xcb_tmp = xcb_out;
    for(i=0; i<xcb_parts_idx; i++) {
        if (0 != xcb_parts[i].iov_base && 0 != xcb_parts[i].iov_len)
            memcpy(xcb_tmp, xcb_parts[i].iov_base, xcb_parts[i].iov_len);
        if (0 != xcb_parts[i].iov_len)
            xcb_tmp += xcb_parts[i].iov_len;
    }

    return xcb_buffer_len;
}

int
xcb_configure_window_value_list_unpack (const void                         *_buffer,
                                        uint16_t                            value_mask,
                                        xcb_configure_window_value_list_t  *_aux)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;


    if(value_mask & XCB_CONFIG_WINDOW_X) {
        /* xcb_configure_window_value_list_t.x */
        _aux->x = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_Y) {
        /* xcb_configure_window_value_list_t.y */
        _aux->y = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_WIDTH) {
        /* xcb_configure_window_value_list_t.width */
        _aux->width = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_HEIGHT) {
        /* xcb_configure_window_value_list_t.height */
        _aux->height = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_BORDER_WIDTH) {
        /* xcb_configure_window_value_list_t.border_width */
        _aux->border_width = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_SIBLING) {
        /* xcb_configure_window_value_list_t.sibling */
        _aux->sibling = *(xcb_window_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_window_t);
        xcb_tmp += sizeof(xcb_window_t);
        xcb_align_to = ALIGNOF(xcb_window_t);
    }
    if(value_mask & XCB_CONFIG_WINDOW_STACK_MODE) {
        /* xcb_configure_window_value_list_t.stack_mode */
        _aux->stack_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    return xcb_buffer_len;
}

int
xcb_configure_window_value_list_sizeof (const void  *_buffer,
                                        uint16_t     value_mask)
{
    xcb_configure_window_value_list_t _aux;
    return xcb_configure_window_value_list_unpack(_buffer, value_mask, &_aux);
}

int
xcb_configure_window_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_configure_window_request_t *_aux = (xcb_configure_window_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_configure_window_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value_list */
    xcb_block_len += xcb_configure_window_value_list_sizeof(xcb_tmp, _aux->value_mask);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_configure_window_checked (xcb_connection_t *c,
                              xcb_window_t      window,
                              uint16_t          value_mask,
                              const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CONFIGURE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_configure_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_configure_window_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_configure_window_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_configure_window (xcb_connection_t *c,
                      xcb_window_t      window,
                      uint16_t          value_mask,
                      const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CONFIGURE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_configure_window_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_configure_window_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_configure_window_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_configure_window_aux_checked (xcb_connection_t                        *c,
                                  xcb_window_t                             window,
                                  uint16_t                                 value_mask,
                                  const xcb_configure_window_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CONFIGURE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_configure_window_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_configure_window_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_configure_window_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_configure_window_aux (xcb_connection_t                        *c,
                          xcb_window_t                             window,
                          uint16_t                                 value_mask,
                          const xcb_configure_window_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CONFIGURE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_configure_window_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.value_mask = value_mask;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_configure_window_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_configure_window_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

void *
xcb_configure_window_value_list (const xcb_configure_window_request_t *R)
{
    return (void *) (R + 1);
}

xcb_void_cookie_t
xcb_circulate_window_checked (xcb_connection_t *c,
                              uint8_t           direction,
                              xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CIRCULATE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_circulate_window_request_t xcb_out;

    xcb_out.direction = direction;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_circulate_window (xcb_connection_t *c,
                      uint8_t           direction,
                      xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CIRCULATE_WINDOW,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_circulate_window_request_t xcb_out;

    xcb_out.direction = direction;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_geometry_cookie_t
xcb_get_geometry (xcb_connection_t *c,
                  xcb_drawable_t    drawable)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_GEOMETRY,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_geometry_cookie_t xcb_ret;
    xcb_get_geometry_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_geometry_cookie_t
xcb_get_geometry_unchecked (xcb_connection_t *c,
                            xcb_drawable_t    drawable)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_GEOMETRY,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_geometry_cookie_t xcb_ret;
    xcb_get_geometry_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_geometry_reply_t *
xcb_get_geometry_reply (xcb_connection_t           *c,
                        xcb_get_geometry_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_get_geometry_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_query_tree_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_query_tree_reply_t *_aux = (xcb_query_tree_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_query_tree_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* children */
    xcb_block_len += _aux->children_len * sizeof(xcb_window_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_window_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_query_tree_cookie_t
xcb_query_tree (xcb_connection_t *c,
                xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_TREE,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_tree_cookie_t xcb_ret;
    xcb_query_tree_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_tree_cookie_t
xcb_query_tree_unchecked (xcb_connection_t *c,
                          xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_TREE,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_tree_cookie_t xcb_ret;
    xcb_query_tree_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_window_t *
xcb_query_tree_children (const xcb_query_tree_reply_t *R)
{
    return (xcb_window_t *) (R + 1);
}

int
xcb_query_tree_children_length (const xcb_query_tree_reply_t *R)
{
    return R->children_len;
}

xcb_generic_iterator_t
xcb_query_tree_children_end (const xcb_query_tree_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_window_t *) (R + 1)) + (R->children_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_query_tree_reply_t *
xcb_query_tree_reply (xcb_connection_t         *c,
                      xcb_query_tree_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e)
{
    return (xcb_query_tree_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_intern_atom_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_intern_atom_request_t *_aux = (xcb_intern_atom_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_intern_atom_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_intern_atom_cookie_t
xcb_intern_atom (xcb_connection_t *c,
                 uint8_t           only_if_exists,
                 uint16_t          name_len,
                 const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_INTERN_ATOM,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_intern_atom_cookie_t xcb_ret;
    xcb_intern_atom_request_t xcb_out;

    xcb_out.only_if_exists = only_if_exists;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_intern_atom_cookie_t
xcb_intern_atom_unchecked (xcb_connection_t *c,
                           uint8_t           only_if_exists,
                           uint16_t          name_len,
                           const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_INTERN_ATOM,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_intern_atom_cookie_t xcb_ret;
    xcb_intern_atom_request_t xcb_out;

    xcb_out.only_if_exists = only_if_exists;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_intern_atom_reply_t *
xcb_intern_atom_reply (xcb_connection_t          *c,
                       xcb_intern_atom_cookie_t   cookie  /**< */,
                       xcb_generic_error_t      **e)
{
    return (xcb_intern_atom_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_get_atom_name_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_atom_name_reply_t *_aux = (xcb_get_atom_name_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_atom_name_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_atom_name_cookie_t
xcb_get_atom_name (xcb_connection_t *c,
                   xcb_atom_t        atom)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_ATOM_NAME,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_atom_name_cookie_t xcb_ret;
    xcb_get_atom_name_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.atom = atom;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_atom_name_cookie_t
xcb_get_atom_name_unchecked (xcb_connection_t *c,
                             xcb_atom_t        atom)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_ATOM_NAME,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_atom_name_cookie_t xcb_ret;
    xcb_get_atom_name_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.atom = atom;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

char *
xcb_get_atom_name_name (const xcb_get_atom_name_reply_t *R)
{
    return (char *) (R + 1);
}

int
xcb_get_atom_name_name_length (const xcb_get_atom_name_reply_t *R)
{
    return R->name_len;
}

xcb_generic_iterator_t
xcb_get_atom_name_name_end (const xcb_get_atom_name_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->name_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_atom_name_reply_t *
xcb_get_atom_name_reply (xcb_connection_t            *c,
                         xcb_get_atom_name_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e)
{
    return (xcb_get_atom_name_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_change_property_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_change_property_request_t *_aux = (xcb_change_property_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_change_property_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* data */
    xcb_block_len += ((_aux->data_len * _aux->format) / 8) * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_change_property_checked (xcb_connection_t *c,
                             uint8_t           mode,
                             xcb_window_t      window,
                             xcb_atom_t        property,
                             xcb_atom_t        type,
                             uint8_t           format,
                             uint32_t          data_len,
                             const void       *data)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_CHANGE_PROPERTY,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_change_property_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.window = window;
    xcb_out.property = property;
    xcb_out.type = type;
    xcb_out.format = format;
    memset(xcb_out.pad0, 0, 3);
    xcb_out.data_len = data_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* void data */
    xcb_parts[4].iov_base = (char *) data;
    xcb_parts[4].iov_len = ((data_len * format) / 8) * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_property (xcb_connection_t *c,
                     uint8_t           mode,
                     xcb_window_t      window,
                     xcb_atom_t        property,
                     xcb_atom_t        type,
                     uint8_t           format,
                     uint32_t          data_len,
                     const void       *data)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_CHANGE_PROPERTY,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_change_property_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.window = window;
    xcb_out.property = property;
    xcb_out.type = type;
    xcb_out.format = format;
    memset(xcb_out.pad0, 0, 3);
    xcb_out.data_len = data_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* void data */
    xcb_parts[4].iov_base = (char *) data;
    xcb_parts[4].iov_len = ((data_len * format) / 8) * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

void *
xcb_change_property_data (const xcb_change_property_request_t *R)
{
    return (void *) (R + 1);
}

int
xcb_change_property_data_length (const xcb_change_property_request_t *R)
{
    return ((R->data_len * R->format) / 8);
}

xcb_generic_iterator_t
xcb_change_property_data_end (const xcb_change_property_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (((R->data_len * R->format) / 8));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_void_cookie_t
xcb_delete_property_checked (xcb_connection_t *c,
                             xcb_window_t      window,
                             xcb_atom_t        property)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_DELETE_PROPERTY,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_delete_property_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.property = property;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_delete_property (xcb_connection_t *c,
                     xcb_window_t      window,
                     xcb_atom_t        property)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_DELETE_PROPERTY,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_delete_property_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.property = property;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_get_property_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_property_reply_t *_aux = (xcb_get_property_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_property_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value */
    xcb_block_len += (_aux->value_len * (_aux->format / 8)) * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_property_cookie_t
xcb_get_property (xcb_connection_t *c,
                  uint8_t           _delete,
                  xcb_window_t      window,
                  xcb_atom_t        property,
                  xcb_atom_t        type,
                  uint32_t          long_offset,
                  uint32_t          long_length)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_PROPERTY,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_property_cookie_t xcb_ret;
    xcb_get_property_request_t xcb_out;

    xcb_out._delete = _delete;
    xcb_out.window = window;
    xcb_out.property = property;
    xcb_out.type = type;
    xcb_out.long_offset = long_offset;
    xcb_out.long_length = long_length;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_property_cookie_t
xcb_get_property_unchecked (xcb_connection_t *c,
                            uint8_t           _delete,
                            xcb_window_t      window,
                            xcb_atom_t        property,
                            xcb_atom_t        type,
                            uint32_t          long_offset,
                            uint32_t          long_length)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_PROPERTY,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_property_cookie_t xcb_ret;
    xcb_get_property_request_t xcb_out;

    xcb_out._delete = _delete;
    xcb_out.window = window;
    xcb_out.property = property;
    xcb_out.type = type;
    xcb_out.long_offset = long_offset;
    xcb_out.long_length = long_length;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

void *
xcb_get_property_value (const xcb_get_property_reply_t *R)
{
    return (void *) (R + 1);
}

int
xcb_get_property_value_length (const xcb_get_property_reply_t *R)
{
    return (R->value_len * (R->format / 8));
}

xcb_generic_iterator_t
xcb_get_property_value_end (const xcb_get_property_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + ((R->value_len * (R->format / 8)));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_property_reply_t *
xcb_get_property_reply (xcb_connection_t           *c,
                        xcb_get_property_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_get_property_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_list_properties_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_list_properties_reply_t *_aux = (xcb_list_properties_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_list_properties_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* atoms */
    xcb_block_len += _aux->atoms_len * sizeof(xcb_atom_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_atom_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_list_properties_cookie_t
xcb_list_properties (xcb_connection_t *c,
                     xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_PROPERTIES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_properties_cookie_t xcb_ret;
    xcb_list_properties_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_list_properties_cookie_t
xcb_list_properties_unchecked (xcb_connection_t *c,
                               xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_PROPERTIES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_properties_cookie_t xcb_ret;
    xcb_list_properties_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_atom_t *
xcb_list_properties_atoms (const xcb_list_properties_reply_t *R)
{
    return (xcb_atom_t *) (R + 1);
}

int
xcb_list_properties_atoms_length (const xcb_list_properties_reply_t *R)
{
    return R->atoms_len;
}

xcb_generic_iterator_t
xcb_list_properties_atoms_end (const xcb_list_properties_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_atom_t *) (R + 1)) + (R->atoms_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_list_properties_reply_t *
xcb_list_properties_reply (xcb_connection_t              *c,
                           xcb_list_properties_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e)
{
    return (xcb_list_properties_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_set_selection_owner_checked (xcb_connection_t *c,
                                 xcb_window_t      owner,
                                 xcb_atom_t        selection,
                                 xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_SELECTION_OWNER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_selection_owner_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.owner = owner;
    xcb_out.selection = selection;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_selection_owner (xcb_connection_t *c,
                         xcb_window_t      owner,
                         xcb_atom_t        selection,
                         xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_SELECTION_OWNER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_selection_owner_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.owner = owner;
    xcb_out.selection = selection;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_selection_owner_cookie_t
xcb_get_selection_owner (xcb_connection_t *c,
                         xcb_atom_t        selection)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_SELECTION_OWNER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_selection_owner_cookie_t xcb_ret;
    xcb_get_selection_owner_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.selection = selection;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_selection_owner_cookie_t
xcb_get_selection_owner_unchecked (xcb_connection_t *c,
                                   xcb_atom_t        selection)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_SELECTION_OWNER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_selection_owner_cookie_t xcb_ret;
    xcb_get_selection_owner_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.selection = selection;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_selection_owner_reply_t *
xcb_get_selection_owner_reply (xcb_connection_t                  *c,
                               xcb_get_selection_owner_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e)
{
    return (xcb_get_selection_owner_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_convert_selection_checked (xcb_connection_t *c,
                               xcb_window_t      requestor,
                               xcb_atom_t        selection,
                               xcb_atom_t        target,
                               xcb_atom_t        property,
                               xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CONVERT_SELECTION,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_convert_selection_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.requestor = requestor;
    xcb_out.selection = selection;
    xcb_out.target = target;
    xcb_out.property = property;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_convert_selection (xcb_connection_t *c,
                       xcb_window_t      requestor,
                       xcb_atom_t        selection,
                       xcb_atom_t        target,
                       xcb_atom_t        property,
                       xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CONVERT_SELECTION,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_convert_selection_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.requestor = requestor;
    xcb_out.selection = selection;
    xcb_out.target = target;
    xcb_out.property = property;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_send_event_checked (xcb_connection_t *c,
                        uint8_t           propagate,
                        xcb_window_t      destination,
                        uint32_t          event_mask,
                        const char       *event)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SEND_EVENT,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_send_event_request_t xcb_out;

    xcb_out.propagate = propagate;
    xcb_out.destination = destination;
    xcb_out.event_mask = event_mask;
    memcpy(xcb_out.event, event, 32);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_send_event (xcb_connection_t *c,
                uint8_t           propagate,
                xcb_window_t      destination,
                uint32_t          event_mask,
                const char       *event)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SEND_EVENT,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_send_event_request_t xcb_out;

    xcb_out.propagate = propagate;
    xcb_out.destination = destination;
    xcb_out.event_mask = event_mask;
    memcpy(xcb_out.event, event, 32);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_grab_pointer_cookie_t
xcb_grab_pointer (xcb_connection_t *c,
                  uint8_t           owner_events,
                  xcb_window_t      grab_window,
                  uint16_t          event_mask,
                  uint8_t           pointer_mode,
                  uint8_t           keyboard_mode,
                  xcb_window_t      confine_to,
                  xcb_cursor_t      cursor,
                  xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_POINTER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_grab_pointer_cookie_t xcb_ret;
    xcb_grab_pointer_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.event_mask = event_mask;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    xcb_out.confine_to = confine_to;
    xcb_out.cursor = cursor;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_grab_pointer_cookie_t
xcb_grab_pointer_unchecked (xcb_connection_t *c,
                            uint8_t           owner_events,
                            xcb_window_t      grab_window,
                            uint16_t          event_mask,
                            uint8_t           pointer_mode,
                            uint8_t           keyboard_mode,
                            xcb_window_t      confine_to,
                            xcb_cursor_t      cursor,
                            xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_POINTER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_grab_pointer_cookie_t xcb_ret;
    xcb_grab_pointer_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.event_mask = event_mask;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    xcb_out.confine_to = confine_to;
    xcb_out.cursor = cursor;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_grab_pointer_reply_t *
xcb_grab_pointer_reply (xcb_connection_t           *c,
                        xcb_grab_pointer_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_grab_pointer_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_ungrab_pointer_checked (xcb_connection_t *c,
                            xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_POINTER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_pointer_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_pointer (xcb_connection_t *c,
                    xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_POINTER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_pointer_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_grab_button_checked (xcb_connection_t *c,
                         uint8_t           owner_events,
                         xcb_window_t      grab_window,
                         uint16_t          event_mask,
                         uint8_t           pointer_mode,
                         uint8_t           keyboard_mode,
                         xcb_window_t      confine_to,
                         xcb_cursor_t      cursor,
                         uint8_t           button,
                         uint16_t          modifiers)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_BUTTON,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_grab_button_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.event_mask = event_mask;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    xcb_out.confine_to = confine_to;
    xcb_out.cursor = cursor;
    xcb_out.button = button;
    xcb_out.pad0 = 0;
    xcb_out.modifiers = modifiers;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_grab_button (xcb_connection_t *c,
                 uint8_t           owner_events,
                 xcb_window_t      grab_window,
                 uint16_t          event_mask,
                 uint8_t           pointer_mode,
                 uint8_t           keyboard_mode,
                 xcb_window_t      confine_to,
                 xcb_cursor_t      cursor,
                 uint8_t           button,
                 uint16_t          modifiers)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_BUTTON,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_grab_button_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.event_mask = event_mask;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    xcb_out.confine_to = confine_to;
    xcb_out.cursor = cursor;
    xcb_out.button = button;
    xcb_out.pad0 = 0;
    xcb_out.modifiers = modifiers;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_button_checked (xcb_connection_t *c,
                           uint8_t           button,
                           xcb_window_t      grab_window,
                           uint16_t          modifiers)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_BUTTON,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_button_request_t xcb_out;

    xcb_out.button = button;
    xcb_out.grab_window = grab_window;
    xcb_out.modifiers = modifiers;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_button (xcb_connection_t *c,
                   uint8_t           button,
                   xcb_window_t      grab_window,
                   uint16_t          modifiers)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_BUTTON,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_button_request_t xcb_out;

    xcb_out.button = button;
    xcb_out.grab_window = grab_window;
    xcb_out.modifiers = modifiers;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_active_pointer_grab_checked (xcb_connection_t *c,
                                        xcb_cursor_t      cursor,
                                        xcb_timestamp_t   time,
                                        uint16_t          event_mask)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CHANGE_ACTIVE_POINTER_GRAB,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_change_active_pointer_grab_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cursor = cursor;
    xcb_out.time = time;
    xcb_out.event_mask = event_mask;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_active_pointer_grab (xcb_connection_t *c,
                                xcb_cursor_t      cursor,
                                xcb_timestamp_t   time,
                                uint16_t          event_mask)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CHANGE_ACTIVE_POINTER_GRAB,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_change_active_pointer_grab_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cursor = cursor;
    xcb_out.time = time;
    xcb_out.event_mask = event_mask;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_grab_keyboard_cookie_t
xcb_grab_keyboard (xcb_connection_t *c,
                   uint8_t           owner_events,
                   xcb_window_t      grab_window,
                   xcb_timestamp_t   time,
                   uint8_t           pointer_mode,
                   uint8_t           keyboard_mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_KEYBOARD,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_grab_keyboard_cookie_t xcb_ret;
    xcb_grab_keyboard_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.time = time;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_grab_keyboard_cookie_t
xcb_grab_keyboard_unchecked (xcb_connection_t *c,
                             uint8_t           owner_events,
                             xcb_window_t      grab_window,
                             xcb_timestamp_t   time,
                             uint8_t           pointer_mode,
                             uint8_t           keyboard_mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_KEYBOARD,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_grab_keyboard_cookie_t xcb_ret;
    xcb_grab_keyboard_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.time = time;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_grab_keyboard_reply_t *
xcb_grab_keyboard_reply (xcb_connection_t            *c,
                         xcb_grab_keyboard_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e)
{
    return (xcb_grab_keyboard_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_ungrab_keyboard_checked (xcb_connection_t *c,
                             xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_KEYBOARD,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_keyboard_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_keyboard (xcb_connection_t *c,
                     xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_KEYBOARD,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_keyboard_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_grab_key_checked (xcb_connection_t *c,
                      uint8_t           owner_events,
                      xcb_window_t      grab_window,
                      uint16_t          modifiers,
                      xcb_keycode_t     key,
                      uint8_t           pointer_mode,
                      uint8_t           keyboard_mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_KEY,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_grab_key_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.modifiers = modifiers;
    xcb_out.key = key;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    memset(xcb_out.pad0, 0, 3);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_grab_key (xcb_connection_t *c,
              uint8_t           owner_events,
              xcb_window_t      grab_window,
              uint16_t          modifiers,
              xcb_keycode_t     key,
              uint8_t           pointer_mode,
              uint8_t           keyboard_mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_KEY,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_grab_key_request_t xcb_out;

    xcb_out.owner_events = owner_events;
    xcb_out.grab_window = grab_window;
    xcb_out.modifiers = modifiers;
    xcb_out.key = key;
    xcb_out.pointer_mode = pointer_mode;
    xcb_out.keyboard_mode = keyboard_mode;
    memset(xcb_out.pad0, 0, 3);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_key_checked (xcb_connection_t *c,
                        xcb_keycode_t     key,
                        xcb_window_t      grab_window,
                        uint16_t          modifiers)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_KEY,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_key_request_t xcb_out;

    xcb_out.key = key;
    xcb_out.grab_window = grab_window;
    xcb_out.modifiers = modifiers;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_key (xcb_connection_t *c,
                xcb_keycode_t     key,
                xcb_window_t      grab_window,
                uint16_t          modifiers)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_KEY,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_key_request_t xcb_out;

    xcb_out.key = key;
    xcb_out.grab_window = grab_window;
    xcb_out.modifiers = modifiers;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_allow_events_checked (xcb_connection_t *c,
                          uint8_t           mode,
                          xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOW_EVENTS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_allow_events_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_allow_events (xcb_connection_t *c,
                  uint8_t           mode,
                  xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOW_EVENTS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_allow_events_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_grab_server_checked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_SERVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_grab_server_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_grab_server (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GRAB_SERVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_grab_server_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_server_checked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_SERVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_server_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_ungrab_server (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNGRAB_SERVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_ungrab_server_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_pointer_cookie_t
xcb_query_pointer (xcb_connection_t *c,
                   xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_POINTER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_pointer_cookie_t xcb_ret;
    xcb_query_pointer_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_pointer_cookie_t
xcb_query_pointer_unchecked (xcb_connection_t *c,
                             xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_POINTER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_pointer_cookie_t xcb_ret;
    xcb_query_pointer_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_pointer_reply_t *
xcb_query_pointer_reply (xcb_connection_t            *c,
                         xcb_query_pointer_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e)
{
    return (xcb_query_pointer_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

void
xcb_timecoord_next (xcb_timecoord_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_timecoord_t);
}

xcb_generic_iterator_t
xcb_timecoord_end (xcb_timecoord_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_get_motion_events_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_motion_events_reply_t *_aux = (xcb_get_motion_events_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_motion_events_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* events */
    xcb_block_len += _aux->events_len * sizeof(xcb_timecoord_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_timecoord_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_motion_events_cookie_t
xcb_get_motion_events (xcb_connection_t *c,
                       xcb_window_t      window,
                       xcb_timestamp_t   start,
                       xcb_timestamp_t   stop)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_MOTION_EVENTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_motion_events_cookie_t xcb_ret;
    xcb_get_motion_events_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.start = start;
    xcb_out.stop = stop;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_motion_events_cookie_t
xcb_get_motion_events_unchecked (xcb_connection_t *c,
                                 xcb_window_t      window,
                                 xcb_timestamp_t   start,
                                 xcb_timestamp_t   stop)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_MOTION_EVENTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_motion_events_cookie_t xcb_ret;
    xcb_get_motion_events_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.start = start;
    xcb_out.stop = stop;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_timecoord_t *
xcb_get_motion_events_events (const xcb_get_motion_events_reply_t *R)
{
    return (xcb_timecoord_t *) (R + 1);
}

int
xcb_get_motion_events_events_length (const xcb_get_motion_events_reply_t *R)
{
    return R->events_len;
}

xcb_timecoord_iterator_t
xcb_get_motion_events_events_iterator (const xcb_get_motion_events_reply_t *R)
{
    xcb_timecoord_iterator_t i;
    i.data = (xcb_timecoord_t *) (R + 1);
    i.rem = R->events_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_motion_events_reply_t *
xcb_get_motion_events_reply (xcb_connection_t                *c,
                             xcb_get_motion_events_cookie_t   cookie  /**< */,
                             xcb_generic_error_t            **e)
{
    return (xcb_get_motion_events_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_translate_coordinates_cookie_t
xcb_translate_coordinates (xcb_connection_t *c,
                           xcb_window_t      src_window,
                           xcb_window_t      dst_window,
                           int16_t           src_x,
                           int16_t           src_y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_TRANSLATE_COORDINATES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_translate_coordinates_cookie_t xcb_ret;
    xcb_translate_coordinates_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_window = src_window;
    xcb_out.dst_window = dst_window;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_translate_coordinates_cookie_t
xcb_translate_coordinates_unchecked (xcb_connection_t *c,
                                     xcb_window_t      src_window,
                                     xcb_window_t      dst_window,
                                     int16_t           src_x,
                                     int16_t           src_y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_TRANSLATE_COORDINATES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_translate_coordinates_cookie_t xcb_ret;
    xcb_translate_coordinates_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_window = src_window;
    xcb_out.dst_window = dst_window;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_translate_coordinates_reply_t *
xcb_translate_coordinates_reply (xcb_connection_t                    *c,
                                 xcb_translate_coordinates_cookie_t   cookie  /**< */,
                                 xcb_generic_error_t                **e)
{
    return (xcb_translate_coordinates_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_warp_pointer_checked (xcb_connection_t *c,
                          xcb_window_t      src_window,
                          xcb_window_t      dst_window,
                          int16_t           src_x,
                          int16_t           src_y,
                          uint16_t          src_width,
                          uint16_t          src_height,
                          int16_t           dst_x,
                          int16_t           dst_y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_WARP_POINTER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_warp_pointer_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_window = src_window;
    xcb_out.dst_window = dst_window;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;
    xcb_out.src_width = src_width;
    xcb_out.src_height = src_height;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_warp_pointer (xcb_connection_t *c,
                  xcb_window_t      src_window,
                  xcb_window_t      dst_window,
                  int16_t           src_x,
                  int16_t           src_y,
                  uint16_t          src_width,
                  uint16_t          src_height,
                  int16_t           dst_x,
                  int16_t           dst_y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_WARP_POINTER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_warp_pointer_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_window = src_window;
    xcb_out.dst_window = dst_window;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;
    xcb_out.src_width = src_width;
    xcb_out.src_height = src_height;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_input_focus_checked (xcb_connection_t *c,
                             uint8_t           revert_to,
                             xcb_window_t      focus,
                             xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_INPUT_FOCUS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_input_focus_request_t xcb_out;

    xcb_out.revert_to = revert_to;
    xcb_out.focus = focus;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_input_focus (xcb_connection_t *c,
                     uint8_t           revert_to,
                     xcb_window_t      focus,
                     xcb_timestamp_t   time)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_INPUT_FOCUS,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_input_focus_request_t xcb_out;

    xcb_out.revert_to = revert_to;
    xcb_out.focus = focus;
    xcb_out.time = time;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_input_focus_cookie_t
xcb_get_input_focus (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_INPUT_FOCUS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_input_focus_cookie_t xcb_ret;
    xcb_get_input_focus_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_input_focus_cookie_t
xcb_get_input_focus_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_INPUT_FOCUS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_input_focus_cookie_t xcb_ret;
    xcb_get_input_focus_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_input_focus_reply_t *
xcb_get_input_focus_reply (xcb_connection_t              *c,
                           xcb_get_input_focus_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e)
{
    return (xcb_get_input_focus_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_query_keymap_cookie_t
xcb_query_keymap (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_KEYMAP,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_keymap_cookie_t xcb_ret;
    xcb_query_keymap_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_keymap_cookie_t
xcb_query_keymap_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_KEYMAP,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_keymap_cookie_t xcb_ret;
    xcb_query_keymap_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_keymap_reply_t *
xcb_query_keymap_reply (xcb_connection_t           *c,
                        xcb_query_keymap_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_query_keymap_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_open_font_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_open_font_request_t *_aux = (xcb_open_font_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_open_font_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_open_font_checked (xcb_connection_t *c,
                       xcb_font_t        fid,
                       uint16_t          name_len,
                       const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_OPEN_FONT,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_open_font_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.fid = fid;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_open_font (xcb_connection_t *c,
               xcb_font_t        fid,
               uint16_t          name_len,
               const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_OPEN_FONT,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_open_font_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.fid = fid;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

char *
xcb_open_font_name (const xcb_open_font_request_t *R)
{
    return (char *) (R + 1);
}

int
xcb_open_font_name_length (const xcb_open_font_request_t *R)
{
    return R->name_len;
}

xcb_generic_iterator_t
xcb_open_font_name_end (const xcb_open_font_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->name_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_void_cookie_t
xcb_close_font_checked (xcb_connection_t *c,
                        xcb_font_t        font)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CLOSE_FONT,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_close_font_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.font = font;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_close_font (xcb_connection_t *c,
                xcb_font_t        font)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CLOSE_FONT,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_close_font_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.font = font;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

void
xcb_fontprop_next (xcb_fontprop_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_fontprop_t);
}

xcb_generic_iterator_t
xcb_fontprop_end (xcb_fontprop_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

void
xcb_charinfo_next (xcb_charinfo_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_charinfo_t);
}

xcb_generic_iterator_t
xcb_charinfo_end (xcb_charinfo_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_query_font_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_query_font_reply_t *_aux = (xcb_query_font_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_query_font_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* properties */
    xcb_block_len += _aux->properties_len * sizeof(xcb_fontprop_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_fontprop_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* char_infos */
    xcb_block_len += _aux->char_infos_len * sizeof(xcb_charinfo_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_charinfo_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_query_font_cookie_t
xcb_query_font (xcb_connection_t *c,
                xcb_fontable_t    font)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_FONT,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_font_cookie_t xcb_ret;
    xcb_query_font_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.font = font;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_font_cookie_t
xcb_query_font_unchecked (xcb_connection_t *c,
                          xcb_fontable_t    font)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_FONT,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_font_cookie_t xcb_ret;
    xcb_query_font_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.font = font;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_fontprop_t *
xcb_query_font_properties (const xcb_query_font_reply_t *R)
{
    return (xcb_fontprop_t *) (R + 1);
}

int
xcb_query_font_properties_length (const xcb_query_font_reply_t *R)
{
    return R->properties_len;
}

xcb_fontprop_iterator_t
xcb_query_font_properties_iterator (const xcb_query_font_reply_t *R)
{
    xcb_fontprop_iterator_t i;
    i.data = (xcb_fontprop_t *) (R + 1);
    i.rem = R->properties_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_charinfo_t *
xcb_query_font_char_infos (const xcb_query_font_reply_t *R)
{
    xcb_generic_iterator_t prev = xcb_fontprop_end(xcb_query_font_properties_iterator(R));
    return (xcb_charinfo_t *) ((char *) prev.data + XCB_TYPE_PAD(xcb_charinfo_t, prev.index) + 0);
}

int
xcb_query_font_char_infos_length (const xcb_query_font_reply_t *R)
{
    return R->char_infos_len;
}

xcb_charinfo_iterator_t
xcb_query_font_char_infos_iterator (const xcb_query_font_reply_t *R)
{
    xcb_charinfo_iterator_t i;
    xcb_generic_iterator_t prev = xcb_fontprop_end(xcb_query_font_properties_iterator(R));
    i.data = (xcb_charinfo_t *) ((char *) prev.data + XCB_TYPE_PAD(xcb_charinfo_t, prev.index));
    i.rem = R->char_infos_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_query_font_reply_t *
xcb_query_font_reply (xcb_connection_t         *c,
                      xcb_query_font_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e)
{
    return (xcb_query_font_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_query_text_extents_sizeof (const void  *_buffer,
                               uint32_t     string_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_query_text_extents_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* string */
    xcb_block_len += string_len * sizeof(xcb_char2b_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_char2b_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_query_text_extents_cookie_t
xcb_query_text_extents (xcb_connection_t   *c,
                        xcb_fontable_t      font,
                        uint32_t            string_len,
                        const xcb_char2b_t *string)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_QUERY_TEXT_EXTENTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_query_text_extents_cookie_t xcb_ret;
    xcb_query_text_extents_request_t xcb_out;

    xcb_out.odd_length = (string_len & 1);
    xcb_out.font = font;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_char2b_t string */
    xcb_parts[4].iov_base = (char *) string;
    xcb_parts[4].iov_len = string_len * sizeof(xcb_char2b_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_text_extents_cookie_t
xcb_query_text_extents_unchecked (xcb_connection_t   *c,
                                  xcb_fontable_t      font,
                                  uint32_t            string_len,
                                  const xcb_char2b_t *string)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_QUERY_TEXT_EXTENTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_query_text_extents_cookie_t xcb_ret;
    xcb_query_text_extents_request_t xcb_out;

    xcb_out.odd_length = (string_len & 1);
    xcb_out.font = font;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_char2b_t string */
    xcb_parts[4].iov_base = (char *) string;
    xcb_parts[4].iov_len = string_len * sizeof(xcb_char2b_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_text_extents_reply_t *
xcb_query_text_extents_reply (xcb_connection_t                 *c,
                              xcb_query_text_extents_cookie_t   cookie  /**< */,
                              xcb_generic_error_t             **e)
{
    return (xcb_query_text_extents_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_str_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_str_t *_aux = (xcb_str_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_str_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

char *
xcb_str_name (const xcb_str_t *R)
{
    return (char *) (R + 1);
}

int
xcb_str_name_length (const xcb_str_t *R)
{
    return R->name_len;
}

xcb_generic_iterator_t
xcb_str_name_end (const xcb_str_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->name_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_str_next (xcb_str_iterator_t *i)
{
    xcb_str_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_str_t *)(((char *)R) + xcb_str_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_str_t *) child.data;
}

xcb_generic_iterator_t
xcb_str_end (xcb_str_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_str_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_list_fonts_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_list_fonts_request_t *_aux = (xcb_list_fonts_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_list_fonts_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* pattern */
    xcb_block_len += _aux->pattern_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_list_fonts_cookie_t
xcb_list_fonts (xcb_connection_t *c,
                uint16_t          max_names,
                uint16_t          pattern_len,
                const char       *pattern)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_LIST_FONTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_list_fonts_cookie_t xcb_ret;
    xcb_list_fonts_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.max_names = max_names;
    xcb_out.pattern_len = pattern_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char pattern */
    xcb_parts[4].iov_base = (char *) pattern;
    xcb_parts[4].iov_len = pattern_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_list_fonts_cookie_t
xcb_list_fonts_unchecked (xcb_connection_t *c,
                          uint16_t          max_names,
                          uint16_t          pattern_len,
                          const char       *pattern)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_LIST_FONTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_list_fonts_cookie_t xcb_ret;
    xcb_list_fonts_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.max_names = max_names;
    xcb_out.pattern_len = pattern_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char pattern */
    xcb_parts[4].iov_base = (char *) pattern;
    xcb_parts[4].iov_len = pattern_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_list_fonts_names_length (const xcb_list_fonts_reply_t *R)
{
    return R->names_len;
}

xcb_str_iterator_t
xcb_list_fonts_names_iterator (const xcb_list_fonts_reply_t *R)
{
    xcb_str_iterator_t i;
    i.data = (xcb_str_t *) (R + 1);
    i.rem = R->names_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_list_fonts_reply_t *
xcb_list_fonts_reply (xcb_connection_t         *c,
                      xcb_list_fonts_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e)
{
    return (xcb_list_fonts_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_list_fonts_with_info_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_list_fonts_with_info_request_t *_aux = (xcb_list_fonts_with_info_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_list_fonts_with_info_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* pattern */
    xcb_block_len += _aux->pattern_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_list_fonts_with_info_cookie_t
xcb_list_fonts_with_info (xcb_connection_t *c,
                          uint16_t          max_names,
                          uint16_t          pattern_len,
                          const char       *pattern)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_LIST_FONTS_WITH_INFO,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_list_fonts_with_info_cookie_t xcb_ret;
    xcb_list_fonts_with_info_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.max_names = max_names;
    xcb_out.pattern_len = pattern_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char pattern */
    xcb_parts[4].iov_base = (char *) pattern;
    xcb_parts[4].iov_len = pattern_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_list_fonts_with_info_cookie_t
xcb_list_fonts_with_info_unchecked (xcb_connection_t *c,
                                    uint16_t          max_names,
                                    uint16_t          pattern_len,
                                    const char       *pattern)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_LIST_FONTS_WITH_INFO,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_list_fonts_with_info_cookie_t xcb_ret;
    xcb_list_fonts_with_info_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.max_names = max_names;
    xcb_out.pattern_len = pattern_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char pattern */
    xcb_parts[4].iov_base = (char *) pattern;
    xcb_parts[4].iov_len = pattern_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_fontprop_t *
xcb_list_fonts_with_info_properties (const xcb_list_fonts_with_info_reply_t *R)
{
    return (xcb_fontprop_t *) (R + 1);
}

int
xcb_list_fonts_with_info_properties_length (const xcb_list_fonts_with_info_reply_t *R)
{
    return R->properties_len;
}

xcb_fontprop_iterator_t
xcb_list_fonts_with_info_properties_iterator (const xcb_list_fonts_with_info_reply_t *R)
{
    xcb_fontprop_iterator_t i;
    i.data = (xcb_fontprop_t *) (R + 1);
    i.rem = R->properties_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

char *
xcb_list_fonts_with_info_name (const xcb_list_fonts_with_info_reply_t *R)
{
    xcb_generic_iterator_t prev = xcb_fontprop_end(xcb_list_fonts_with_info_properties_iterator(R));
    return (char *) ((char *) prev.data + XCB_TYPE_PAD(char, prev.index) + 0);
}

int
xcb_list_fonts_with_info_name_length (const xcb_list_fonts_with_info_reply_t *R)
{
    return R->name_len;
}

xcb_generic_iterator_t
xcb_list_fonts_with_info_name_end (const xcb_list_fonts_with_info_reply_t *R)
{
    xcb_generic_iterator_t i;
    xcb_generic_iterator_t prev = xcb_fontprop_end(xcb_list_fonts_with_info_properties_iterator(R));
    i.data = ((char *) ((char*) prev.data + XCB_TYPE_PAD(char, prev.index))) + (R->name_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_list_fonts_with_info_reply_t *
xcb_list_fonts_with_info_reply (xcb_connection_t                   *c,
                                xcb_list_fonts_with_info_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e)
{
    return (xcb_list_fonts_with_info_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_set_font_path_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_set_font_path_request_t *_aux = (xcb_set_font_path_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;

    unsigned int i;
    unsigned int xcb_tmp_len;

    xcb_block_len += sizeof(xcb_set_font_path_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* font */
    for(i=0; i<_aux->font_qty; i++) {
        xcb_tmp_len = xcb_str_sizeof(xcb_tmp);
        xcb_block_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_align_to = ALIGNOF(xcb_str_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_set_font_path_checked (xcb_connection_t *c,
                           uint16_t          font_qty,
                           const xcb_str_t  *font)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_FONT_PATH,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_set_font_path_request_t xcb_out;
    unsigned int xcb_tmp_len;
    char *xcb_tmp;
    unsigned int i;

    xcb_out.pad0 = 0;
    xcb_out.font_qty = font_qty;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_str_t font */
    xcb_parts[4].iov_base = (char *) font;
    xcb_parts[4].iov_len = 0;
    xcb_tmp = (char *)font;
    for(i=0; i<font_qty; i++) {
        xcb_tmp_len = xcb_str_sizeof(xcb_tmp);
        xcb_parts[4].iov_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_font_path (xcb_connection_t *c,
                   uint16_t          font_qty,
                   const xcb_str_t  *font)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_FONT_PATH,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_set_font_path_request_t xcb_out;
    unsigned int xcb_tmp_len;
    char *xcb_tmp;
    unsigned int i;

    xcb_out.pad0 = 0;
    xcb_out.font_qty = font_qty;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_str_t font */
    xcb_parts[4].iov_base = (char *) font;
    xcb_parts[4].iov_len = 0;
    xcb_tmp = (char *)font;
    for(i=0; i<font_qty; i++) {
        xcb_tmp_len = xcb_str_sizeof(xcb_tmp);
        xcb_parts[4].iov_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_set_font_path_font_length (const xcb_set_font_path_request_t *R)
{
    return R->font_qty;
}

xcb_str_iterator_t
xcb_set_font_path_font_iterator (const xcb_set_font_path_request_t *R)
{
    xcb_str_iterator_t i;
    i.data = (xcb_str_t *) (R + 1);
    i.rem = R->font_qty;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_get_font_path_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_font_path_reply_t *_aux = (xcb_get_font_path_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;

    unsigned int i;
    unsigned int xcb_tmp_len;

    xcb_block_len += sizeof(xcb_get_font_path_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* path */
    for(i=0; i<_aux->path_len; i++) {
        xcb_tmp_len = xcb_str_sizeof(xcb_tmp);
        xcb_block_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_align_to = ALIGNOF(xcb_str_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_font_path_cookie_t
xcb_get_font_path (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_FONT_PATH,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_font_path_cookie_t xcb_ret;
    xcb_get_font_path_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_font_path_cookie_t
xcb_get_font_path_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_FONT_PATH,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_font_path_cookie_t xcb_ret;
    xcb_get_font_path_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_get_font_path_path_length (const xcb_get_font_path_reply_t *R)
{
    return R->path_len;
}

xcb_str_iterator_t
xcb_get_font_path_path_iterator (const xcb_get_font_path_reply_t *R)
{
    xcb_str_iterator_t i;
    i.data = (xcb_str_t *) (R + 1);
    i.rem = R->path_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_font_path_reply_t *
xcb_get_font_path_reply (xcb_connection_t            *c,
                         xcb_get_font_path_cookie_t   cookie  /**< */,
                         xcb_generic_error_t        **e)
{
    return (xcb_get_font_path_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_create_pixmap_checked (xcb_connection_t *c,
                           uint8_t           depth,
                           xcb_pixmap_t      pid,
                           xcb_drawable_t    drawable,
                           uint16_t          width,
                           uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_PIXMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_pixmap_request_t xcb_out;

    xcb_out.depth = depth;
    xcb_out.pid = pid;
    xcb_out.drawable = drawable;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_pixmap (xcb_connection_t *c,
                   uint8_t           depth,
                   xcb_pixmap_t      pid,
                   xcb_drawable_t    drawable,
                   uint16_t          width,
                   uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_PIXMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_pixmap_request_t xcb_out;

    xcb_out.depth = depth;
    xcb_out.pid = pid;
    xcb_out.drawable = drawable;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_pixmap_checked (xcb_connection_t *c,
                         xcb_pixmap_t      pixmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_PIXMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_pixmap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.pixmap = pixmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_pixmap (xcb_connection_t *c,
                 xcb_pixmap_t      pixmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_PIXMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_pixmap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.pixmap = pixmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_create_gc_value_list_serialize (void                             **_buffer,
                                    uint32_t                           value_mask,
                                    const xcb_create_gc_value_list_t  *_aux)
{
    char *xcb_out = *_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;

    unsigned int xcb_pad = 0;
    char xcb_pad0[3] = {0, 0, 0};
    struct iovec xcb_parts[24];
    unsigned int xcb_parts_idx = 0;
    unsigned int xcb_block_len = 0;
    unsigned int i;
    char *xcb_tmp;

    if(value_mask & XCB_GC_FUNCTION) {
        /* xcb_create_gc_value_list_t.function */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->function;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_PLANE_MASK) {
        /* xcb_create_gc_value_list_t.plane_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->plane_mask;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FOREGROUND) {
        /* xcb_create_gc_value_list_t.foreground */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->foreground;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_BACKGROUND) {
        /* xcb_create_gc_value_list_t.background */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->background;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_WIDTH) {
        /* xcb_create_gc_value_list_t.line_width */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->line_width;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_STYLE) {
        /* xcb_create_gc_value_list_t.line_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->line_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_CAP_STYLE) {
        /* xcb_create_gc_value_list_t.cap_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->cap_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_JOIN_STYLE) {
        /* xcb_create_gc_value_list_t.join_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->join_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_STYLE) {
        /* xcb_create_gc_value_list_t.fill_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->fill_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_RULE) {
        /* xcb_create_gc_value_list_t.fill_rule */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->fill_rule;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_TILE) {
        /* xcb_create_gc_value_list_t.tile */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->tile;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_STIPPLE) {
        /* xcb_create_gc_value_list_t.stipple */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->stipple;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_X) {
        /* xcb_create_gc_value_list_t.tile_stipple_x_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->tile_stipple_x_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_Y) {
        /* xcb_create_gc_value_list_t.tile_stipple_y_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->tile_stipple_y_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_FONT) {
        /* xcb_create_gc_value_list_t.font */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->font;
        xcb_block_len += sizeof(xcb_font_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_font_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_font_t);
    }
    if(value_mask & XCB_GC_SUBWINDOW_MODE) {
        /* xcb_create_gc_value_list_t.subwindow_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->subwindow_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_GRAPHICS_EXPOSURES) {
        /* xcb_create_gc_value_list_t.graphics_exposures */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->graphics_exposures;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_bool32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_X) {
        /* xcb_create_gc_value_list_t.clip_x_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->clip_x_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_Y) {
        /* xcb_create_gc_value_list_t.clip_y_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->clip_y_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_MASK) {
        /* xcb_create_gc_value_list_t.clip_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->clip_mask;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_DASH_OFFSET) {
        /* xcb_create_gc_value_list_t.dash_offset */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->dash_offset;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_DASH_LIST) {
        /* xcb_create_gc_value_list_t.dashes */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->dashes;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_ARC_MODE) {
        /* xcb_create_gc_value_list_t.arc_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->arc_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_parts[xcb_parts_idx].iov_base = xcb_pad0;
        xcb_parts[xcb_parts_idx].iov_len = xcb_pad;
        xcb_parts_idx++;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    if (NULL == xcb_out) {
        /* allocate memory */
        xcb_out = malloc(xcb_buffer_len);
        *_buffer = xcb_out;
    }

    xcb_tmp = xcb_out;
    for(i=0; i<xcb_parts_idx; i++) {
        if (0 != xcb_parts[i].iov_base && 0 != xcb_parts[i].iov_len)
            memcpy(xcb_tmp, xcb_parts[i].iov_base, xcb_parts[i].iov_len);
        if (0 != xcb_parts[i].iov_len)
            xcb_tmp += xcb_parts[i].iov_len;
    }

    return xcb_buffer_len;
}

int
xcb_create_gc_value_list_unpack (const void                  *_buffer,
                                 uint32_t                     value_mask,
                                 xcb_create_gc_value_list_t  *_aux)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;


    if(value_mask & XCB_GC_FUNCTION) {
        /* xcb_create_gc_value_list_t.function */
        _aux->function = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_PLANE_MASK) {
        /* xcb_create_gc_value_list_t.plane_mask */
        _aux->plane_mask = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FOREGROUND) {
        /* xcb_create_gc_value_list_t.foreground */
        _aux->foreground = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_BACKGROUND) {
        /* xcb_create_gc_value_list_t.background */
        _aux->background = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_WIDTH) {
        /* xcb_create_gc_value_list_t.line_width */
        _aux->line_width = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_STYLE) {
        /* xcb_create_gc_value_list_t.line_style */
        _aux->line_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_CAP_STYLE) {
        /* xcb_create_gc_value_list_t.cap_style */
        _aux->cap_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_JOIN_STYLE) {
        /* xcb_create_gc_value_list_t.join_style */
        _aux->join_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_STYLE) {
        /* xcb_create_gc_value_list_t.fill_style */
        _aux->fill_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_RULE) {
        /* xcb_create_gc_value_list_t.fill_rule */
        _aux->fill_rule = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_TILE) {
        /* xcb_create_gc_value_list_t.tile */
        _aux->tile = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_STIPPLE) {
        /* xcb_create_gc_value_list_t.stipple */
        _aux->stipple = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_X) {
        /* xcb_create_gc_value_list_t.tile_stipple_x_origin */
        _aux->tile_stipple_x_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_Y) {
        /* xcb_create_gc_value_list_t.tile_stipple_y_origin */
        _aux->tile_stipple_y_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_FONT) {
        /* xcb_create_gc_value_list_t.font */
        _aux->font = *(xcb_font_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_font_t);
        xcb_tmp += sizeof(xcb_font_t);
        xcb_align_to = ALIGNOF(xcb_font_t);
    }
    if(value_mask & XCB_GC_SUBWINDOW_MODE) {
        /* xcb_create_gc_value_list_t.subwindow_mode */
        _aux->subwindow_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_GRAPHICS_EXPOSURES) {
        /* xcb_create_gc_value_list_t.graphics_exposures */
        _aux->graphics_exposures = *(xcb_bool32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_tmp += sizeof(xcb_bool32_t);
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_X) {
        /* xcb_create_gc_value_list_t.clip_x_origin */
        _aux->clip_x_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_Y) {
        /* xcb_create_gc_value_list_t.clip_y_origin */
        _aux->clip_y_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_MASK) {
        /* xcb_create_gc_value_list_t.clip_mask */
        _aux->clip_mask = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_DASH_OFFSET) {
        /* xcb_create_gc_value_list_t.dash_offset */
        _aux->dash_offset = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_DASH_LIST) {
        /* xcb_create_gc_value_list_t.dashes */
        _aux->dashes = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_ARC_MODE) {
        /* xcb_create_gc_value_list_t.arc_mode */
        _aux->arc_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    return xcb_buffer_len;
}

int
xcb_create_gc_value_list_sizeof (const void  *_buffer,
                                 uint32_t     value_mask)
{
    xcb_create_gc_value_list_t _aux;
    return xcb_create_gc_value_list_unpack(_buffer, value_mask, &_aux);
}

int
xcb_create_gc_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_create_gc_request_t *_aux = (xcb_create_gc_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_create_gc_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value_list */
    xcb_block_len += xcb_create_gc_value_list_sizeof(xcb_tmp, _aux->value_mask);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_create_gc_checked (xcb_connection_t *c,
                       xcb_gcontext_t    cid,
                       xcb_drawable_t    drawable,
                       uint32_t          value_mask,
                       const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.drawable = drawable;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_gc_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_create_gc_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_gc (xcb_connection_t *c,
               xcb_gcontext_t    cid,
               xcb_drawable_t    drawable,
               uint32_t          value_mask,
               const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.drawable = drawable;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_gc_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_create_gc_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_gc_aux_checked (xcb_connection_t                 *c,
                           xcb_gcontext_t                    cid,
                           xcb_drawable_t                    drawable,
                           uint32_t                          value_mask,
                           const xcb_create_gc_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_gc_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.drawable = drawable;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_gc_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_create_gc_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_gc_aux (xcb_connection_t                 *c,
                   xcb_gcontext_t                    cid,
                   xcb_drawable_t                    drawable,
                   uint32_t                          value_mask,
                   const xcb_create_gc_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CREATE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_create_gc_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.drawable = drawable;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_create_gc_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_create_gc_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

void *
xcb_create_gc_value_list (const xcb_create_gc_request_t *R)
{
    return (void *) (R + 1);
}

int
xcb_change_gc_value_list_serialize (void                             **_buffer,
                                    uint32_t                           value_mask,
                                    const xcb_change_gc_value_list_t  *_aux)
{
    char *xcb_out = *_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;

    unsigned int xcb_pad = 0;
    char xcb_pad0[3] = {0, 0, 0};
    struct iovec xcb_parts[24];
    unsigned int xcb_parts_idx = 0;
    unsigned int xcb_block_len = 0;
    unsigned int i;
    char *xcb_tmp;

    if(value_mask & XCB_GC_FUNCTION) {
        /* xcb_change_gc_value_list_t.function */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->function;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_PLANE_MASK) {
        /* xcb_change_gc_value_list_t.plane_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->plane_mask;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FOREGROUND) {
        /* xcb_change_gc_value_list_t.foreground */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->foreground;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_BACKGROUND) {
        /* xcb_change_gc_value_list_t.background */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->background;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_WIDTH) {
        /* xcb_change_gc_value_list_t.line_width */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->line_width;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_STYLE) {
        /* xcb_change_gc_value_list_t.line_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->line_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_CAP_STYLE) {
        /* xcb_change_gc_value_list_t.cap_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->cap_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_JOIN_STYLE) {
        /* xcb_change_gc_value_list_t.join_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->join_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_STYLE) {
        /* xcb_change_gc_value_list_t.fill_style */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->fill_style;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_RULE) {
        /* xcb_change_gc_value_list_t.fill_rule */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->fill_rule;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_TILE) {
        /* xcb_change_gc_value_list_t.tile */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->tile;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_STIPPLE) {
        /* xcb_change_gc_value_list_t.stipple */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->stipple;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_X) {
        /* xcb_change_gc_value_list_t.tile_stipple_x_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->tile_stipple_x_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_Y) {
        /* xcb_change_gc_value_list_t.tile_stipple_y_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->tile_stipple_y_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_FONT) {
        /* xcb_change_gc_value_list_t.font */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->font;
        xcb_block_len += sizeof(xcb_font_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_font_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_font_t);
    }
    if(value_mask & XCB_GC_SUBWINDOW_MODE) {
        /* xcb_change_gc_value_list_t.subwindow_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->subwindow_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_GRAPHICS_EXPOSURES) {
        /* xcb_change_gc_value_list_t.graphics_exposures */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->graphics_exposures;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_bool32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_X) {
        /* xcb_change_gc_value_list_t.clip_x_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->clip_x_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_Y) {
        /* xcb_change_gc_value_list_t.clip_y_origin */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->clip_y_origin;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_MASK) {
        /* xcb_change_gc_value_list_t.clip_mask */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->clip_mask;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_pixmap_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_DASH_OFFSET) {
        /* xcb_change_gc_value_list_t.dash_offset */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->dash_offset;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_DASH_LIST) {
        /* xcb_change_gc_value_list_t.dashes */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->dashes;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_ARC_MODE) {
        /* xcb_change_gc_value_list_t.arc_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->arc_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_parts[xcb_parts_idx].iov_base = xcb_pad0;
        xcb_parts[xcb_parts_idx].iov_len = xcb_pad;
        xcb_parts_idx++;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    if (NULL == xcb_out) {
        /* allocate memory */
        xcb_out = malloc(xcb_buffer_len);
        *_buffer = xcb_out;
    }

    xcb_tmp = xcb_out;
    for(i=0; i<xcb_parts_idx; i++) {
        if (0 != xcb_parts[i].iov_base && 0 != xcb_parts[i].iov_len)
            memcpy(xcb_tmp, xcb_parts[i].iov_base, xcb_parts[i].iov_len);
        if (0 != xcb_parts[i].iov_len)
            xcb_tmp += xcb_parts[i].iov_len;
    }

    return xcb_buffer_len;
}

int
xcb_change_gc_value_list_unpack (const void                  *_buffer,
                                 uint32_t                     value_mask,
                                 xcb_change_gc_value_list_t  *_aux)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;


    if(value_mask & XCB_GC_FUNCTION) {
        /* xcb_change_gc_value_list_t.function */
        _aux->function = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_PLANE_MASK) {
        /* xcb_change_gc_value_list_t.plane_mask */
        _aux->plane_mask = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FOREGROUND) {
        /* xcb_change_gc_value_list_t.foreground */
        _aux->foreground = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_BACKGROUND) {
        /* xcb_change_gc_value_list_t.background */
        _aux->background = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_WIDTH) {
        /* xcb_change_gc_value_list_t.line_width */
        _aux->line_width = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_LINE_STYLE) {
        /* xcb_change_gc_value_list_t.line_style */
        _aux->line_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_CAP_STYLE) {
        /* xcb_change_gc_value_list_t.cap_style */
        _aux->cap_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_JOIN_STYLE) {
        /* xcb_change_gc_value_list_t.join_style */
        _aux->join_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_STYLE) {
        /* xcb_change_gc_value_list_t.fill_style */
        _aux->fill_style = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_FILL_RULE) {
        /* xcb_change_gc_value_list_t.fill_rule */
        _aux->fill_rule = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_TILE) {
        /* xcb_change_gc_value_list_t.tile */
        _aux->tile = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_STIPPLE) {
        /* xcb_change_gc_value_list_t.stipple */
        _aux->stipple = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_X) {
        /* xcb_change_gc_value_list_t.tile_stipple_x_origin */
        _aux->tile_stipple_x_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_TILE_STIPPLE_ORIGIN_Y) {
        /* xcb_change_gc_value_list_t.tile_stipple_y_origin */
        _aux->tile_stipple_y_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_FONT) {
        /* xcb_change_gc_value_list_t.font */
        _aux->font = *(xcb_font_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_font_t);
        xcb_tmp += sizeof(xcb_font_t);
        xcb_align_to = ALIGNOF(xcb_font_t);
    }
    if(value_mask & XCB_GC_SUBWINDOW_MODE) {
        /* xcb_change_gc_value_list_t.subwindow_mode */
        _aux->subwindow_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_GRAPHICS_EXPOSURES) {
        /* xcb_change_gc_value_list_t.graphics_exposures */
        _aux->graphics_exposures = *(xcb_bool32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_bool32_t);
        xcb_tmp += sizeof(xcb_bool32_t);
        xcb_align_to = ALIGNOF(xcb_bool32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_X) {
        /* xcb_change_gc_value_list_t.clip_x_origin */
        _aux->clip_x_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_ORIGIN_Y) {
        /* xcb_change_gc_value_list_t.clip_y_origin */
        _aux->clip_y_origin = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_GC_CLIP_MASK) {
        /* xcb_change_gc_value_list_t.clip_mask */
        _aux->clip_mask = *(xcb_pixmap_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_pixmap_t);
        xcb_tmp += sizeof(xcb_pixmap_t);
        xcb_align_to = ALIGNOF(xcb_pixmap_t);
    }
    if(value_mask & XCB_GC_DASH_OFFSET) {
        /* xcb_change_gc_value_list_t.dash_offset */
        _aux->dash_offset = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_DASH_LIST) {
        /* xcb_change_gc_value_list_t.dashes */
        _aux->dashes = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_GC_ARC_MODE) {
        /* xcb_change_gc_value_list_t.arc_mode */
        _aux->arc_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    return xcb_buffer_len;
}

int
xcb_change_gc_value_list_sizeof (const void  *_buffer,
                                 uint32_t     value_mask)
{
    xcb_change_gc_value_list_t _aux;
    return xcb_change_gc_value_list_unpack(_buffer, value_mask, &_aux);
}

int
xcb_change_gc_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_change_gc_request_t *_aux = (xcb_change_gc_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_change_gc_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value_list */
    xcb_block_len += xcb_change_gc_value_list_sizeof(xcb_tmp, _aux->value_mask);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_change_gc_checked (xcb_connection_t *c,
                       xcb_gcontext_t    gc,
                       uint32_t          value_mask,
                       const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_gc_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_change_gc_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_gc (xcb_connection_t *c,
               xcb_gcontext_t    gc,
               uint32_t          value_mask,
               const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_gc_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_change_gc_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_gc_aux_checked (xcb_connection_t                 *c,
                           xcb_gcontext_t                    gc,
                           uint32_t                          value_mask,
                           const xcb_change_gc_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_gc_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_gc_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_change_gc_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_gc_aux (xcb_connection_t                 *c,
                   xcb_gcontext_t                    gc,
                   uint32_t                          value_mask,
                   const xcb_change_gc_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_gc_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_gc_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_change_gc_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

void *
xcb_change_gc_value_list (const xcb_change_gc_request_t *R)
{
    return (void *) (R + 1);
}

xcb_void_cookie_t
xcb_copy_gc_checked (xcb_connection_t *c,
                     xcb_gcontext_t    src_gc,
                     xcb_gcontext_t    dst_gc,
                     uint32_t          value_mask)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_gc = src_gc;
    xcb_out.dst_gc = dst_gc;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_gc (xcb_connection_t *c,
             xcb_gcontext_t    src_gc,
             xcb_gcontext_t    dst_gc,
             uint32_t          value_mask)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_gc = src_gc;
    xcb_out.dst_gc = dst_gc;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_set_dashes_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_set_dashes_request_t *_aux = (xcb_set_dashes_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_set_dashes_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* dashes */
    xcb_block_len += _aux->dashes_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_set_dashes_checked (xcb_connection_t *c,
                        xcb_gcontext_t    gc,
                        uint16_t          dash_offset,
                        uint16_t          dashes_len,
                        const uint8_t    *dashes)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_DASHES,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_set_dashes_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;
    xcb_out.dash_offset = dash_offset;
    xcb_out.dashes_len = dashes_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t dashes */
    xcb_parts[4].iov_base = (char *) dashes;
    xcb_parts[4].iov_len = dashes_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_dashes (xcb_connection_t *c,
                xcb_gcontext_t    gc,
                uint16_t          dash_offset,
                uint16_t          dashes_len,
                const uint8_t    *dashes)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_DASHES,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_set_dashes_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;
    xcb_out.dash_offset = dash_offset;
    xcb_out.dashes_len = dashes_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t dashes */
    xcb_parts[4].iov_base = (char *) dashes;
    xcb_parts[4].iov_len = dashes_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_set_dashes_dashes (const xcb_set_dashes_request_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_set_dashes_dashes_length (const xcb_set_dashes_request_t *R)
{
    return R->dashes_len;
}

xcb_generic_iterator_t
xcb_set_dashes_dashes_end (const xcb_set_dashes_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + (R->dashes_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_set_clip_rectangles_sizeof (const void  *_buffer,
                                uint32_t     rectangles_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_set_clip_rectangles_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* rectangles */
    xcb_block_len += rectangles_len * sizeof(xcb_rectangle_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_rectangle_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_set_clip_rectangles_checked (xcb_connection_t      *c,
                                 uint8_t                ordering,
                                 xcb_gcontext_t         gc,
                                 int16_t                clip_x_origin,
                                 int16_t                clip_y_origin,
                                 uint32_t               rectangles_len,
                                 const xcb_rectangle_t *rectangles)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_CLIP_RECTANGLES,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_set_clip_rectangles_request_t xcb_out;

    xcb_out.ordering = ordering;
    xcb_out.gc = gc;
    xcb_out.clip_x_origin = clip_x_origin;
    xcb_out.clip_y_origin = clip_y_origin;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_rectangle_t rectangles */
    xcb_parts[4].iov_base = (char *) rectangles;
    xcb_parts[4].iov_len = rectangles_len * sizeof(xcb_rectangle_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_clip_rectangles (xcb_connection_t      *c,
                         uint8_t                ordering,
                         xcb_gcontext_t         gc,
                         int16_t                clip_x_origin,
                         int16_t                clip_y_origin,
                         uint32_t               rectangles_len,
                         const xcb_rectangle_t *rectangles)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_CLIP_RECTANGLES,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_set_clip_rectangles_request_t xcb_out;

    xcb_out.ordering = ordering;
    xcb_out.gc = gc;
    xcb_out.clip_x_origin = clip_x_origin;
    xcb_out.clip_y_origin = clip_y_origin;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_rectangle_t rectangles */
    xcb_parts[4].iov_base = (char *) rectangles;
    xcb_parts[4].iov_len = rectangles_len * sizeof(xcb_rectangle_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_rectangle_t *
xcb_set_clip_rectangles_rectangles (const xcb_set_clip_rectangles_request_t *R)
{
    return (xcb_rectangle_t *) (R + 1);
}

int
xcb_set_clip_rectangles_rectangles_length (const xcb_set_clip_rectangles_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_set_clip_rectangles_request_t))/sizeof(xcb_rectangle_t));
}

xcb_rectangle_iterator_t
xcb_set_clip_rectangles_rectangles_iterator (const xcb_set_clip_rectangles_request_t *R)
{
    xcb_rectangle_iterator_t i;
    i.data = (xcb_rectangle_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_set_clip_rectangles_request_t))/sizeof(xcb_rectangle_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_void_cookie_t
xcb_free_gc_checked (xcb_connection_t *c,
                     xcb_gcontext_t    gc)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_gc (xcb_connection_t *c,
             xcb_gcontext_t    gc)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_GC,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_gc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_clear_area_checked (xcb_connection_t *c,
                        uint8_t           exposures,
                        xcb_window_t      window,
                        int16_t           x,
                        int16_t           y,
                        uint16_t          width,
                        uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CLEAR_AREA,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_clear_area_request_t xcb_out;

    xcb_out.exposures = exposures;
    xcb_out.window = window;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_clear_area (xcb_connection_t *c,
                uint8_t           exposures,
                xcb_window_t      window,
                int16_t           x,
                int16_t           y,
                uint16_t          width,
                uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CLEAR_AREA,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_clear_area_request_t xcb_out;

    xcb_out.exposures = exposures;
    xcb_out.window = window;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_area_checked (xcb_connection_t *c,
                       xcb_drawable_t    src_drawable,
                       xcb_drawable_t    dst_drawable,
                       xcb_gcontext_t    gc,
                       int16_t           src_x,
                       int16_t           src_y,
                       int16_t           dst_x,
                       int16_t           dst_y,
                       uint16_t          width,
                       uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_AREA,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_area_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_drawable = src_drawable;
    xcb_out.dst_drawable = dst_drawable;
    xcb_out.gc = gc;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_area (xcb_connection_t *c,
               xcb_drawable_t    src_drawable,
               xcb_drawable_t    dst_drawable,
               xcb_gcontext_t    gc,
               int16_t           src_x,
               int16_t           src_y,
               int16_t           dst_x,
               int16_t           dst_y,
               uint16_t          width,
               uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_AREA,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_area_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_drawable = src_drawable;
    xcb_out.dst_drawable = dst_drawable;
    xcb_out.gc = gc;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_plane_checked (xcb_connection_t *c,
                        xcb_drawable_t    src_drawable,
                        xcb_drawable_t    dst_drawable,
                        xcb_gcontext_t    gc,
                        int16_t           src_x,
                        int16_t           src_y,
                        int16_t           dst_x,
                        int16_t           dst_y,
                        uint16_t          width,
                        uint16_t          height,
                        uint32_t          bit_plane)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_PLANE,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_plane_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_drawable = src_drawable;
    xcb_out.dst_drawable = dst_drawable;
    xcb_out.gc = gc;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.bit_plane = bit_plane;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_plane (xcb_connection_t *c,
                xcb_drawable_t    src_drawable,
                xcb_drawable_t    dst_drawable,
                xcb_gcontext_t    gc,
                int16_t           src_x,
                int16_t           src_y,
                int16_t           dst_x,
                int16_t           dst_y,
                uint16_t          width,
                uint16_t          height,
                uint32_t          bit_plane)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_PLANE,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_plane_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.src_drawable = src_drawable;
    xcb_out.dst_drawable = dst_drawable;
    xcb_out.gc = gc;
    xcb_out.src_x = src_x;
    xcb_out.src_y = src_y;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.bit_plane = bit_plane;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_poly_point_sizeof (const void  *_buffer,
                       uint32_t     points_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_point_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* points */
    xcb_block_len += points_len * sizeof(xcb_point_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_point_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_point_checked (xcb_connection_t  *c,
                        uint8_t            coordinate_mode,
                        xcb_drawable_t     drawable,
                        xcb_gcontext_t     gc,
                        uint32_t           points_len,
                        const xcb_point_t *points)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_POINT,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_point_request_t xcb_out;

    xcb_out.coordinate_mode = coordinate_mode;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_point_t points */
    xcb_parts[4].iov_base = (char *) points;
    xcb_parts[4].iov_len = points_len * sizeof(xcb_point_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_point (xcb_connection_t  *c,
                uint8_t            coordinate_mode,
                xcb_drawable_t     drawable,
                xcb_gcontext_t     gc,
                uint32_t           points_len,
                const xcb_point_t *points)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_POINT,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_point_request_t xcb_out;

    xcb_out.coordinate_mode = coordinate_mode;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_point_t points */
    xcb_parts[4].iov_base = (char *) points;
    xcb_parts[4].iov_len = points_len * sizeof(xcb_point_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_point_t *
xcb_poly_point_points (const xcb_poly_point_request_t *R)
{
    return (xcb_point_t *) (R + 1);
}

int
xcb_poly_point_points_length (const xcb_poly_point_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_point_request_t))/sizeof(xcb_point_t));
}

xcb_point_iterator_t
xcb_poly_point_points_iterator (const xcb_poly_point_request_t *R)
{
    xcb_point_iterator_t i;
    i.data = (xcb_point_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_point_request_t))/sizeof(xcb_point_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_poly_line_sizeof (const void  *_buffer,
                      uint32_t     points_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_line_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* points */
    xcb_block_len += points_len * sizeof(xcb_point_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_point_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_line_checked (xcb_connection_t  *c,
                       uint8_t            coordinate_mode,
                       xcb_drawable_t     drawable,
                       xcb_gcontext_t     gc,
                       uint32_t           points_len,
                       const xcb_point_t *points)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_LINE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_line_request_t xcb_out;

    xcb_out.coordinate_mode = coordinate_mode;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_point_t points */
    xcb_parts[4].iov_base = (char *) points;
    xcb_parts[4].iov_len = points_len * sizeof(xcb_point_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_line (xcb_connection_t  *c,
               uint8_t            coordinate_mode,
               xcb_drawable_t     drawable,
               xcb_gcontext_t     gc,
               uint32_t           points_len,
               const xcb_point_t *points)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_LINE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_line_request_t xcb_out;

    xcb_out.coordinate_mode = coordinate_mode;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_point_t points */
    xcb_parts[4].iov_base = (char *) points;
    xcb_parts[4].iov_len = points_len * sizeof(xcb_point_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_point_t *
xcb_poly_line_points (const xcb_poly_line_request_t *R)
{
    return (xcb_point_t *) (R + 1);
}

int
xcb_poly_line_points_length (const xcb_poly_line_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_line_request_t))/sizeof(xcb_point_t));
}

xcb_point_iterator_t
xcb_poly_line_points_iterator (const xcb_poly_line_request_t *R)
{
    xcb_point_iterator_t i;
    i.data = (xcb_point_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_line_request_t))/sizeof(xcb_point_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_segment_next (xcb_segment_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_segment_t);
}

xcb_generic_iterator_t
xcb_segment_end (xcb_segment_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_poly_segment_sizeof (const void  *_buffer,
                         uint32_t     segments_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_segment_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* segments */
    xcb_block_len += segments_len * sizeof(xcb_segment_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_segment_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_segment_checked (xcb_connection_t    *c,
                          xcb_drawable_t       drawable,
                          xcb_gcontext_t       gc,
                          uint32_t             segments_len,
                          const xcb_segment_t *segments)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_SEGMENT,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_segment_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_segment_t segments */
    xcb_parts[4].iov_base = (char *) segments;
    xcb_parts[4].iov_len = segments_len * sizeof(xcb_segment_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_segment (xcb_connection_t    *c,
                  xcb_drawable_t       drawable,
                  xcb_gcontext_t       gc,
                  uint32_t             segments_len,
                  const xcb_segment_t *segments)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_SEGMENT,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_segment_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_segment_t segments */
    xcb_parts[4].iov_base = (char *) segments;
    xcb_parts[4].iov_len = segments_len * sizeof(xcb_segment_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_segment_t *
xcb_poly_segment_segments (const xcb_poly_segment_request_t *R)
{
    return (xcb_segment_t *) (R + 1);
}

int
xcb_poly_segment_segments_length (const xcb_poly_segment_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_segment_request_t))/sizeof(xcb_segment_t));
}

xcb_segment_iterator_t
xcb_poly_segment_segments_iterator (const xcb_poly_segment_request_t *R)
{
    xcb_segment_iterator_t i;
    i.data = (xcb_segment_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_segment_request_t))/sizeof(xcb_segment_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_poly_rectangle_sizeof (const void  *_buffer,
                           uint32_t     rectangles_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_rectangle_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* rectangles */
    xcb_block_len += rectangles_len * sizeof(xcb_rectangle_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_rectangle_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_rectangle_checked (xcb_connection_t      *c,
                            xcb_drawable_t         drawable,
                            xcb_gcontext_t         gc,
                            uint32_t               rectangles_len,
                            const xcb_rectangle_t *rectangles)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_RECTANGLE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_rectangle_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_rectangle_t rectangles */
    xcb_parts[4].iov_base = (char *) rectangles;
    xcb_parts[4].iov_len = rectangles_len * sizeof(xcb_rectangle_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_rectangle (xcb_connection_t      *c,
                    xcb_drawable_t         drawable,
                    xcb_gcontext_t         gc,
                    uint32_t               rectangles_len,
                    const xcb_rectangle_t *rectangles)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_RECTANGLE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_rectangle_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_rectangle_t rectangles */
    xcb_parts[4].iov_base = (char *) rectangles;
    xcb_parts[4].iov_len = rectangles_len * sizeof(xcb_rectangle_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_rectangle_t *
xcb_poly_rectangle_rectangles (const xcb_poly_rectangle_request_t *R)
{
    return (xcb_rectangle_t *) (R + 1);
}

int
xcb_poly_rectangle_rectangles_length (const xcb_poly_rectangle_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_rectangle_request_t))/sizeof(xcb_rectangle_t));
}

xcb_rectangle_iterator_t
xcb_poly_rectangle_rectangles_iterator (const xcb_poly_rectangle_request_t *R)
{
    xcb_rectangle_iterator_t i;
    i.data = (xcb_rectangle_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_rectangle_request_t))/sizeof(xcb_rectangle_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_poly_arc_sizeof (const void  *_buffer,
                     uint32_t     arcs_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_arc_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* arcs */
    xcb_block_len += arcs_len * sizeof(xcb_arc_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_arc_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_arc_checked (xcb_connection_t *c,
                      xcb_drawable_t    drawable,
                      xcb_gcontext_t    gc,
                      uint32_t          arcs_len,
                      const xcb_arc_t  *arcs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_ARC,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_arc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_arc_t arcs */
    xcb_parts[4].iov_base = (char *) arcs;
    xcb_parts[4].iov_len = arcs_len * sizeof(xcb_arc_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_arc (xcb_connection_t *c,
              xcb_drawable_t    drawable,
              xcb_gcontext_t    gc,
              uint32_t          arcs_len,
              const xcb_arc_t  *arcs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_ARC,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_arc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_arc_t arcs */
    xcb_parts[4].iov_base = (char *) arcs;
    xcb_parts[4].iov_len = arcs_len * sizeof(xcb_arc_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_arc_t *
xcb_poly_arc_arcs (const xcb_poly_arc_request_t *R)
{
    return (xcb_arc_t *) (R + 1);
}

int
xcb_poly_arc_arcs_length (const xcb_poly_arc_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_arc_request_t))/sizeof(xcb_arc_t));
}

xcb_arc_iterator_t
xcb_poly_arc_arcs_iterator (const xcb_poly_arc_request_t *R)
{
    xcb_arc_iterator_t i;
    i.data = (xcb_arc_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_arc_request_t))/sizeof(xcb_arc_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_fill_poly_sizeof (const void  *_buffer,
                      uint32_t     points_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_fill_poly_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* points */
    xcb_block_len += points_len * sizeof(xcb_point_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_point_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_fill_poly_checked (xcb_connection_t  *c,
                       xcb_drawable_t     drawable,
                       xcb_gcontext_t     gc,
                       uint8_t            shape,
                       uint8_t            coordinate_mode,
                       uint32_t           points_len,
                       const xcb_point_t *points)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_FILL_POLY,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_fill_poly_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.shape = shape;
    xcb_out.coordinate_mode = coordinate_mode;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_point_t points */
    xcb_parts[4].iov_base = (char *) points;
    xcb_parts[4].iov_len = points_len * sizeof(xcb_point_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_fill_poly (xcb_connection_t  *c,
               xcb_drawable_t     drawable,
               xcb_gcontext_t     gc,
               uint8_t            shape,
               uint8_t            coordinate_mode,
               uint32_t           points_len,
               const xcb_point_t *points)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_FILL_POLY,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_fill_poly_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.shape = shape;
    xcb_out.coordinate_mode = coordinate_mode;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_point_t points */
    xcb_parts[4].iov_base = (char *) points;
    xcb_parts[4].iov_len = points_len * sizeof(xcb_point_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_point_t *
xcb_fill_poly_points (const xcb_fill_poly_request_t *R)
{
    return (xcb_point_t *) (R + 1);
}

int
xcb_fill_poly_points_length (const xcb_fill_poly_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_fill_poly_request_t))/sizeof(xcb_point_t));
}

xcb_point_iterator_t
xcb_fill_poly_points_iterator (const xcb_fill_poly_request_t *R)
{
    xcb_point_iterator_t i;
    i.data = (xcb_point_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_fill_poly_request_t))/sizeof(xcb_point_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_poly_fill_rectangle_sizeof (const void  *_buffer,
                                uint32_t     rectangles_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_fill_rectangle_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* rectangles */
    xcb_block_len += rectangles_len * sizeof(xcb_rectangle_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_rectangle_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_fill_rectangle_checked (xcb_connection_t      *c,
                                 xcb_drawable_t         drawable,
                                 xcb_gcontext_t         gc,
                                 uint32_t               rectangles_len,
                                 const xcb_rectangle_t *rectangles)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_FILL_RECTANGLE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_fill_rectangle_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_rectangle_t rectangles */
    xcb_parts[4].iov_base = (char *) rectangles;
    xcb_parts[4].iov_len = rectangles_len * sizeof(xcb_rectangle_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_fill_rectangle (xcb_connection_t      *c,
                         xcb_drawable_t         drawable,
                         xcb_gcontext_t         gc,
                         uint32_t               rectangles_len,
                         const xcb_rectangle_t *rectangles)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_FILL_RECTANGLE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_fill_rectangle_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_rectangle_t rectangles */
    xcb_parts[4].iov_base = (char *) rectangles;
    xcb_parts[4].iov_len = rectangles_len * sizeof(xcb_rectangle_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_rectangle_t *
xcb_poly_fill_rectangle_rectangles (const xcb_poly_fill_rectangle_request_t *R)
{
    return (xcb_rectangle_t *) (R + 1);
}

int
xcb_poly_fill_rectangle_rectangles_length (const xcb_poly_fill_rectangle_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_fill_rectangle_request_t))/sizeof(xcb_rectangle_t));
}

xcb_rectangle_iterator_t
xcb_poly_fill_rectangle_rectangles_iterator (const xcb_poly_fill_rectangle_request_t *R)
{
    xcb_rectangle_iterator_t i;
    i.data = (xcb_rectangle_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_fill_rectangle_request_t))/sizeof(xcb_rectangle_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_poly_fill_arc_sizeof (const void  *_buffer,
                          uint32_t     arcs_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_fill_arc_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* arcs */
    xcb_block_len += arcs_len * sizeof(xcb_arc_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_arc_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_fill_arc_checked (xcb_connection_t *c,
                           xcb_drawable_t    drawable,
                           xcb_gcontext_t    gc,
                           uint32_t          arcs_len,
                           const xcb_arc_t  *arcs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_FILL_ARC,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_fill_arc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_arc_t arcs */
    xcb_parts[4].iov_base = (char *) arcs;
    xcb_parts[4].iov_len = arcs_len * sizeof(xcb_arc_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_fill_arc (xcb_connection_t *c,
                   xcb_drawable_t    drawable,
                   xcb_gcontext_t    gc,
                   uint32_t          arcs_len,
                   const xcb_arc_t  *arcs)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_FILL_ARC,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_fill_arc_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_arc_t arcs */
    xcb_parts[4].iov_base = (char *) arcs;
    xcb_parts[4].iov_len = arcs_len * sizeof(xcb_arc_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_arc_t *
xcb_poly_fill_arc_arcs (const xcb_poly_fill_arc_request_t *R)
{
    return (xcb_arc_t *) (R + 1);
}

int
xcb_poly_fill_arc_arcs_length (const xcb_poly_fill_arc_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_fill_arc_request_t))/sizeof(xcb_arc_t));
}

xcb_arc_iterator_t
xcb_poly_fill_arc_arcs_iterator (const xcb_poly_fill_arc_request_t *R)
{
    xcb_arc_iterator_t i;
    i.data = (xcb_arc_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_poly_fill_arc_request_t))/sizeof(xcb_arc_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_put_image_sizeof (const void  *_buffer,
                      uint32_t     data_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_put_image_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* data */
    xcb_block_len += data_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_put_image_checked (xcb_connection_t *c,
                       uint8_t           format,
                       xcb_drawable_t    drawable,
                       xcb_gcontext_t    gc,
                       uint16_t          width,
                       uint16_t          height,
                       int16_t           dst_x,
                       int16_t           dst_y,
                       uint8_t           left_pad,
                       uint8_t           depth,
                       uint32_t          data_len,
                       const uint8_t    *data)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_PUT_IMAGE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_put_image_request_t xcb_out;

    xcb_out.format = format;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;
    xcb_out.left_pad = left_pad;
    xcb_out.depth = depth;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t data */
    xcb_parts[4].iov_base = (char *) data;
    xcb_parts[4].iov_len = data_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_put_image (xcb_connection_t *c,
               uint8_t           format,
               xcb_drawable_t    drawable,
               xcb_gcontext_t    gc,
               uint16_t          width,
               uint16_t          height,
               int16_t           dst_x,
               int16_t           dst_y,
               uint8_t           left_pad,
               uint8_t           depth,
               uint32_t          data_len,
               const uint8_t    *data)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_PUT_IMAGE,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_put_image_request_t xcb_out;

    xcb_out.format = format;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.dst_x = dst_x;
    xcb_out.dst_y = dst_y;
    xcb_out.left_pad = left_pad;
    xcb_out.depth = depth;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t data */
    xcb_parts[4].iov_base = (char *) data;
    xcb_parts[4].iov_len = data_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_put_image_data (const xcb_put_image_request_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_put_image_data_length (const xcb_put_image_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_put_image_request_t))/sizeof(uint8_t));
}

xcb_generic_iterator_t
xcb_put_image_data_end (const xcb_put_image_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + ((((R->length * 4) - sizeof(xcb_put_image_request_t))/sizeof(uint8_t)));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_get_image_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_image_reply_t *_aux = (xcb_get_image_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_image_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* data */
    xcb_block_len += (_aux->length * 4) * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_image_cookie_t
xcb_get_image (xcb_connection_t *c,
               uint8_t           format,
               xcb_drawable_t    drawable,
               int16_t           x,
               int16_t           y,
               uint16_t          width,
               uint16_t          height,
               uint32_t          plane_mask)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_IMAGE,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_image_cookie_t xcb_ret;
    xcb_get_image_request_t xcb_out;

    xcb_out.format = format;
    xcb_out.drawable = drawable;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.plane_mask = plane_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_image_cookie_t
xcb_get_image_unchecked (xcb_connection_t *c,
                         uint8_t           format,
                         xcb_drawable_t    drawable,
                         int16_t           x,
                         int16_t           y,
                         uint16_t          width,
                         uint16_t          height,
                         uint32_t          plane_mask)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_IMAGE,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_image_cookie_t xcb_ret;
    xcb_get_image_request_t xcb_out;

    xcb_out.format = format;
    xcb_out.drawable = drawable;
    xcb_out.x = x;
    xcb_out.y = y;
    xcb_out.width = width;
    xcb_out.height = height;
    xcb_out.plane_mask = plane_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_get_image_data (const xcb_get_image_reply_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_get_image_data_length (const xcb_get_image_reply_t *R)
{
    return (R->length * 4);
}

xcb_generic_iterator_t
xcb_get_image_data_end (const xcb_get_image_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + ((R->length * 4));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_image_reply_t *
xcb_get_image_reply (xcb_connection_t        *c,
                     xcb_get_image_cookie_t   cookie  /**< */,
                     xcb_generic_error_t    **e)
{
    return (xcb_get_image_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_poly_text_8_sizeof (const void  *_buffer,
                        uint32_t     items_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_text_8_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* items */
    xcb_block_len += items_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_text_8_checked (xcb_connection_t *c,
                         xcb_drawable_t    drawable,
                         xcb_gcontext_t    gc,
                         int16_t           x,
                         int16_t           y,
                         uint32_t          items_len,
                         const uint8_t    *items)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_TEXT_8,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_text_8_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t items */
    xcb_parts[4].iov_base = (char *) items;
    xcb_parts[4].iov_len = items_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_text_8 (xcb_connection_t *c,
                 xcb_drawable_t    drawable,
                 xcb_gcontext_t    gc,
                 int16_t           x,
                 int16_t           y,
                 uint32_t          items_len,
                 const uint8_t    *items)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_TEXT_8,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_text_8_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t items */
    xcb_parts[4].iov_base = (char *) items;
    xcb_parts[4].iov_len = items_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_poly_text_8_items (const xcb_poly_text_8_request_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_poly_text_8_items_length (const xcb_poly_text_8_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_text_8_request_t))/sizeof(uint8_t));
}

xcb_generic_iterator_t
xcb_poly_text_8_items_end (const xcb_poly_text_8_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + ((((R->length * 4) - sizeof(xcb_poly_text_8_request_t))/sizeof(uint8_t)));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_poly_text_16_sizeof (const void  *_buffer,
                         uint32_t     items_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_poly_text_16_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* items */
    xcb_block_len += items_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_poly_text_16_checked (xcb_connection_t *c,
                          xcb_drawable_t    drawable,
                          xcb_gcontext_t    gc,
                          int16_t           x,
                          int16_t           y,
                          uint32_t          items_len,
                          const uint8_t    *items)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_TEXT_16,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_text_16_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t items */
    xcb_parts[4].iov_base = (char *) items;
    xcb_parts[4].iov_len = items_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_poly_text_16 (xcb_connection_t *c,
                  xcb_drawable_t    drawable,
                  xcb_gcontext_t    gc,
                  int16_t           x,
                  int16_t           y,
                  uint32_t          items_len,
                  const uint8_t    *items)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_POLY_TEXT_16,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_poly_text_16_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t items */
    xcb_parts[4].iov_base = (char *) items;
    xcb_parts[4].iov_len = items_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_poly_text_16_items (const xcb_poly_text_16_request_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_poly_text_16_items_length (const xcb_poly_text_16_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_poly_text_16_request_t))/sizeof(uint8_t));
}

xcb_generic_iterator_t
xcb_poly_text_16_items_end (const xcb_poly_text_16_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + ((((R->length * 4) - sizeof(xcb_poly_text_16_request_t))/sizeof(uint8_t)));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_image_text_8_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_image_text_8_request_t *_aux = (xcb_image_text_8_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_image_text_8_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* string */
    xcb_block_len += _aux->string_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_image_text_8_checked (xcb_connection_t *c,
                          uint8_t           string_len,
                          xcb_drawable_t    drawable,
                          xcb_gcontext_t    gc,
                          int16_t           x,
                          int16_t           y,
                          const char       *string)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_IMAGE_TEXT_8,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_image_text_8_request_t xcb_out;

    xcb_out.string_len = string_len;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char string */
    xcb_parts[4].iov_base = (char *) string;
    xcb_parts[4].iov_len = string_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_image_text_8 (xcb_connection_t *c,
                  uint8_t           string_len,
                  xcb_drawable_t    drawable,
                  xcb_gcontext_t    gc,
                  int16_t           x,
                  int16_t           y,
                  const char       *string)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_IMAGE_TEXT_8,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_image_text_8_request_t xcb_out;

    xcb_out.string_len = string_len;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char string */
    xcb_parts[4].iov_base = (char *) string;
    xcb_parts[4].iov_len = string_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

char *
xcb_image_text_8_string (const xcb_image_text_8_request_t *R)
{
    return (char *) (R + 1);
}

int
xcb_image_text_8_string_length (const xcb_image_text_8_request_t *R)
{
    return R->string_len;
}

xcb_generic_iterator_t
xcb_image_text_8_string_end (const xcb_image_text_8_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->string_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_image_text_16_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_image_text_16_request_t *_aux = (xcb_image_text_16_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_image_text_16_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* string */
    xcb_block_len += _aux->string_len * sizeof(xcb_char2b_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_char2b_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_image_text_16_checked (xcb_connection_t   *c,
                           uint8_t             string_len,
                           xcb_drawable_t      drawable,
                           xcb_gcontext_t      gc,
                           int16_t             x,
                           int16_t             y,
                           const xcb_char2b_t *string)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_IMAGE_TEXT_16,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_image_text_16_request_t xcb_out;

    xcb_out.string_len = string_len;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_char2b_t string */
    xcb_parts[4].iov_base = (char *) string;
    xcb_parts[4].iov_len = string_len * sizeof(xcb_char2b_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_image_text_16 (xcb_connection_t   *c,
                   uint8_t             string_len,
                   xcb_drawable_t      drawable,
                   xcb_gcontext_t      gc,
                   int16_t             x,
                   int16_t             y,
                   const xcb_char2b_t *string)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_IMAGE_TEXT_16,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_image_text_16_request_t xcb_out;

    xcb_out.string_len = string_len;
    xcb_out.drawable = drawable;
    xcb_out.gc = gc;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_char2b_t string */
    xcb_parts[4].iov_base = (char *) string;
    xcb_parts[4].iov_len = string_len * sizeof(xcb_char2b_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_char2b_t *
xcb_image_text_16_string (const xcb_image_text_16_request_t *R)
{
    return (xcb_char2b_t *) (R + 1);
}

int
xcb_image_text_16_string_length (const xcb_image_text_16_request_t *R)
{
    return R->string_len;
}

xcb_char2b_iterator_t
xcb_image_text_16_string_iterator (const xcb_image_text_16_request_t *R)
{
    xcb_char2b_iterator_t i;
    i.data = (xcb_char2b_t *) (R + 1);
    i.rem = R->string_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_void_cookie_t
xcb_create_colormap_checked (xcb_connection_t *c,
                             uint8_t           alloc,
                             xcb_colormap_t    mid,
                             xcb_window_t      window,
                             xcb_visualid_t    visual)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_colormap_request_t xcb_out;

    xcb_out.alloc = alloc;
    xcb_out.mid = mid;
    xcb_out.window = window;
    xcb_out.visual = visual;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_colormap (xcb_connection_t *c,
                     uint8_t           alloc,
                     xcb_colormap_t    mid,
                     xcb_window_t      window,
                     xcb_visualid_t    visual)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_colormap_request_t xcb_out;

    xcb_out.alloc = alloc;
    xcb_out.mid = mid;
    xcb_out.window = window;
    xcb_out.visual = visual;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_colormap_checked (xcb_connection_t *c,
                           xcb_colormap_t    cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_colormap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_colormap (xcb_connection_t *c,
                   xcb_colormap_t    cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_colormap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_colormap_and_free_checked (xcb_connection_t *c,
                                    xcb_colormap_t    mid,
                                    xcb_colormap_t    src_cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_COLORMAP_AND_FREE,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_colormap_and_free_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.mid = mid;
    xcb_out.src_cmap = src_cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_copy_colormap_and_free (xcb_connection_t *c,
                            xcb_colormap_t    mid,
                            xcb_colormap_t    src_cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_COPY_COLORMAP_AND_FREE,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_copy_colormap_and_free_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.mid = mid;
    xcb_out.src_cmap = src_cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_install_colormap_checked (xcb_connection_t *c,
                              xcb_colormap_t    cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_INSTALL_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_install_colormap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_install_colormap (xcb_connection_t *c,
                      xcb_colormap_t    cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_INSTALL_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_install_colormap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_uninstall_colormap_checked (xcb_connection_t *c,
                                xcb_colormap_t    cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNINSTALL_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_uninstall_colormap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_uninstall_colormap (xcb_connection_t *c,
                        xcb_colormap_t    cmap)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_UNINSTALL_COLORMAP,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_uninstall_colormap_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_list_installed_colormaps_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_list_installed_colormaps_reply_t *_aux = (xcb_list_installed_colormaps_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_list_installed_colormaps_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* cmaps */
    xcb_block_len += _aux->cmaps_len * sizeof(xcb_colormap_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_colormap_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_list_installed_colormaps_cookie_t
xcb_list_installed_colormaps (xcb_connection_t *c,
                              xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_INSTALLED_COLORMAPS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_installed_colormaps_cookie_t xcb_ret;
    xcb_list_installed_colormaps_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_list_installed_colormaps_cookie_t
xcb_list_installed_colormaps_unchecked (xcb_connection_t *c,
                                        xcb_window_t      window)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_INSTALLED_COLORMAPS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_installed_colormaps_cookie_t xcb_ret;
    xcb_list_installed_colormaps_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_colormap_t *
xcb_list_installed_colormaps_cmaps (const xcb_list_installed_colormaps_reply_t *R)
{
    return (xcb_colormap_t *) (R + 1);
}

int
xcb_list_installed_colormaps_cmaps_length (const xcb_list_installed_colormaps_reply_t *R)
{
    return R->cmaps_len;
}

xcb_generic_iterator_t
xcb_list_installed_colormaps_cmaps_end (const xcb_list_installed_colormaps_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_colormap_t *) (R + 1)) + (R->cmaps_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_list_installed_colormaps_reply_t *
xcb_list_installed_colormaps_reply (xcb_connection_t                       *c,
                                    xcb_list_installed_colormaps_cookie_t   cookie  /**< */,
                                    xcb_generic_error_t                   **e)
{
    return (xcb_list_installed_colormaps_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_alloc_color_cookie_t
xcb_alloc_color (xcb_connection_t *c,
                 xcb_colormap_t    cmap,
                 uint16_t          red,
                 uint16_t          green,
                 uint16_t          blue)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOC_COLOR,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_alloc_color_cookie_t xcb_ret;
    xcb_alloc_color_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.red = red;
    xcb_out.green = green;
    xcb_out.blue = blue;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_alloc_color_cookie_t
xcb_alloc_color_unchecked (xcb_connection_t *c,
                           xcb_colormap_t    cmap,
                           uint16_t          red,
                           uint16_t          green,
                           uint16_t          blue)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOC_COLOR,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_alloc_color_cookie_t xcb_ret;
    xcb_alloc_color_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.red = red;
    xcb_out.green = green;
    xcb_out.blue = blue;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_alloc_color_reply_t *
xcb_alloc_color_reply (xcb_connection_t          *c,
                       xcb_alloc_color_cookie_t   cookie  /**< */,
                       xcb_generic_error_t      **e)
{
    return (xcb_alloc_color_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_alloc_named_color_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_alloc_named_color_request_t *_aux = (xcb_alloc_named_color_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_alloc_named_color_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_alloc_named_color_cookie_t
xcb_alloc_named_color (xcb_connection_t *c,
                       xcb_colormap_t    cmap,
                       uint16_t          name_len,
                       const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_ALLOC_NAMED_COLOR,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_alloc_named_color_cookie_t xcb_ret;
    xcb_alloc_named_color_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_alloc_named_color_cookie_t
xcb_alloc_named_color_unchecked (xcb_connection_t *c,
                                 xcb_colormap_t    cmap,
                                 uint16_t          name_len,
                                 const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_ALLOC_NAMED_COLOR,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_alloc_named_color_cookie_t xcb_ret;
    xcb_alloc_named_color_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_alloc_named_color_reply_t *
xcb_alloc_named_color_reply (xcb_connection_t                *c,
                             xcb_alloc_named_color_cookie_t   cookie  /**< */,
                             xcb_generic_error_t            **e)
{
    return (xcb_alloc_named_color_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_alloc_color_cells_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_alloc_color_cells_reply_t *_aux = (xcb_alloc_color_cells_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_alloc_color_cells_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* pixels */
    xcb_block_len += _aux->pixels_len * sizeof(uint32_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint32_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* masks */
    xcb_block_len += _aux->masks_len * sizeof(uint32_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint32_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_alloc_color_cells_cookie_t
xcb_alloc_color_cells (xcb_connection_t *c,
                       uint8_t           contiguous,
                       xcb_colormap_t    cmap,
                       uint16_t          colors,
                       uint16_t          planes)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOC_COLOR_CELLS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_alloc_color_cells_cookie_t xcb_ret;
    xcb_alloc_color_cells_request_t xcb_out;

    xcb_out.contiguous = contiguous;
    xcb_out.cmap = cmap;
    xcb_out.colors = colors;
    xcb_out.planes = planes;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_alloc_color_cells_cookie_t
xcb_alloc_color_cells_unchecked (xcb_connection_t *c,
                                 uint8_t           contiguous,
                                 xcb_colormap_t    cmap,
                                 uint16_t          colors,
                                 uint16_t          planes)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOC_COLOR_CELLS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_alloc_color_cells_cookie_t xcb_ret;
    xcb_alloc_color_cells_request_t xcb_out;

    xcb_out.contiguous = contiguous;
    xcb_out.cmap = cmap;
    xcb_out.colors = colors;
    xcb_out.planes = planes;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint32_t *
xcb_alloc_color_cells_pixels (const xcb_alloc_color_cells_reply_t *R)
{
    return (uint32_t *) (R + 1);
}

int
xcb_alloc_color_cells_pixels_length (const xcb_alloc_color_cells_reply_t *R)
{
    return R->pixels_len;
}

xcb_generic_iterator_t
xcb_alloc_color_cells_pixels_end (const xcb_alloc_color_cells_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint32_t *) (R + 1)) + (R->pixels_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

uint32_t *
xcb_alloc_color_cells_masks (const xcb_alloc_color_cells_reply_t *R)
{
    xcb_generic_iterator_t prev = xcb_alloc_color_cells_pixels_end(R);
    return (uint32_t *) ((char *) prev.data + XCB_TYPE_PAD(uint32_t, prev.index) + 0);
}

int
xcb_alloc_color_cells_masks_length (const xcb_alloc_color_cells_reply_t *R)
{
    return R->masks_len;
}

xcb_generic_iterator_t
xcb_alloc_color_cells_masks_end (const xcb_alloc_color_cells_reply_t *R)
{
    xcb_generic_iterator_t i;
    xcb_generic_iterator_t prev = xcb_alloc_color_cells_pixels_end(R);
    i.data = ((uint32_t *) ((char*) prev.data + XCB_TYPE_PAD(uint32_t, prev.index))) + (R->masks_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_alloc_color_cells_reply_t *
xcb_alloc_color_cells_reply (xcb_connection_t                *c,
                             xcb_alloc_color_cells_cookie_t   cookie  /**< */,
                             xcb_generic_error_t            **e)
{
    return (xcb_alloc_color_cells_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_alloc_color_planes_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_alloc_color_planes_reply_t *_aux = (xcb_alloc_color_planes_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_alloc_color_planes_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* pixels */
    xcb_block_len += _aux->pixels_len * sizeof(uint32_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint32_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_alloc_color_planes_cookie_t
xcb_alloc_color_planes (xcb_connection_t *c,
                        uint8_t           contiguous,
                        xcb_colormap_t    cmap,
                        uint16_t          colors,
                        uint16_t          reds,
                        uint16_t          greens,
                        uint16_t          blues)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOC_COLOR_PLANES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_alloc_color_planes_cookie_t xcb_ret;
    xcb_alloc_color_planes_request_t xcb_out;

    xcb_out.contiguous = contiguous;
    xcb_out.cmap = cmap;
    xcb_out.colors = colors;
    xcb_out.reds = reds;
    xcb_out.greens = greens;
    xcb_out.blues = blues;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_alloc_color_planes_cookie_t
xcb_alloc_color_planes_unchecked (xcb_connection_t *c,
                                  uint8_t           contiguous,
                                  xcb_colormap_t    cmap,
                                  uint16_t          colors,
                                  uint16_t          reds,
                                  uint16_t          greens,
                                  uint16_t          blues)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_ALLOC_COLOR_PLANES,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_alloc_color_planes_cookie_t xcb_ret;
    xcb_alloc_color_planes_request_t xcb_out;

    xcb_out.contiguous = contiguous;
    xcb_out.cmap = cmap;
    xcb_out.colors = colors;
    xcb_out.reds = reds;
    xcb_out.greens = greens;
    xcb_out.blues = blues;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint32_t *
xcb_alloc_color_planes_pixels (const xcb_alloc_color_planes_reply_t *R)
{
    return (uint32_t *) (R + 1);
}

int
xcb_alloc_color_planes_pixels_length (const xcb_alloc_color_planes_reply_t *R)
{
    return R->pixels_len;
}

xcb_generic_iterator_t
xcb_alloc_color_planes_pixels_end (const xcb_alloc_color_planes_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint32_t *) (R + 1)) + (R->pixels_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_alloc_color_planes_reply_t *
xcb_alloc_color_planes_reply (xcb_connection_t                 *c,
                              xcb_alloc_color_planes_cookie_t   cookie  /**< */,
                              xcb_generic_error_t             **e)
{
    return (xcb_alloc_color_planes_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_free_colors_sizeof (const void  *_buffer,
                        uint32_t     pixels_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_free_colors_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* pixels */
    xcb_block_len += pixels_len * sizeof(uint32_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint32_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_free_colors_checked (xcb_connection_t *c,
                         xcb_colormap_t    cmap,
                         uint32_t          plane_mask,
                         uint32_t          pixels_len,
                         const uint32_t   *pixels)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_FREE_COLORS,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_free_colors_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.plane_mask = plane_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint32_t pixels */
    xcb_parts[4].iov_base = (char *) pixels;
    xcb_parts[4].iov_len = pixels_len * sizeof(uint32_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_colors (xcb_connection_t *c,
                 xcb_colormap_t    cmap,
                 uint32_t          plane_mask,
                 uint32_t          pixels_len,
                 const uint32_t   *pixels)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_FREE_COLORS,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_free_colors_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.plane_mask = plane_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint32_t pixels */
    xcb_parts[4].iov_base = (char *) pixels;
    xcb_parts[4].iov_len = pixels_len * sizeof(uint32_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint32_t *
xcb_free_colors_pixels (const xcb_free_colors_request_t *R)
{
    return (uint32_t *) (R + 1);
}

int
xcb_free_colors_pixels_length (const xcb_free_colors_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_free_colors_request_t))/sizeof(uint32_t));
}

xcb_generic_iterator_t
xcb_free_colors_pixels_end (const xcb_free_colors_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint32_t *) (R + 1)) + ((((R->length * 4) - sizeof(xcb_free_colors_request_t))/sizeof(uint32_t)));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_coloritem_next (xcb_coloritem_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_coloritem_t);
}

xcb_generic_iterator_t
xcb_coloritem_end (xcb_coloritem_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_store_colors_sizeof (const void  *_buffer,
                         uint32_t     items_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_store_colors_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* items */
    xcb_block_len += items_len * sizeof(xcb_coloritem_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_coloritem_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_store_colors_checked (xcb_connection_t      *c,
                          xcb_colormap_t         cmap,
                          uint32_t               items_len,
                          const xcb_coloritem_t *items)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_STORE_COLORS,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_store_colors_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_coloritem_t items */
    xcb_parts[4].iov_base = (char *) items;
    xcb_parts[4].iov_len = items_len * sizeof(xcb_coloritem_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_store_colors (xcb_connection_t      *c,
                  xcb_colormap_t         cmap,
                  uint32_t               items_len,
                  const xcb_coloritem_t *items)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_STORE_COLORS,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_store_colors_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_coloritem_t items */
    xcb_parts[4].iov_base = (char *) items;
    xcb_parts[4].iov_len = items_len * sizeof(xcb_coloritem_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_coloritem_t *
xcb_store_colors_items (const xcb_store_colors_request_t *R)
{
    return (xcb_coloritem_t *) (R + 1);
}

int
xcb_store_colors_items_length (const xcb_store_colors_request_t *R)
{
    return (((R->length * 4) - sizeof(xcb_store_colors_request_t))/sizeof(xcb_coloritem_t));
}

xcb_coloritem_iterator_t
xcb_store_colors_items_iterator (const xcb_store_colors_request_t *R)
{
    xcb_coloritem_iterator_t i;
    i.data = (xcb_coloritem_t *) (R + 1);
    i.rem = (((R->length * 4) - sizeof(xcb_store_colors_request_t))/sizeof(xcb_coloritem_t));
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_store_named_color_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_store_named_color_request_t *_aux = (xcb_store_named_color_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_store_named_color_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_store_named_color_checked (xcb_connection_t *c,
                               uint8_t           flags,
                               xcb_colormap_t    cmap,
                               uint32_t          pixel,
                               uint16_t          name_len,
                               const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_STORE_NAMED_COLOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_store_named_color_request_t xcb_out;

    xcb_out.flags = flags;
    xcb_out.cmap = cmap;
    xcb_out.pixel = pixel;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_store_named_color (xcb_connection_t *c,
                       uint8_t           flags,
                       xcb_colormap_t    cmap,
                       uint32_t          pixel,
                       uint16_t          name_len,
                       const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_STORE_NAMED_COLOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_store_named_color_request_t xcb_out;

    xcb_out.flags = flags;
    xcb_out.cmap = cmap;
    xcb_out.pixel = pixel;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

char *
xcb_store_named_color_name (const xcb_store_named_color_request_t *R)
{
    return (char *) (R + 1);
}

int
xcb_store_named_color_name_length (const xcb_store_named_color_request_t *R)
{
    return R->name_len;
}

xcb_generic_iterator_t
xcb_store_named_color_name_end (const xcb_store_named_color_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((char *) (R + 1)) + (R->name_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_rgb_next (xcb_rgb_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_rgb_t);
}

xcb_generic_iterator_t
xcb_rgb_end (xcb_rgb_iterator_t i)
{
    xcb_generic_iterator_t ret;
    ret.data = i.data + i.rem;
    ret.index = i.index + ((char *) ret.data - (char *) i.data);
    ret.rem = 0;
    return ret;
}

int
xcb_query_colors_sizeof (const void  *_buffer,
                         uint32_t     pixels_len)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_query_colors_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* pixels */
    xcb_block_len += pixels_len * sizeof(uint32_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint32_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_query_colors_cookie_t
xcb_query_colors (xcb_connection_t *c,
                  xcb_colormap_t    cmap,
                  uint32_t          pixels_len,
                  const uint32_t   *pixels)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_QUERY_COLORS,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_query_colors_cookie_t xcb_ret;
    xcb_query_colors_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint32_t pixels */
    xcb_parts[4].iov_base = (char *) pixels;
    xcb_parts[4].iov_len = pixels_len * sizeof(uint32_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_colors_cookie_t
xcb_query_colors_unchecked (xcb_connection_t *c,
                            xcb_colormap_t    cmap,
                            uint32_t          pixels_len,
                            const uint32_t   *pixels)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_QUERY_COLORS,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_query_colors_cookie_t xcb_ret;
    xcb_query_colors_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint32_t pixels */
    xcb_parts[4].iov_base = (char *) pixels;
    xcb_parts[4].iov_len = pixels_len * sizeof(uint32_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_rgb_t *
xcb_query_colors_colors (const xcb_query_colors_reply_t *R)
{
    return (xcb_rgb_t *) (R + 1);
}

int
xcb_query_colors_colors_length (const xcb_query_colors_reply_t *R)
{
    return R->colors_len;
}

xcb_rgb_iterator_t
xcb_query_colors_colors_iterator (const xcb_query_colors_reply_t *R)
{
    xcb_rgb_iterator_t i;
    i.data = (xcb_rgb_t *) (R + 1);
    i.rem = R->colors_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_query_colors_reply_t *
xcb_query_colors_reply (xcb_connection_t           *c,
                        xcb_query_colors_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_query_colors_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_lookup_color_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_lookup_color_request_t *_aux = (xcb_lookup_color_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_lookup_color_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_lookup_color_cookie_t
xcb_lookup_color (xcb_connection_t *c,
                  xcb_colormap_t    cmap,
                  uint16_t          name_len,
                  const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_LOOKUP_COLOR,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_lookup_color_cookie_t xcb_ret;
    xcb_lookup_color_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_lookup_color_cookie_t
xcb_lookup_color_unchecked (xcb_connection_t *c,
                            xcb_colormap_t    cmap,
                            uint16_t          name_len,
                            const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_LOOKUP_COLOR,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_lookup_color_cookie_t xcb_ret;
    xcb_lookup_color_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cmap = cmap;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_lookup_color_reply_t *
xcb_lookup_color_reply (xcb_connection_t           *c,
                        xcb_lookup_color_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_lookup_color_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_create_cursor_checked (xcb_connection_t *c,
                           xcb_cursor_t      cid,
                           xcb_pixmap_t      source,
                           xcb_pixmap_t      mask,
                           uint16_t          fore_red,
                           uint16_t          fore_green,
                           uint16_t          fore_blue,
                           uint16_t          back_red,
                           uint16_t          back_green,
                           uint16_t          back_blue,
                           uint16_t          x,
                           uint16_t          y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.source = source;
    xcb_out.mask = mask;
    xcb_out.fore_red = fore_red;
    xcb_out.fore_green = fore_green;
    xcb_out.fore_blue = fore_blue;
    xcb_out.back_red = back_red;
    xcb_out.back_green = back_green;
    xcb_out.back_blue = back_blue;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_cursor (xcb_connection_t *c,
                   xcb_cursor_t      cid,
                   xcb_pixmap_t      source,
                   xcb_pixmap_t      mask,
                   uint16_t          fore_red,
                   uint16_t          fore_green,
                   uint16_t          fore_blue,
                   uint16_t          back_red,
                   uint16_t          back_green,
                   uint16_t          back_blue,
                   uint16_t          x,
                   uint16_t          y)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.source = source;
    xcb_out.mask = mask;
    xcb_out.fore_red = fore_red;
    xcb_out.fore_green = fore_green;
    xcb_out.fore_blue = fore_blue;
    xcb_out.back_red = back_red;
    xcb_out.back_green = back_green;
    xcb_out.back_blue = back_blue;
    xcb_out.x = x;
    xcb_out.y = y;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_glyph_cursor_checked (xcb_connection_t *c,
                                 xcb_cursor_t      cid,
                                 xcb_font_t        source_font,
                                 xcb_font_t        mask_font,
                                 uint16_t          source_char,
                                 uint16_t          mask_char,
                                 uint16_t          fore_red,
                                 uint16_t          fore_green,
                                 uint16_t          fore_blue,
                                 uint16_t          back_red,
                                 uint16_t          back_green,
                                 uint16_t          back_blue)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_GLYPH_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_glyph_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.source_font = source_font;
    xcb_out.mask_font = mask_font;
    xcb_out.source_char = source_char;
    xcb_out.mask_char = mask_char;
    xcb_out.fore_red = fore_red;
    xcb_out.fore_green = fore_green;
    xcb_out.fore_blue = fore_blue;
    xcb_out.back_red = back_red;
    xcb_out.back_green = back_green;
    xcb_out.back_blue = back_blue;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_create_glyph_cursor (xcb_connection_t *c,
                         xcb_cursor_t      cid,
                         xcb_font_t        source_font,
                         xcb_font_t        mask_font,
                         uint16_t          source_char,
                         uint16_t          mask_char,
                         uint16_t          fore_red,
                         uint16_t          fore_green,
                         uint16_t          fore_blue,
                         uint16_t          back_red,
                         uint16_t          back_green,
                         uint16_t          back_blue)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CREATE_GLYPH_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_create_glyph_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cid = cid;
    xcb_out.source_font = source_font;
    xcb_out.mask_font = mask_font;
    xcb_out.source_char = source_char;
    xcb_out.mask_char = mask_char;
    xcb_out.fore_red = fore_red;
    xcb_out.fore_green = fore_green;
    xcb_out.fore_blue = fore_blue;
    xcb_out.back_red = back_red;
    xcb_out.back_green = back_green;
    xcb_out.back_blue = back_blue;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_cursor_checked (xcb_connection_t *c,
                         xcb_cursor_t      cursor)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cursor = cursor;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_free_cursor (xcb_connection_t *c,
                 xcb_cursor_t      cursor)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FREE_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_free_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cursor = cursor;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_recolor_cursor_checked (xcb_connection_t *c,
                            xcb_cursor_t      cursor,
                            uint16_t          fore_red,
                            uint16_t          fore_green,
                            uint16_t          fore_blue,
                            uint16_t          back_red,
                            uint16_t          back_green,
                            uint16_t          back_blue)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_RECOLOR_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_recolor_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cursor = cursor;
    xcb_out.fore_red = fore_red;
    xcb_out.fore_green = fore_green;
    xcb_out.fore_blue = fore_blue;
    xcb_out.back_red = back_red;
    xcb_out.back_green = back_green;
    xcb_out.back_blue = back_blue;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_recolor_cursor (xcb_connection_t *c,
                    xcb_cursor_t      cursor,
                    uint16_t          fore_red,
                    uint16_t          fore_green,
                    uint16_t          fore_blue,
                    uint16_t          back_red,
                    uint16_t          back_green,
                    uint16_t          back_blue)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_RECOLOR_CURSOR,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_recolor_cursor_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.cursor = cursor;
    xcb_out.fore_red = fore_red;
    xcb_out.fore_green = fore_green;
    xcb_out.fore_blue = fore_blue;
    xcb_out.back_red = back_red;
    xcb_out.back_green = back_green;
    xcb_out.back_blue = back_blue;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_best_size_cookie_t
xcb_query_best_size (xcb_connection_t *c,
                     uint8_t           _class,
                     xcb_drawable_t    drawable,
                     uint16_t          width,
                     uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_BEST_SIZE,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_best_size_cookie_t xcb_ret;
    xcb_query_best_size_request_t xcb_out;

    xcb_out._class = _class;
    xcb_out.drawable = drawable;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_best_size_cookie_t
xcb_query_best_size_unchecked (xcb_connection_t *c,
                               uint8_t           _class,
                               xcb_drawable_t    drawable,
                               uint16_t          width,
                               uint16_t          height)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_QUERY_BEST_SIZE,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_query_best_size_cookie_t xcb_ret;
    xcb_query_best_size_request_t xcb_out;

    xcb_out._class = _class;
    xcb_out.drawable = drawable;
    xcb_out.width = width;
    xcb_out.height = height;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_best_size_reply_t *
xcb_query_best_size_reply (xcb_connection_t              *c,
                           xcb_query_best_size_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e)
{
    return (xcb_query_best_size_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_query_extension_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_query_extension_request_t *_aux = (xcb_query_extension_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_query_extension_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* name */
    xcb_block_len += _aux->name_len * sizeof(char);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_query_extension_cookie_t
xcb_query_extension (xcb_connection_t *c,
                     uint16_t          name_len,
                     const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_QUERY_EXTENSION,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_query_extension_cookie_t xcb_ret;
    xcb_query_extension_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_extension_cookie_t
xcb_query_extension_unchecked (xcb_connection_t *c,
                               uint16_t          name_len,
                               const char       *name)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_QUERY_EXTENSION,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_query_extension_cookie_t xcb_ret;
    xcb_query_extension_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.name_len = name_len;
    memset(xcb_out.pad1, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* char name */
    xcb_parts[4].iov_base = (char *) name;
    xcb_parts[4].iov_len = name_len * sizeof(char);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_query_extension_reply_t *
xcb_query_extension_reply (xcb_connection_t              *c,
                           xcb_query_extension_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e)
{
    return (xcb_query_extension_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_list_extensions_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_list_extensions_reply_t *_aux = (xcb_list_extensions_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;

    unsigned int i;
    unsigned int xcb_tmp_len;

    xcb_block_len += sizeof(xcb_list_extensions_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* names */
    for(i=0; i<_aux->names_len; i++) {
        xcb_tmp_len = xcb_str_sizeof(xcb_tmp);
        xcb_block_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_align_to = ALIGNOF(xcb_str_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_list_extensions_cookie_t
xcb_list_extensions (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_EXTENSIONS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_extensions_cookie_t xcb_ret;
    xcb_list_extensions_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_list_extensions_cookie_t
xcb_list_extensions_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_EXTENSIONS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_extensions_cookie_t xcb_ret;
    xcb_list_extensions_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_list_extensions_names_length (const xcb_list_extensions_reply_t *R)
{
    return R->names_len;
}

xcb_str_iterator_t
xcb_list_extensions_names_iterator (const xcb_list_extensions_reply_t *R)
{
    xcb_str_iterator_t i;
    i.data = (xcb_str_t *) (R + 1);
    i.rem = R->names_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_list_extensions_reply_t *
xcb_list_extensions_reply (xcb_connection_t              *c,
                           xcb_list_extensions_cookie_t   cookie  /**< */,
                           xcb_generic_error_t          **e)
{
    return (xcb_list_extensions_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_change_keyboard_mapping_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_change_keyboard_mapping_request_t *_aux = (xcb_change_keyboard_mapping_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_change_keyboard_mapping_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* keysyms */
    xcb_block_len += (_aux->keycode_count * _aux->keysyms_per_keycode) * sizeof(xcb_keysym_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_keysym_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_change_keyboard_mapping_checked (xcb_connection_t   *c,
                                     uint8_t             keycode_count,
                                     xcb_keycode_t       first_keycode,
                                     uint8_t             keysyms_per_keycode,
                                     const xcb_keysym_t *keysyms)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_CHANGE_KEYBOARD_MAPPING,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_change_keyboard_mapping_request_t xcb_out;

    xcb_out.keycode_count = keycode_count;
    xcb_out.first_keycode = first_keycode;
    xcb_out.keysyms_per_keycode = keysyms_per_keycode;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_keysym_t keysyms */
    xcb_parts[4].iov_base = (char *) keysyms;
    xcb_parts[4].iov_len = (keycode_count * keysyms_per_keycode) * sizeof(xcb_keysym_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_keyboard_mapping (xcb_connection_t   *c,
                             uint8_t             keycode_count,
                             xcb_keycode_t       first_keycode,
                             uint8_t             keysyms_per_keycode,
                             const xcb_keysym_t *keysyms)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_CHANGE_KEYBOARD_MAPPING,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_change_keyboard_mapping_request_t xcb_out;

    xcb_out.keycode_count = keycode_count;
    xcb_out.first_keycode = first_keycode;
    xcb_out.keysyms_per_keycode = keysyms_per_keycode;
    memset(xcb_out.pad0, 0, 2);

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_keysym_t keysyms */
    xcb_parts[4].iov_base = (char *) keysyms;
    xcb_parts[4].iov_len = (keycode_count * keysyms_per_keycode) * sizeof(xcb_keysym_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_keysym_t *
xcb_change_keyboard_mapping_keysyms (const xcb_change_keyboard_mapping_request_t *R)
{
    return (xcb_keysym_t *) (R + 1);
}

int
xcb_change_keyboard_mapping_keysyms_length (const xcb_change_keyboard_mapping_request_t *R)
{
    return (R->keycode_count * R->keysyms_per_keycode);
}

xcb_generic_iterator_t
xcb_change_keyboard_mapping_keysyms_end (const xcb_change_keyboard_mapping_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_keysym_t *) (R + 1)) + ((R->keycode_count * R->keysyms_per_keycode));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_get_keyboard_mapping_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_keyboard_mapping_reply_t *_aux = (xcb_get_keyboard_mapping_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_keyboard_mapping_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* keysyms */
    xcb_block_len += _aux->length * sizeof(xcb_keysym_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_keysym_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_keyboard_mapping_cookie_t
xcb_get_keyboard_mapping (xcb_connection_t *c,
                          xcb_keycode_t     first_keycode,
                          uint8_t           count)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_KEYBOARD_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_keyboard_mapping_cookie_t xcb_ret;
    xcb_get_keyboard_mapping_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.first_keycode = first_keycode;
    xcb_out.count = count;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_keyboard_mapping_cookie_t
xcb_get_keyboard_mapping_unchecked (xcb_connection_t *c,
                                    xcb_keycode_t     first_keycode,
                                    uint8_t           count)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_KEYBOARD_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_keyboard_mapping_cookie_t xcb_ret;
    xcb_get_keyboard_mapping_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.first_keycode = first_keycode;
    xcb_out.count = count;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_keysym_t *
xcb_get_keyboard_mapping_keysyms (const xcb_get_keyboard_mapping_reply_t *R)
{
    return (xcb_keysym_t *) (R + 1);
}

int
xcb_get_keyboard_mapping_keysyms_length (const xcb_get_keyboard_mapping_reply_t *R)
{
    return R->length;
}

xcb_generic_iterator_t
xcb_get_keyboard_mapping_keysyms_end (const xcb_get_keyboard_mapping_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_keysym_t *) (R + 1)) + (R->length);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_keyboard_mapping_reply_t *
xcb_get_keyboard_mapping_reply (xcb_connection_t                   *c,
                                xcb_get_keyboard_mapping_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e)
{
    return (xcb_get_keyboard_mapping_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_change_keyboard_control_value_list_serialize (void                                           **_buffer,
                                                  uint32_t                                         value_mask,
                                                  const xcb_change_keyboard_control_value_list_t  *_aux)
{
    char *xcb_out = *_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;

    unsigned int xcb_pad = 0;
    char xcb_pad0[3] = {0, 0, 0};
    struct iovec xcb_parts[9];
    unsigned int xcb_parts_idx = 0;
    unsigned int xcb_block_len = 0;
    unsigned int i;
    char *xcb_tmp;

    if(value_mask & XCB_KB_KEY_CLICK_PERCENT) {
        /* xcb_change_keyboard_control_value_list_t.key_click_percent */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->key_click_percent;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_BELL_PERCENT) {
        /* xcb_change_keyboard_control_value_list_t.bell_percent */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->bell_percent;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_BELL_PITCH) {
        /* xcb_change_keyboard_control_value_list_t.bell_pitch */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->bell_pitch;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_BELL_DURATION) {
        /* xcb_change_keyboard_control_value_list_t.bell_duration */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->bell_duration;
        xcb_block_len += sizeof(int32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(int32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_LED) {
        /* xcb_change_keyboard_control_value_list_t.led */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->led;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_KB_LED_MODE) {
        /* xcb_change_keyboard_control_value_list_t.led_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->led_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_KB_KEY) {
        /* xcb_change_keyboard_control_value_list_t.key */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->key;
        xcb_block_len += sizeof(xcb_keycode32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(xcb_keycode32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(xcb_keycode32_t);
    }
    if(value_mask & XCB_KB_AUTO_REPEAT_MODE) {
        /* xcb_change_keyboard_control_value_list_t.auto_repeat_mode */
        xcb_parts[xcb_parts_idx].iov_base = (char *) &_aux->auto_repeat_mode;
        xcb_block_len += sizeof(uint32_t);
        xcb_parts[xcb_parts_idx].iov_len = sizeof(uint32_t);
        xcb_parts_idx++;
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_parts[xcb_parts_idx].iov_base = xcb_pad0;
        xcb_parts[xcb_parts_idx].iov_len = xcb_pad;
        xcb_parts_idx++;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    if (NULL == xcb_out) {
        /* allocate memory */
        xcb_out = malloc(xcb_buffer_len);
        *_buffer = xcb_out;
    }

    xcb_tmp = xcb_out;
    for(i=0; i<xcb_parts_idx; i++) {
        if (0 != xcb_parts[i].iov_base && 0 != xcb_parts[i].iov_len)
            memcpy(xcb_tmp, xcb_parts[i].iov_base, xcb_parts[i].iov_len);
        if (0 != xcb_parts[i].iov_len)
            xcb_tmp += xcb_parts[i].iov_len;
    }

    return xcb_buffer_len;
}

int
xcb_change_keyboard_control_value_list_unpack (const void                                *_buffer,
                                               uint32_t                                   value_mask,
                                               xcb_change_keyboard_control_value_list_t  *_aux)
{
    char *xcb_tmp = (char *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;
    unsigned int xcb_padding_offset = 0;


    if(value_mask & XCB_KB_KEY_CLICK_PERCENT) {
        /* xcb_change_keyboard_control_value_list_t.key_click_percent */
        _aux->key_click_percent = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_BELL_PERCENT) {
        /* xcb_change_keyboard_control_value_list_t.bell_percent */
        _aux->bell_percent = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_BELL_PITCH) {
        /* xcb_change_keyboard_control_value_list_t.bell_pitch */
        _aux->bell_pitch = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_BELL_DURATION) {
        /* xcb_change_keyboard_control_value_list_t.bell_duration */
        _aux->bell_duration = *(int32_t *)xcb_tmp;
        xcb_block_len += sizeof(int32_t);
        xcb_tmp += sizeof(int32_t);
        xcb_align_to = ALIGNOF(int32_t);
    }
    if(value_mask & XCB_KB_LED) {
        /* xcb_change_keyboard_control_value_list_t.led */
        _aux->led = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_KB_LED_MODE) {
        /* xcb_change_keyboard_control_value_list_t.led_mode */
        _aux->led_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    if(value_mask & XCB_KB_KEY) {
        /* xcb_change_keyboard_control_value_list_t.key */
        _aux->key = *(xcb_keycode32_t *)xcb_tmp;
        xcb_block_len += sizeof(xcb_keycode32_t);
        xcb_tmp += sizeof(xcb_keycode32_t);
        xcb_align_to = ALIGNOF(xcb_keycode32_t);
    }
    if(value_mask & XCB_KB_AUTO_REPEAT_MODE) {
        /* xcb_change_keyboard_control_value_list_t.auto_repeat_mode */
        _aux->auto_repeat_mode = *(uint32_t *)xcb_tmp;
        xcb_block_len += sizeof(uint32_t);
        xcb_tmp += sizeof(uint32_t);
        xcb_align_to = ALIGNOF(uint32_t);
    }
    /* insert padding */
    xcb_pad = -(xcb_block_len + xcb_padding_offset) & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    xcb_padding_offset = 0;

    return xcb_buffer_len;
}

int
xcb_change_keyboard_control_value_list_sizeof (const void  *_buffer,
                                               uint32_t     value_mask)
{
    xcb_change_keyboard_control_value_list_t _aux;
    return xcb_change_keyboard_control_value_list_unpack(_buffer, value_mask, &_aux);
}

int
xcb_change_keyboard_control_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_change_keyboard_control_request_t *_aux = (xcb_change_keyboard_control_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_change_keyboard_control_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* value_list */
    xcb_block_len += xcb_change_keyboard_control_value_list_sizeof(xcb_tmp, _aux->value_mask);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(char);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_change_keyboard_control_checked (xcb_connection_t *c,
                                     uint32_t          value_mask,
                                     const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_KEYBOARD_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_keyboard_control_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_keyboard_control_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_change_keyboard_control_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_keyboard_control (xcb_connection_t *c,
                             uint32_t          value_mask,
                             const void       *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_KEYBOARD_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_keyboard_control_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_keyboard_control_value_list_t value_list */
    xcb_parts[4].iov_base = (char *) value_list;
    xcb_parts[4].iov_len =
      xcb_change_keyboard_control_value_list_sizeof (value_list, value_mask);

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_keyboard_control_aux_checked (xcb_connection_t                               *c,
                                         uint32_t                                        value_mask,
                                         const xcb_change_keyboard_control_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_KEYBOARD_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_keyboard_control_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_keyboard_control_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_change_keyboard_control_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_keyboard_control_aux (xcb_connection_t                               *c,
                                 uint32_t                                        value_mask,
                                 const xcb_change_keyboard_control_value_list_t *value_list)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 3,
        .ext = 0,
        .opcode = XCB_CHANGE_KEYBOARD_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[5];
    xcb_void_cookie_t xcb_ret;
    xcb_change_keyboard_control_request_t xcb_out;
    void *xcb_aux0 = 0;

    xcb_out.pad0 = 0;
    xcb_out.value_mask = value_mask;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_change_keyboard_control_value_list_t value_list */
    xcb_parts[4].iov_len =
      xcb_change_keyboard_control_value_list_serialize (&xcb_aux0, value_mask, value_list);
    xcb_parts[4].iov_base = xcb_aux0;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    free(xcb_aux0);
    return xcb_ret;
}

void *
xcb_change_keyboard_control_value_list (const xcb_change_keyboard_control_request_t *R)
{
    return (void *) (R + 1);
}

xcb_get_keyboard_control_cookie_t
xcb_get_keyboard_control (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_KEYBOARD_CONTROL,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_keyboard_control_cookie_t xcb_ret;
    xcb_get_keyboard_control_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_keyboard_control_cookie_t
xcb_get_keyboard_control_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_KEYBOARD_CONTROL,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_keyboard_control_cookie_t xcb_ret;
    xcb_get_keyboard_control_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_keyboard_control_reply_t *
xcb_get_keyboard_control_reply (xcb_connection_t                   *c,
                                xcb_get_keyboard_control_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e)
{
    return (xcb_get_keyboard_control_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_bell_checked (xcb_connection_t *c,
                  int8_t            percent)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_BELL,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_bell_request_t xcb_out;

    xcb_out.percent = percent;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_bell (xcb_connection_t *c,
          int8_t            percent)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_BELL,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_bell_request_t xcb_out;

    xcb_out.percent = percent;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_pointer_control_checked (xcb_connection_t *c,
                                    int16_t           acceleration_numerator,
                                    int16_t           acceleration_denominator,
                                    int16_t           threshold,
                                    uint8_t           do_acceleration,
                                    uint8_t           do_threshold)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CHANGE_POINTER_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_change_pointer_control_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.acceleration_numerator = acceleration_numerator;
    xcb_out.acceleration_denominator = acceleration_denominator;
    xcb_out.threshold = threshold;
    xcb_out.do_acceleration = do_acceleration;
    xcb_out.do_threshold = do_threshold;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_pointer_control (xcb_connection_t *c,
                            int16_t           acceleration_numerator,
                            int16_t           acceleration_denominator,
                            int16_t           threshold,
                            uint8_t           do_acceleration,
                            uint8_t           do_threshold)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_CHANGE_POINTER_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_change_pointer_control_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.acceleration_numerator = acceleration_numerator;
    xcb_out.acceleration_denominator = acceleration_denominator;
    xcb_out.threshold = threshold;
    xcb_out.do_acceleration = do_acceleration;
    xcb_out.do_threshold = do_threshold;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_pointer_control_cookie_t
xcb_get_pointer_control (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_POINTER_CONTROL,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_pointer_control_cookie_t xcb_ret;
    xcb_get_pointer_control_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_pointer_control_cookie_t
xcb_get_pointer_control_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_POINTER_CONTROL,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_pointer_control_cookie_t xcb_ret;
    xcb_get_pointer_control_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_pointer_control_reply_t *
xcb_get_pointer_control_reply (xcb_connection_t                  *c,
                               xcb_get_pointer_control_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e)
{
    return (xcb_get_pointer_control_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_set_screen_saver_checked (xcb_connection_t *c,
                              int16_t           timeout,
                              int16_t           interval,
                              uint8_t           prefer_blanking,
                              uint8_t           allow_exposures)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_SCREEN_SAVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_screen_saver_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.timeout = timeout;
    xcb_out.interval = interval;
    xcb_out.prefer_blanking = prefer_blanking;
    xcb_out.allow_exposures = allow_exposures;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_screen_saver (xcb_connection_t *c,
                      int16_t           timeout,
                      int16_t           interval,
                      uint8_t           prefer_blanking,
                      uint8_t           allow_exposures)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_SCREEN_SAVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_screen_saver_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.timeout = timeout;
    xcb_out.interval = interval;
    xcb_out.prefer_blanking = prefer_blanking;
    xcb_out.allow_exposures = allow_exposures;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_screen_saver_cookie_t
xcb_get_screen_saver (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_SCREEN_SAVER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_screen_saver_cookie_t xcb_ret;
    xcb_get_screen_saver_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_screen_saver_cookie_t
xcb_get_screen_saver_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_SCREEN_SAVER,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_screen_saver_cookie_t xcb_ret;
    xcb_get_screen_saver_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_screen_saver_reply_t *
xcb_get_screen_saver_reply (xcb_connection_t               *c,
                            xcb_get_screen_saver_cookie_t   cookie  /**< */,
                            xcb_generic_error_t           **e)
{
    return (xcb_get_screen_saver_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_change_hosts_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_change_hosts_request_t *_aux = (xcb_change_hosts_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_change_hosts_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* address */
    xcb_block_len += _aux->address_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_change_hosts_checked (xcb_connection_t *c,
                          uint8_t           mode,
                          uint8_t           family,
                          uint16_t          address_len,
                          const uint8_t    *address)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_CHANGE_HOSTS,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_change_hosts_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.family = family;
    xcb_out.pad0 = 0;
    xcb_out.address_len = address_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t address */
    xcb_parts[4].iov_base = (char *) address;
    xcb_parts[4].iov_len = address_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_change_hosts (xcb_connection_t *c,
                  uint8_t           mode,
                  uint8_t           family,
                  uint16_t          address_len,
                  const uint8_t    *address)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_CHANGE_HOSTS,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_change_hosts_request_t xcb_out;

    xcb_out.mode = mode;
    xcb_out.family = family;
    xcb_out.pad0 = 0;
    xcb_out.address_len = address_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t address */
    xcb_parts[4].iov_base = (char *) address;
    xcb_parts[4].iov_len = address_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_change_hosts_address (const xcb_change_hosts_request_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_change_hosts_address_length (const xcb_change_hosts_request_t *R)
{
    return R->address_len;
}

xcb_generic_iterator_t
xcb_change_hosts_address_end (const xcb_change_hosts_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + (R->address_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

int
xcb_host_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_host_t *_aux = (xcb_host_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_host_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* address */
    xcb_block_len += _aux->address_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    xcb_align_to = 4;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

uint8_t *
xcb_host_address (const xcb_host_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_host_address_length (const xcb_host_t *R)
{
    return R->address_len;
}

xcb_generic_iterator_t
xcb_host_address_end (const xcb_host_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + (R->address_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

void
xcb_host_next (xcb_host_iterator_t *i)
{
    xcb_host_t *R = i->data;
    xcb_generic_iterator_t child;
    child.data = (xcb_host_t *)(((char *)R) + xcb_host_sizeof(R));
    i->index = (char *) child.data - (char *) i->data;
    --i->rem;
    i->data = (xcb_host_t *) child.data;
}

xcb_generic_iterator_t
xcb_host_end (xcb_host_iterator_t i)
{
    xcb_generic_iterator_t ret;
    while(i.rem > 0)
        xcb_host_next(&i);
    ret.data = i.data;
    ret.rem = i.rem;
    ret.index = i.index;
    return ret;
}

int
xcb_list_hosts_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_list_hosts_reply_t *_aux = (xcb_list_hosts_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;

    unsigned int i;
    unsigned int xcb_tmp_len;

    xcb_block_len += sizeof(xcb_list_hosts_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* hosts */
    for(i=0; i<_aux->hosts_len; i++) {
        xcb_tmp_len = xcb_host_sizeof(xcb_tmp);
        xcb_block_len += xcb_tmp_len;
        xcb_tmp += xcb_tmp_len;
    }
    xcb_align_to = ALIGNOF(xcb_host_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_list_hosts_cookie_t
xcb_list_hosts (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_HOSTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_hosts_cookie_t xcb_ret;
    xcb_list_hosts_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_list_hosts_cookie_t
xcb_list_hosts_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_LIST_HOSTS,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_list_hosts_cookie_t xcb_ret;
    xcb_list_hosts_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_list_hosts_hosts_length (const xcb_list_hosts_reply_t *R)
{
    return R->hosts_len;
}

xcb_host_iterator_t
xcb_list_hosts_hosts_iterator (const xcb_list_hosts_reply_t *R)
{
    xcb_host_iterator_t i;
    i.data = (xcb_host_t *) (R + 1);
    i.rem = R->hosts_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_list_hosts_reply_t *
xcb_list_hosts_reply (xcb_connection_t         *c,
                      xcb_list_hosts_cookie_t   cookie  /**< */,
                      xcb_generic_error_t     **e)
{
    return (xcb_list_hosts_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_set_access_control_checked (xcb_connection_t *c,
                                uint8_t           mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_ACCESS_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_access_control_request_t xcb_out;

    xcb_out.mode = mode;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_access_control (xcb_connection_t *c,
                        uint8_t           mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_ACCESS_CONTROL,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_access_control_request_t xcb_out;

    xcb_out.mode = mode;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_close_down_mode_checked (xcb_connection_t *c,
                                 uint8_t           mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_CLOSE_DOWN_MODE,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_close_down_mode_request_t xcb_out;

    xcb_out.mode = mode;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_set_close_down_mode (xcb_connection_t *c,
                         uint8_t           mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_SET_CLOSE_DOWN_MODE,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_set_close_down_mode_request_t xcb_out;

    xcb_out.mode = mode;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_kill_client_checked (xcb_connection_t *c,
                         uint32_t          resource)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_KILL_CLIENT,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_kill_client_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.resource = resource;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_kill_client (xcb_connection_t *c,
                 uint32_t          resource)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_KILL_CLIENT,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_kill_client_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.resource = resource;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_rotate_properties_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_rotate_properties_request_t *_aux = (xcb_rotate_properties_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_rotate_properties_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* atoms */
    xcb_block_len += _aux->atoms_len * sizeof(xcb_atom_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_atom_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_void_cookie_t
xcb_rotate_properties_checked (xcb_connection_t *c,
                               xcb_window_t      window,
                               uint16_t          atoms_len,
                               int16_t           delta,
                               const xcb_atom_t *atoms)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_ROTATE_PROPERTIES,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_rotate_properties_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.atoms_len = atoms_len;
    xcb_out.delta = delta;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_atom_t atoms */
    xcb_parts[4].iov_base = (char *) atoms;
    xcb_parts[4].iov_len = atoms_len * sizeof(xcb_atom_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_rotate_properties (xcb_connection_t *c,
                       xcb_window_t      window,
                       uint16_t          atoms_len,
                       int16_t           delta,
                       const xcb_atom_t *atoms)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_ROTATE_PROPERTIES,
        .isvoid = 1
    };

    struct iovec xcb_parts[6];
    xcb_void_cookie_t xcb_ret;
    xcb_rotate_properties_request_t xcb_out;

    xcb_out.pad0 = 0;
    xcb_out.window = window;
    xcb_out.atoms_len = atoms_len;
    xcb_out.delta = delta;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_atom_t atoms */
    xcb_parts[4].iov_base = (char *) atoms;
    xcb_parts[4].iov_len = atoms_len * sizeof(xcb_atom_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_atom_t *
xcb_rotate_properties_atoms (const xcb_rotate_properties_request_t *R)
{
    return (xcb_atom_t *) (R + 1);
}

int
xcb_rotate_properties_atoms_length (const xcb_rotate_properties_request_t *R)
{
    return R->atoms_len;
}

xcb_generic_iterator_t
xcb_rotate_properties_atoms_end (const xcb_rotate_properties_request_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_atom_t *) (R + 1)) + (R->atoms_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_void_cookie_t
xcb_force_screen_saver_checked (xcb_connection_t *c,
                                uint8_t           mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FORCE_SCREEN_SAVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_force_screen_saver_request_t xcb_out;

    xcb_out.mode = mode;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_force_screen_saver (xcb_connection_t *c,
                        uint8_t           mode)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_FORCE_SCREEN_SAVER,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_force_screen_saver_request_t xcb_out;

    xcb_out.mode = mode;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

int
xcb_set_pointer_mapping_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_set_pointer_mapping_request_t *_aux = (xcb_set_pointer_mapping_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_set_pointer_mapping_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* map */
    xcb_block_len += _aux->map_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_set_pointer_mapping_cookie_t
xcb_set_pointer_mapping (xcb_connection_t *c,
                         uint8_t           map_len,
                         const uint8_t    *map)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_POINTER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_set_pointer_mapping_cookie_t xcb_ret;
    xcb_set_pointer_mapping_request_t xcb_out;

    xcb_out.map_len = map_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t map */
    xcb_parts[4].iov_base = (char *) map;
    xcb_parts[4].iov_len = map_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_set_pointer_mapping_cookie_t
xcb_set_pointer_mapping_unchecked (xcb_connection_t *c,
                                   uint8_t           map_len,
                                   const uint8_t    *map)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_POINTER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_set_pointer_mapping_cookie_t xcb_ret;
    xcb_set_pointer_mapping_request_t xcb_out;

    xcb_out.map_len = map_len;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* uint8_t map */
    xcb_parts[4].iov_base = (char *) map;
    xcb_parts[4].iov_len = map_len * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_set_pointer_mapping_reply_t *
xcb_set_pointer_mapping_reply (xcb_connection_t                  *c,
                               xcb_set_pointer_mapping_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e)
{
    return (xcb_set_pointer_mapping_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_get_pointer_mapping_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_pointer_mapping_reply_t *_aux = (xcb_get_pointer_mapping_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_pointer_mapping_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* map */
    xcb_block_len += _aux->map_len * sizeof(uint8_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(uint8_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_pointer_mapping_cookie_t
xcb_get_pointer_mapping (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_POINTER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_pointer_mapping_cookie_t xcb_ret;
    xcb_get_pointer_mapping_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_pointer_mapping_cookie_t
xcb_get_pointer_mapping_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_POINTER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_pointer_mapping_cookie_t xcb_ret;
    xcb_get_pointer_mapping_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

uint8_t *
xcb_get_pointer_mapping_map (const xcb_get_pointer_mapping_reply_t *R)
{
    return (uint8_t *) (R + 1);
}

int
xcb_get_pointer_mapping_map_length (const xcb_get_pointer_mapping_reply_t *R)
{
    return R->map_len;
}

xcb_generic_iterator_t
xcb_get_pointer_mapping_map_end (const xcb_get_pointer_mapping_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((uint8_t *) (R + 1)) + (R->map_len);
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_pointer_mapping_reply_t *
xcb_get_pointer_mapping_reply (xcb_connection_t                  *c,
                               xcb_get_pointer_mapping_cookie_t   cookie  /**< */,
                               xcb_generic_error_t              **e)
{
    return (xcb_get_pointer_mapping_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_set_modifier_mapping_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_set_modifier_mapping_request_t *_aux = (xcb_set_modifier_mapping_request_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_set_modifier_mapping_request_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* keycodes */
    xcb_block_len += (_aux->keycodes_per_modifier * 8) * sizeof(xcb_keycode_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_keycode_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_set_modifier_mapping_cookie_t
xcb_set_modifier_mapping (xcb_connection_t    *c,
                          uint8_t              keycodes_per_modifier,
                          const xcb_keycode_t *keycodes)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_MODIFIER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_set_modifier_mapping_cookie_t xcb_ret;
    xcb_set_modifier_mapping_request_t xcb_out;

    xcb_out.keycodes_per_modifier = keycodes_per_modifier;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_keycode_t keycodes */
    xcb_parts[4].iov_base = (char *) keycodes;
    xcb_parts[4].iov_len = (keycodes_per_modifier * 8) * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_set_modifier_mapping_cookie_t
xcb_set_modifier_mapping_unchecked (xcb_connection_t    *c,
                                    uint8_t              keycodes_per_modifier,
                                    const xcb_keycode_t *keycodes)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 4,
        .ext = 0,
        .opcode = XCB_SET_MODIFIER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[6];
    xcb_set_modifier_mapping_cookie_t xcb_ret;
    xcb_set_modifier_mapping_request_t xcb_out;

    xcb_out.keycodes_per_modifier = keycodes_per_modifier;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;
    /* xcb_keycode_t keycodes */
    xcb_parts[4].iov_base = (char *) keycodes;
    xcb_parts[4].iov_len = (keycodes_per_modifier * 8) * sizeof(uint8_t);
    xcb_parts[5].iov_base = 0;
    xcb_parts[5].iov_len = -xcb_parts[4].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_set_modifier_mapping_reply_t *
xcb_set_modifier_mapping_reply (xcb_connection_t                   *c,
                                xcb_set_modifier_mapping_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e)
{
    return (xcb_set_modifier_mapping_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

int
xcb_get_modifier_mapping_sizeof (const void  *_buffer)
{
    char *xcb_tmp = (char *)_buffer;
    const xcb_get_modifier_mapping_reply_t *_aux = (xcb_get_modifier_mapping_reply_t *)_buffer;
    unsigned int xcb_buffer_len = 0;
    unsigned int xcb_block_len = 0;
    unsigned int xcb_pad = 0;
    unsigned int xcb_align_to = 0;


    xcb_block_len += sizeof(xcb_get_modifier_mapping_reply_t);
    xcb_tmp += xcb_block_len;
    xcb_buffer_len += xcb_block_len;
    xcb_block_len = 0;
    /* keycodes */
    xcb_block_len += (_aux->keycodes_per_modifier * 8) * sizeof(xcb_keycode_t);
    xcb_tmp += xcb_block_len;
    xcb_align_to = ALIGNOF(xcb_keycode_t);
    /* insert padding */
    xcb_pad = -xcb_block_len & (xcb_align_to - 1);
    xcb_buffer_len += xcb_block_len + xcb_pad;
    if (0 != xcb_pad) {
        xcb_tmp += xcb_pad;
        xcb_pad = 0;
    }
    xcb_block_len = 0;

    return xcb_buffer_len;
}

xcb_get_modifier_mapping_cookie_t
xcb_get_modifier_mapping (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_MODIFIER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_modifier_mapping_cookie_t xcb_ret;
    xcb_get_modifier_mapping_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_get_modifier_mapping_cookie_t
xcb_get_modifier_mapping_unchecked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_GET_MODIFIER_MAPPING,
        .isvoid = 0
    };

    struct iovec xcb_parts[4];
    xcb_get_modifier_mapping_cookie_t xcb_ret;
    xcb_get_modifier_mapping_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_keycode_t *
xcb_get_modifier_mapping_keycodes (const xcb_get_modifier_mapping_reply_t *R)
{
    return (xcb_keycode_t *) (R + 1);
}

int
xcb_get_modifier_mapping_keycodes_length (const xcb_get_modifier_mapping_reply_t *R)
{
    return (R->keycodes_per_modifier * 8);
}

xcb_generic_iterator_t
xcb_get_modifier_mapping_keycodes_end (const xcb_get_modifier_mapping_reply_t *R)
{
    xcb_generic_iterator_t i;
    i.data = ((xcb_keycode_t *) (R + 1)) + ((R->keycodes_per_modifier * 8));
    i.rem = 0;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_modifier_mapping_reply_t *
xcb_get_modifier_mapping_reply (xcb_connection_t                   *c,
                                xcb_get_modifier_mapping_cookie_t   cookie  /**< */,
                                xcb_generic_error_t               **e)
{
    return (xcb_get_modifier_mapping_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

xcb_void_cookie_t
xcb_no_operation_checked (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_NO_OPERATION,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_no_operation_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, XCB_REQUEST_CHECKED, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

xcb_void_cookie_t
xcb_no_operation (xcb_connection_t *c)
{
    static const xcb_protocol_request_t xcb_req = {
        .count = 2,
        .ext = 0,
        .opcode = XCB_NO_OPERATION,
        .isvoid = 1
    };

    struct iovec xcb_parts[4];
    xcb_void_cookie_t xcb_ret;
    xcb_no_operation_request_t xcb_out;

    xcb_out.pad0 = 0;

    xcb_parts[2].iov_base = (char *) &xcb_out;
    xcb_parts[2].iov_len = sizeof(xcb_out);
    xcb_parts[3].iov_base = 0;
    xcb_parts[3].iov_len = -xcb_parts[2].iov_len & 3;

    xcb_ret.sequence = xcb_send_request(c, 0, xcb_parts + 2, &xcb_req);
    return xcb_ret;
}

/*
Copyright 1989, 1998  The Open Group
Copyright 2009  Open Text Corporation

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.
 * *
 * Author:  Jim Fulton, MIT X Consortium
 * Author:  Peter Harris, Open Text Corporation
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#ifndef PRIx32
#define PRIx32 "x"
#endif
#ifndef PRIu32
#define PRIu32 "u"
#endif

#ifndef __has_attribute
# define __has_attribute(x) 0  /* Compatibility with older compilers. */
#endif

static char *ProgramName;

static xcb_atom_t WM_STATE;

static void lookat (xcb_connection_t *dpy, xcb_window_t root, int verbose, int maxcmdlen);
static void print_client_properties (xcb_connection_t *dpy, xcb_window_t w,
				     int verbose, int maxcmdlen );
static void print_text_field (xcb_connection_t *dpy, const char *s, xcb_get_property_reply_t *tp );
static int print_quoted_word (char *s, int maxlen);
static void unknown (xcb_connection_t *dpy, xcb_atom_t actual_type, int actual_format );

/* For convenience: */
typedef int Bool;
#define False (0)
#define True (!False)

static void
#if __has_attribute(__cold__)
__attribute__((__cold__))
#endif
#if __has_attribute(noreturn)
__attribute__((noreturn))
#endif
usage(const char *errmsg)
{
    if (errmsg != NULL)
	fprintf (stderr, "%s: %s\n\n", ProgramName, errmsg);

    fprintf (stderr,
	     "usage:  %s  [-display dpy] [-m len] [-[a][l]] [-version]\n",
	     ProgramName);
    exit (1);
}

typedef void (*queue_func)(void *closure);
typedef struct queue_blob {
    queue_func func;
    void *closure;
    struct queue_blob *next;
} queue_blob;

static queue_blob *head = NULL;
static queue_blob **tail = &head;

static void enqueue(queue_func func, void *closure)
{
    queue_blob *blob = malloc(sizeof(*blob));
    if (!blob)
	return; /* TODO: print OOM error */

    blob->func = func;
    blob->closure = closure;
    blob->next = NULL;
    *tail = blob;
    tail = &blob->next;
}

static void run_queue(void)
{
    while (head) {
	queue_blob *blob = head;
	blob->func(blob->closure);
	head = blob->next;
	free(blob);
    }
    tail = &head;
}

typedef struct {
    xcb_connection_t *c;
    xcb_intern_atom_cookie_t cookie;
    xcb_atom_t *atom;
} atom_state;

static void atom_done(void *closure)
{
    xcb_intern_atom_reply_t *reply;
    atom_state *as = closure;

    reply = xcb_intern_atom_reply(as->c, as->cookie, NULL);
    if (!reply)
	goto done; /* TODO: print Error message */

    *(as->atom) = reply->atom;
    free(reply);

done:
    free(as);
}

static void init_atoms(xcb_connection_t *c)
{
    atom_state *as;

    as = malloc(sizeof(*as));
    as->c = c;
    as->atom = &WM_STATE;
    as->cookie = xcb_intern_atom(c, 0, strlen("WM_STATE"), "WM_STATE");
    enqueue(atom_done, as);
}

int
main(int argc, char *argv[])
{
    int i;
    char *displayname = NULL;
    Bool all_screens = False;
    Bool verbose = False;
    xcb_connection_t *dpy;
    const xcb_setup_t *setup;
    int screen_number = 0;
    int maxcmdlen = 10000;

    ProgramName = argv[0];

    for (i = 1; i < argc; i++) {
	char *arg = argv[i];

	if (arg[0] == '-') {
	    char *cp;

	    switch (arg[1]) {
	      case 'd':			/* -display dpyname */
		if (++i >= argc) usage ("-display requires an argument");
		displayname = argv[i];
		continue;
	      case 'm':			/* -max maxcmdlen */
		if (++i >= argc) usage ("-max requires an argument");
		maxcmdlen = atoi (argv[i]);
		continue;
	      case 'v':			/* -version */
		printf("%s\n", "1.1.5");
		exit(0);
	    }

	    for (cp = &arg[1]; *cp; cp++) {
		switch (*cp) {
		  case 'a':		/* -all */
		    all_screens = True;
		    continue;
		  case 'l':		/* -long */
		    verbose = True;
		    continue;
		  default:
		    fprintf (stderr, "%s: unrecognized argument -%s\n\n",
			     ProgramName, cp);
		    usage (NULL);
		}
	    }
	} else {
	    fprintf (stderr, "%s: unrecognized argument %s\n\n",
		     ProgramName, arg);
	    usage (NULL);
	}
    }

    dpy = xcb_connect(displayname, &screen_number);
    if (xcb_connection_has_error(dpy)) {
	const char *name = displayname;
	if (!name)
	    name = getenv("DISPLAY");
	if (!name)
	    name = "";
	fprintf (stderr, "%s:  unable to open display \"%s\"\r\n",
		 ProgramName, name);
	exit (1);
    }

    init_atoms(dpy);

    setup = xcb_get_setup(dpy);
    if (all_screens) {
	xcb_screen_iterator_t screen;

	screen = xcb_setup_roots_iterator(setup);
	do {
	    lookat(dpy, screen.data->root, verbose, maxcmdlen);
	    xcb_screen_next(&screen);
	} while (screen.rem);
    } else {
	xcb_screen_iterator_t screen;

	screen = xcb_setup_roots_iterator(setup);
	for (i = 0; i < screen_number; i++)
	    xcb_screen_next(&screen);

	lookat (dpy, screen.data->root, verbose, maxcmdlen);
    }

    run_queue();

    xcb_disconnect(dpy);
    exit (0);
}

typedef struct {
    xcb_connection_t *c;
    xcb_get_property_cookie_t *prop_cookie;
    xcb_query_tree_cookie_t *tree_cookie;
    xcb_window_t *win;
    xcb_window_t orig_win;
    unsigned int list_length;
    int verbose;
    int maxcmdlen;
} child_wm_state;

static void child_info(void *closure)
{
    child_wm_state *cs = closure;
    xcb_window_t orig = cs->orig_win;
    xcb_connection_t *c = cs->c;
    int verbose = cs->verbose;
    int maxcmdlen = cs->maxcmdlen;
    unsigned int i, j;

    unsigned int child_count, num_rep;
    xcb_query_tree_reply_t **qt_reply;

    for (i = 0; i < cs->list_length; i++) {
	xcb_get_property_reply_t *gp_reply;
	gp_reply = xcb_get_property_reply(c, cs->prop_cookie[i], NULL);
	if (gp_reply) {
	    if (gp_reply->type) {
		/* Show information for this window */
		print_client_properties(c, cs->win[i], cs->verbose, cs->maxcmdlen);

		free(gp_reply);

		/* drain stale replies */
		for (j = i+1; j < cs->list_length; j++) {
		    gp_reply = xcb_get_property_reply(c, cs->prop_cookie[j], NULL);
		    if (gp_reply)
			free(gp_reply);
		}
		for (j = 0; j < cs->list_length; j++) {
		    xcb_query_tree_reply_t *rep;
		    rep = xcb_query_tree_reply(c, cs->tree_cookie[j], NULL);
		    if (rep)
			free(rep);
		}
		goto done;
	    }
	    free(gp_reply);
	}
    }

    /* WM_STATE not found. Recurse into children: */
    num_rep = 0;
    qt_reply = malloc(sizeof(*qt_reply) * cs->list_length);
    if (!qt_reply)
	goto done; /* TODO: print OOM message, drain reply queue */

    for (i = 0; i < cs->list_length; i++) {
	qt_reply[num_rep] = xcb_query_tree_reply(c, cs->tree_cookie[i], NULL);
	if (qt_reply[num_rep])
	    num_rep++;
    }

    child_count = 0;
    for (i = 0; i < num_rep; i++)
	child_count += qt_reply[i]->children_len;

    if (!child_count) {
	/* No children have CS_STATE; try the parent window */
	print_client_properties(c, cs->orig_win, cs->verbose, cs->maxcmdlen);
	goto reply_done;
    }

    cs = malloc(sizeof(*cs) + child_count * (sizeof(*cs->prop_cookie) + sizeof(*cs->tree_cookie) + sizeof(*cs->win)));
    if (!cs)
	goto reply_done; /* TODO: print OOM message */

    cs->c = c;
    cs->verbose = verbose;
    cs->maxcmdlen = maxcmdlen;
    cs->orig_win = orig;
    cs->prop_cookie = (void *)&cs[1];
    cs->tree_cookie = (void *)&cs->prop_cookie[child_count];
    cs->win = (void *)&cs->tree_cookie[child_count];
    cs->list_length = child_count;

    child_count = 0;
    for (i = 0; i < num_rep; i++) {
	xcb_window_t *child = xcb_query_tree_children(qt_reply[i]);
	for (j = 0; j < qt_reply[i]->children_len; j++) {
	    cs->win[child_count] = child[j];
	    cs->prop_cookie[child_count] = xcb_get_property(c, 0, child[j],
			    WM_STATE, XCB_GET_PROPERTY_TYPE_ANY,
			    0, 0);
	    /* Just in case the property isn't there, get the tree too */
	    cs->tree_cookie[child_count++] = xcb_query_tree(c, child[j]);
	}
    }

    enqueue(child_info, cs);

reply_done:
    for (i = 0; i < num_rep; i++)
	free(qt_reply[i]);
    free(qt_reply);

done:
    free(closure);
}

typedef struct {
    xcb_connection_t *c;
    xcb_query_tree_cookie_t cookie;
    int verbose;
    int maxcmdlen;
} root_list_state;

static void root_list(void *closure)
{
    int i;
    xcb_window_t *child;
    xcb_query_tree_reply_t *reply;
    root_list_state *rl = closure;

    reply = xcb_query_tree_reply(rl->c, rl->cookie, NULL);
    if (!reply)
	goto done;

    child = xcb_query_tree_children(reply);
    for (i = 0; i < reply->children_len; i++) {
	/* Get information about each child */
	child_wm_state *cs = malloc(sizeof(*cs) + sizeof(*cs->prop_cookie) + sizeof(*cs->tree_cookie) + sizeof(*cs->win));
	if (!cs)
	    goto done; /* TODO: print OOM message */
	cs->c = rl->c;
	cs->verbose = rl->verbose;
	cs->maxcmdlen = rl->maxcmdlen;
	cs->prop_cookie = (void *)&cs[1];
	cs->tree_cookie = (void *)&cs->prop_cookie[1];
	cs->win = (void *)&cs->tree_cookie[1];

	cs->orig_win = child[i];
	cs->win[0] = child[i];

	cs->prop_cookie[0] = xcb_get_property(rl->c, 0, child[i],
			WM_STATE, XCB_GET_PROPERTY_TYPE_ANY,
			0, 0);
	/* Just in case the property isn't there, get the tree too */
	cs->tree_cookie[0] = xcb_query_tree(rl->c, child[i]);

	cs->list_length = 1;
	enqueue(child_info, cs);
    }
    free(reply);

done:
    free(rl);
}

static void
lookat(xcb_connection_t *dpy, xcb_window_t root, int verbose, int maxcmdlen)
{
    root_list_state *rl = malloc(sizeof(*rl));

    if (!rl)
	return; /* TODO: OOM message */

    /*
     * get the list of windows
     */

    rl->c = dpy;
    rl->cookie = xcb_query_tree(dpy, root);
    rl->verbose = verbose;
    rl->maxcmdlen = maxcmdlen;
    enqueue(root_list, rl);
}

static const char *Nil = "(nil)";

typedef struct {
    xcb_connection_t *c;
    xcb_get_property_cookie_t client_machine;
    xcb_get_property_cookie_t command;
    xcb_get_property_cookie_t name;
    xcb_get_property_cookie_t icon_name;
    xcb_get_property_cookie_t wm_class;
    xcb_window_t w;
    int verbose;
    int maxcmdlen;
} client_state;

static void
show_client_properties(void *closure)
{
    // PRE: true
    client_state *cs = closure;
    xcb_get_property_reply_t *client_machine;
    xcb_get_property_reply_t *command;
    xcb_get_property_reply_t *name = NULL;
    xcb_get_property_reply_t *icon_name = NULL;
    xcb_get_property_reply_t *wm_class = NULL;
    char *argv;
    int charsleft = cs->maxcmdlen;
    unsigned int i;

    /*
     * get the WM_MACHINE and WM_COMMAND list of strings
     */
    client_machine = xcb_get_property_reply(cs->c, cs->client_machine, NULL);
    command = xcb_get_property_reply(cs->c, cs->command, NULL);
    if (cs->verbose) {
	name = xcb_get_property_reply(cs->c, cs->name, NULL);
	icon_name = xcb_get_property_reply(cs->c, cs->icon_name, NULL);
	wm_class = xcb_get_property_reply(cs->c, cs->wm_class, NULL);
    }

    if (!command || !command->type)
	goto done;

    /*
     * do header information
     */
    if (cs->verbose) {
	printf ("Window 0x%" PRIx32 ":\n", cs->w);
	print_text_field (cs->c, "  Machine:  ", client_machine);
	if (name && name->type)
	    print_text_field (cs->c, "  Name:  ", name);
    } else {
	print_text_field (cs->c, NULL, client_machine);
	putchar (' ');
	putchar (' ');
    }


    if (cs->verbose)
	if (icon_name && icon_name->type)
	    print_text_field (cs->c, "  Icon Name:  ", icon_name);


    /*
     * do the command
     */
    if (cs->verbose)
	printf ("  Command:  ");
    argv = xcb_get_property_value(command);
    for (i = 0; i < command->value_len && charsleft > 0; ) {
	charsleft -= print_quoted_word (argv + i, charsleft);
	i += strnlen(argv + i, command->value_len - i) + 1;
	if (i < command->value_len && charsleft > 0) {
	    putchar (' ');
	    charsleft--;
	}
    }
    putchar ('\n');


    /*
     * do trailer information
     */
    if (cs->verbose) {
	if (wm_class && wm_class->type) {
	    const char *res_name, *res_class;
	    int name_len, class_len; /* Must be int for use with %.*s */
	    res_name = xcb_get_property_value(wm_class);
	    name_len = (int) strnlen(res_name, wm_class->value_len) + 1;
	    class_len = (int) wm_class->value_len - name_len;
	    if (class_len > 0) {
		res_class = res_name + name_len;
	    } else {
		res_class = Nil;
		class_len = (int) strlen(res_class);
	    }

	    printf ("  Instance/Class:  %.*s/%.*s",
		    name_len, res_name,
		    class_len, res_class);
	    putchar ('\n');
	}
    }

done:
    if (client_machine)
	free(client_machine);
    if (command)
	free(command);
    if (cs->verbose) {
	if (name)
	    free(name);
	if (icon_name)
	    free(icon_name);
	if (wm_class)
	    free(wm_class);
    }
    free(cs);
}

static void
print_client_properties(xcb_connection_t *dpy, xcb_window_t w, int verbose, int maxcmdlen)
{
    client_state *cs = malloc(sizeof(*cs));
    if (!cs)
	return; /* TODO: print OOM message */

    cs->c = dpy;
    cs->w = w;
    cs->verbose = verbose;
    cs->maxcmdlen = maxcmdlen;

    /*
     * get the WM_CLIENT_MACHINE and WM_COMMAND list of strings
     */
    cs->client_machine = xcb_get_property(dpy, 0, w,
			    XCB_ATOM_WM_CLIENT_MACHINE, XCB_GET_PROPERTY_TYPE_ANY,
			    0, 1000000L);
    cs->command = xcb_get_property(dpy, 0, w,
			    XCB_ATOM_WM_COMMAND, XCB_GET_PROPERTY_TYPE_ANY,
			    0, 1000000L);

    if (verbose) {
	cs->name = xcb_get_property(dpy, 0, w,
			    XCB_ATOM_WM_NAME, XCB_GET_PROPERTY_TYPE_ANY,
			    0, 1000000L);
	cs->icon_name = xcb_get_property(dpy, 0, w,
			    XCB_ATOM_WM_ICON_NAME, XCB_GET_PROPERTY_TYPE_ANY,
			    0, 1000000L);
	cs->wm_class = xcb_get_property(dpy, 0, w,
			    XCB_ATOM_WM_CLASS, XCB_ATOM_STRING,
			    0, 1000000L);
    }

    enqueue(show_client_properties, cs);
}

static void
print_text_field(xcb_connection_t *dpy, const char *s, xcb_get_property_reply_t *tp)
{
    // POST: tp != NULL
    if (tp->type == XCB_NONE || tp->format == 0) {  /* Or XCB_ATOM_NONE after libxcb 1.5 */
	printf ("''");
	return;
    }

    if (s) printf ("%s", s);
    if (tp->type == XCB_ATOM_STRING && tp->format == 8) {
	printf ("%.*s", (int)tp->value_len, (char *)xcb_get_property_value(tp));
    } else {
	unknown (dpy, tp->type, tp->format);
    }
    if (s) putchar ('\n');
}

/* returns the number of characters printed */
static int
print_quoted_word(char *s, 
		  int maxlen)		/* max number of chars we can print */
{
    register char *cp;
    Bool need_quote = False, in_quote = False;
    char quote_char = '\'', other_quote = '"';
    int charsprinted = 0;

    /*
     * walk down seeing whether or not we need to quote
     */
    for (cp = s; *cp; cp++) {

	if (! ((isascii(*cp) && isalnum(*cp)) || 
	       (*cp == '-' || *cp == '_' || *cp == '.' || *cp == '+' ||
		*cp == '/' || *cp == '=' || *cp == ':' || *cp == ','))) {
	    need_quote = True;
	    break;
	}
    }

    /*
     * write out the string: if we hit a quote, then close any previous quote,
     * emit the other quote, swap quotes and continue on.
     */
    in_quote = need_quote;
    if (need_quote) {
	putchar (quote_char);
	charsprinted++; maxlen--;
    }
    for (cp = s; *cp && maxlen>0; cp++) {
	if (*cp == quote_char) {
	    if (in_quote) {
		putchar (quote_char);
		charsprinted++; maxlen--;
	    }
	    putchar (other_quote);
	    charsprinted++; maxlen--;
	    { 
		char tmp = other_quote; 
		other_quote = quote_char; quote_char = tmp;
	    }
	    in_quote = True;
	}
	putchar (*cp);
	charsprinted++; maxlen--;
    }
    /* close the quote if we opened one and if we printed the whole string */
    if (in_quote && maxlen>0) {
	putchar (quote_char);
	charsprinted++; maxlen--;
    }

    return charsprinted;
}

static void
unknown(xcb_connection_t *dpy, xcb_atom_t actual_type, int actual_format)
{
    printf ("<unknown type ");
    if (actual_type == XCB_NONE)
	printf ("None");
    else {
	/* This should happen so rarely as to make no odds. Eat a round-trip: */
	xcb_get_atom_name_reply_t *atom =
	    xcb_get_atom_name_reply(dpy,
		xcb_get_atom_name(dpy, actual_type), NULL);
	if (atom) {
	    printf("%.*s", xcb_get_atom_name_name_length(atom),
			  xcb_get_atom_name_name(atom));
	    free(atom);
	} else
	    fputs (Nil, stdout);
    }
    printf (" (%" PRIu32 ") or format %d>", actual_type, actual_format);
}

