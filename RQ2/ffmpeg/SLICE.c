/* FILE: audio.c */
/*...*/
#include "libavutil/channel_layout.h"
/*...*/
#include "audio.h"
#include "avfilter.h"
#include "avfilter_internal.h"
#include "filters.h"
#include "framepool.h"

/*...*/
AVFrame *ff_default_get_audio_buffer(AVFilterLink *link, int nb_samples)
{
    AVFrame *frame = NULL;
    FilterLinkInternal *const li = ff_link_internal(link);
    /*...*/
    frame = ff_frame_pool_get(li->frame_pool);
    if (!frame)
        /*...*/;

    frame->nb_samples = nb_samples;
    if (link->ch_layout.order != AV_CHANNEL_ORDER_UNSPEC &&
        av_channel_layout_copy(&frame->ch_layout, &link->ch_layout) < 0) {
        /*...*/

    }
    frame->sample_rate = link->sample_rate;

    /*...*/
    return frame;
}

AVFrame *ff_get_audio_buffer(AVFilterLink *link, int nb_samples)
{
    AVFrame *ret = NULL;

    /*...*/
    if (!ret)
        ret = ff_default_get_audio_buffer(link, nb_samples);

    return ret;
}

/* FILE: buffer_internal.h */
/*...*/
#include "buffer.h"
/*...*/
typedef struct BufferPoolEntry {
    uint8_t *data;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    void *opaque;
    void (*free)(void *opaque, uint8_t *data);

    /*...*/
    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer buffer;
} BufferPoolEntry;

struct AVBufferPool {
    /*...*/
    void *opaque;
    /*...*/

};

/* FILE: buffer.c */
/*...*/
#include "buffer_internal.h"
/*...*/
static void pool_release_buffer(void *opaque, uint8_t *data)
{
    /*...*/

}

/*...*/
static AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    /*...*/
    ret->buffer->opaque = buf;
    ret->buffer->free   = pool_release_buffer;

    return ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    /*...*/
    if (buf) {
        /*...*/

    } else {
        ret = pool_alloc_buffer(pool);
    }
    /*...*/
    if (ret)
        /*...*/;

    return ret;
}

/* FILE: channel_layout.c */
/*...*/
#include "channel_layout.h"
/*...*/
#include "macros.h"
/*...*/
int av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src)
{
    /*...*/
    return 0;
}

/* FILE: framepool.c */
/*...*/
#include "framepool.h"
/*...*/
#include "libavutil/buffer.h"
#include "libavutil/frame.h"
/*...*/
struct FFFramePool {

    /*...*/
    int nb_samples;

    /*...*/
    int align;
    /*...*/
    AVBufferPool *pools[4];

};

/*...*/
AVFrame *ff_frame_pool_get(FFFramePool *pool)
{
    int i;
    AVFrame *frame;
    /*...*/
    switch(pool->type) {
    /*...*/
    case AVMEDIA_TYPE_AUDIO:
        /*...*/
        for (i = 0; i < FFMIN(pool->planes, AV_NUM_DATA_POINTERS); i++) {
            frame->buf[i] = av_buffer_pool_get(pool->pools[0]);
            if (!frame->buf[i])
                goto fail;
            frame->extended_data[i] = frame->data[i] =
                (uint8_t *)FFALIGN((uintptr_t)frame->buf[i]->data, pool->align);
        }
        for (i = 0; i < frame->nb_extended_buf; i++) {
            /*...*/

        }

        /*...*/

    }

    return frame;
fail:
    /*...*/;
    /*...*/

}

/* FILE: framepool.h */
/*...*/
#include "libavutil/buffer.h"
#include "libavutil/frame.h"
/*...*/
/**
 * Frame pool. This structure is opaque and not meant to be accessed
 * directly. It is allocated with ff_frame_pool_init() and freed with
 * ff_frame_pool_uninit().
 */
typedef struct FFFramePool FFFramePool;

/*...*/
AVFrame *ff_frame_pool_get(FFFramePool *pool);

/* FILE: avfilter_internal.h */
/*...*/
#include "avfilter.h"
#include "filters.h"
/*...*/
typedef struct FilterLinkInternal {
    /*...*/
    struct FFFramePool *frame_pool;

    /*...*/

} FilterLinkInternal;

/* FILE: avfilter.c */
/*...*/
#include "libavutil/buffer.h"
#include "libavutil/channel_layout.h"
/*...*/
#include "libavutil/frame.h"
/*...*/
#include "audio.h"
#include "avfilter.h"
#include "avfilter_internal.h"
#include "filters.h"
/*...*/
#include "framepool.h"
/*...*/
static int take_samples(FilterLinkInternal *li, unsigned min, unsigned max,
                        AVFrame **rframe)
{
    /*...*/
    AVFilterLink *link = &l->pub;
    AVFrame *frame0, *frame, *buf;
    unsigned nb_samples, nb_frames, i, p;
    /*...*/
    buf = ff_get_audio_buffer(link, nb_samples);
    if (!buf)
        /*...*/;
    /*...*/
    *rframe = buf;
    return 0;
}

/*...*/
int ff_inlink_consume_samples(AVFilterLink *link, unsigned min, unsigned max,
                            AVFrame **rframe)
{
    FilterLinkInternal * const li = ff_link_internal(link);
    AVFrame *frame;
    int ret;

    /*...*/
    ret = take_samples(li, min, max, &frame);
    /*...*/
    *rframe = frame;
    return 1;
}

/* FILE: avf_showcqt.h */
/*...*/
#include "avfilter.h"

/*...*/
typedef struct ShowCQTContext {
    /*...*/
    int                 remaining_fill;
    int                 remaining_fill_max;
    /*...*/
    AVComplexFloat      *fft_data;
    /*...*/
    int                 fft_len;
    /*...*/

} ShowCQTContext;

/* FILE: filters.h */
/*...*/
#include "avfilter.h"

/*...*/
int ff_inlink_consume_samples(AVFilterLink *link, unsigned min, unsigned max,
                            AVFrame **rframe);

/* FILE: avfilter.h */
/*...*/
#include "libavutil/buffer.h"
/*...*/
#include "libavutil/frame.h"
/*...*/
typedef struct AVFilterContext AVFilterContext;
typedef struct AVFilterLink    AVFilterLink;
/*...*/
/** An instance of a filter */
struct AVFilterContext {
    /*...*/
    void *priv;                     ///< private data for use by the filter

    /*...*/

};

/**
 * A link between two filters. This contains pointers to the source and
 * destination filters between which this link exists, and the indexes of
 * the pads involved. In addition, this link also contains the parameters
 * which have been negotiated and agreed upon between the filter, such as
 * image dimensions, format, etc.
 *
 * Applications must not normally access the link structure directly.
 * Use the buffersrc and buffersink API instead.
 * In the future, access to the header may be reserved for filters
 * implementation.
 */
struct AVFilterLink {
    /*...*/
    AVFilterContext *dst;       ///< dest filter
    /*...*/
    /* These parameters apply only to audio */
    int sample_rate;            ///< samples per second
    AVChannelLayout ch_layout;  ///< channel layout of current buffer (see libavutil/channel_layout.h)

    /*...*/

};

/* FILE: audio.h */
/*...*/
#include "avfilter.h"
#include "filters.h"

/*...*/
AVFrame *ff_default_get_audio_buffer(AVFilterLink *link, int nb_samples);

/*...*/
AVFrame *ff_get_audio_buffer(AVFilterLink *link, int nb_samples);

/* FILE: frame.h */
/*...*/
#include "buffer.h"
#include "channel_layout.h"
/*...*/
/**
 * This structure describes decoded (raw) audio or video data.
 *
 * AVFrame must be allocated using av_frame_alloc(). Note that this only
 * allocates the AVFrame itself, the buffers for the data must be managed
 * through other means (see below).
 * AVFrame must be freed with av_frame_free().
 *
 * AVFrame is typically allocated once and then reused multiple times to hold
 * different data (e.g. a single AVFrame to hold frames received from a
 * decoder). In such a case, av_frame_unref() will free any references held by
 * the frame and reset it to its original clean state before it
 * is reused again.
 *
 * The data described by an AVFrame is usually reference counted through the
 * AVBuffer API. The underlying buffer references are stored in AVFrame.buf /
 * AVFrame.extended_buf. An AVFrame is considered to be reference counted if at
 * least one reference is set, i.e. if AVFrame.buf[0] != NULL. In such a case,
 * every single data plane must be contained in one of the buffers in
 * AVFrame.buf or AVFrame.extended_buf.
 * There may be a single buffer for all the data, or one separate buffer for
 * each plane, or anything in between.
 *
 * sizeof(AVFrame) is not a part of the public ABI, so new fields may be added
 * to the end with a minor bump.
 *
 * Fields can be accessed through AVOptions, the name string used, matches the
 * C structure field name for fields accessible through AVOptions.
 */
typedef struct AVFrame {
#define AV_NUM_DATA_POINTERS 8
    /**
     * pointer to the picture/channel planes.
     * This might be different from the first allocated byte. For video,
     * it could even point to the end of the image data.
     *
     * All pointers in data and extended_data must point into one of the
     * AVBufferRef in buf or extended_buf.
     *
     * Some decoders access areas outside 0,0 - width,height, please
     * see avcodec_align_dimensions2(). Some filters and swscale can read
     * up to 16 bytes beyond the planes, if these filters are to be used,
     * then 16 extra bytes must be allocated.
     *
     * NOTE: Pointers not needed by the format MUST be set to NULL.
     *
     * @attention In case of video, the data[] pointers can point to the
     * end of image data in order to reverse line order, when used in
     * combination with negative values in the linesize[] array.
     */
    uint8_t *data[AV_NUM_DATA_POINTERS];

    /*...*/
    /**
     * pointers to the data planes/channels.
     *
     * For video, this should simply point to data[].
     *
     * For planar audio, each channel has a separate data pointer, and
     * linesize[0] contains the size of each channel buffer.
     * For packed audio, there is just one data pointer, and linesize[0]
     * contains the total size of the buffer for all channels.
     *
     * Note: Both data and extended_data should always be set in a valid frame,
     * but for planar audio with more channels that can fit in data,
     * extended_data must be used in order to access all channels.
     */
    uint8_t **extended_data;

    /*...*/
    /**
     * number of audio samples (per channel) described by this frame
     */
    int nb_samples;

    /*...*/
    /**
     * Frame owner's private data.
     *
     * This field may be set by the code that allocates/owns the frame data.
     * It is then not touched by any library functions, except:
     * - it is copied to other references by av_frame_copy_props() (and hence by
     *   av_frame_ref());
     * - it is set to NULL when the frame is cleared by av_frame_unref()
     * - on the caller's explicit request. E.g. libavcodec encoders/decoders
     *   will copy this field to/from @ref AVPacket "AVPackets" if the caller sets
     *   @ref AV_CODEC_FLAG_COPY_OPAQUE.
     *
     * @see opaque_ref the reference-counted analogue
     */
    void *opaque;

    /*...*/
    /**
     * Sample rate of the audio data.
     */
    int sample_rate;

    /**
     * AVBuffer references backing the data for this frame. All the pointers in
     * data and extended_data must point inside one of the buffers in buf or
     * extended_buf. This array must be filled contiguously -- if buf[i] is
     * non-NULL then buf[j] must also be non-NULL for all j < i.
     *
     * There may be at most one AVBuffer per data plane, so for video this array
     * always contains all the references. For planar audio with more than
     * AV_NUM_DATA_POINTERS channels, there may be more buffers than can fit in
     * this array. Then the extra AVBufferRef pointers are stored in the
     * extended_buf array.
     */
    AVBufferRef *buf[AV_NUM_DATA_POINTERS];

    /*...*/
    /**
     * Number of elements in extended_buf.
     */
    int        nb_extended_buf;

    /*...*/
    /**
     * Channel layout of the audio data.
     */
    AVChannelLayout ch_layout;

    /*...*/

} AVFrame;

/* FILE: buffer.h */
/*...*/
/**
 * A reference to a data buffer.
 *
 * The size of this struct is not a part of the public ABI and it is not meant
 * to be allocated directly.
 */
typedef struct AVBufferRef {
    AVBuffer *buffer;

    /**
     * The data buffer. It is considered writable if and only if
     * this is the only reference to the buffer, in which case
     * av_buffer_is_writable() returns 1.
     */
    uint8_t *data;
    /*...*/

} AVBufferRef;

/*...*/
/**
 * @}
 */

/**
 * @defgroup lavu_bufferpool AVBufferPool
 * @ingroup lavu_data
 *
 * @{
 * AVBufferPool is an API for a lock-free thread-safe pool of AVBuffers.
 *
 * Frequently allocating and freeing large buffers may be slow. AVBufferPool is
 * meant to solve this in cases when the caller needs a set of buffers of the
 * same size (the most obvious use case being buffers for raw video or audio
 * frames).
 *
 * At the beginning, the user must call av_buffer_pool_init() to create the
 * buffer pool. Then whenever a buffer is needed, call av_buffer_pool_get() to
 * get a reference to a new buffer, similar to av_buffer_alloc(). This new
 * reference works in all aspects the same way as the one created by
 * av_buffer_alloc(). However, when the last reference to this buffer is
 * unreferenced, it is returned to the pool instead of being freed and will be
 * reused for subsequent av_buffer_pool_get() calls.
 *
 * When the caller is done with the pool and no longer needs to allocate any new
 * buffers, av_buffer_pool_uninit() must be called to mark the pool as freeable.
 * Once all the buffers are released, it will automatically be freed.
 *
 * Allocating and releasing buffers with this API is thread-safe as long as
 * either the default alloc callback is used, or the user-supplied one is
 * thread-safe.
 */

/**
 * The buffer pool. This structure is opaque and not meant to be accessed
 * directly. It is allocated with av_buffer_pool_init() and freed with
 * av_buffer_pool_uninit().
 */
typedef struct AVBufferPool AVBufferPool;

/*...*/
AVBufferRef *av_buffer_pool_get(AVBufferPool *pool);

/* FILE: avformat.h */
/*...*/
#include "libavutil/frame.h"
/*...*/
struct AVFrame;

/* FILE: macros.h */
/*...*/
#define FFALIGN(x, a) (((x)+(a)-1)&~((a)-1))


/* FILE: channel_layout.h */
/*...*/
enum AVChannelOrder {
    /**
     * Only the channel count is specified, without any further information
     * about the channel order.
     */
    AV_CHANNEL_ORDER_UNSPEC,
    /*...*/

};


/*...*/
/**
 * An AVChannelLayout holds information about the channel layout of audio data.
 *
 * A channel layout here is defined as a set of channels ordered in a specific
 * way (unless the channel order is AV_CHANNEL_ORDER_UNSPEC, in which case an
 * AVChannelLayout carries only the channel count).
 * All orders may be treated as if they were AV_CHANNEL_ORDER_UNSPEC by
 * ignoring everything but the channel count, as long as av_channel_layout_check()
 * considers they are valid.
 *
 * Unlike most structures in FFmpeg, sizeof(AVChannelLayout) is a part of the
 * public ABI and may be used by the caller. E.g. it may be allocated on stack
 * or embedded in caller-defined structs.
 *
 * AVChannelLayout can be initialized as follows:
 * - default initialization with {0}, followed by setting all used fields
 *   correctly;
 * - by assigning one of the predefined AV_CHANNEL_LAYOUT_* initializers;
 * - with a constructor function, such as av_channel_layout_default(),
 *   av_channel_layout_from_mask() or av_channel_layout_from_string().
 *
 * The channel layout must be unitialized with av_channel_layout_uninit()
 *
 * Copying an AVChannelLayout via assigning is forbidden,
 * av_channel_layout_copy() must be used instead (and its return value should
 * be checked)
 *
 * No new fields may be added to it without a major version bump, except for
 * new elements of the union fitting in sizeof(uint64_t).
 */
typedef struct AVChannelLayout {
    /**
     * Channel order used in this layout.
     * This is a mandatory field.
     */
    enum AVChannelOrder order;

    /*...*/
    /**
     * For some private data of the user.
     */
    void *opaque;
} AVChannelLayout;

/*...*/
int av_channel_layout_copy(AVChannelLayout *dst, const AVChannelLayout *src);

/* FILE: avf_showcqt.c */
/*...*/
#include "libavutil/channel_layout.h"
/*...*/
#include "audio.h"
#include "avfilter.h"
#include "filters.h"
/*...*/
#include "avf_showcqt.h"

/*...*/
static int filter_frame(AVFilterLink *inlink, AVFrame *insamples)
{
    AVFilterContext *ctx = inlink->dst;
    /*...*/
    ShowCQTContext *s = ctx->priv;
    int remaining, step, ret, x, i, j, m, got_frame = 0;
    float *audio_data;
    /*...*/
    if (!insamples) {
        /*...*/

    }

    remaining = insamples->nb_samples;
    audio_data = (float*) insamples->data[0];

    while (remaining) {
        i = insamples->nb_samples - remaining;
        j = s->fft_len/2 + s->remaining_fill_max - s->remaining_fill;
        if (remaining >= s->remaining_fill) {
            for (m = 0; m < s->remaining_fill; m++) {
                s->fft_data[j+m].re = audio_data[2*(i+m)];      /* CRASH LOCATION */
                /*...*/

            }
            /*...*/

        } else {
            /*...*/

        }
    }
    /*...*/

}

static int activate(AVFilterContext *ctx)
{
    AVFilterLink *inlink = ctx->inputs[0];
    /*...*/
    int nb_samples, ret, status;
    /*...*/
    AVFrame *in;

    /*...*/
    ret = ff_inlink_consume_samples(inlink, nb_samples, nb_samples, &in);
    /*...*/
    if (ret > 0)
        return filter_frame(inlink, in);

    /*...*/

}
