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
 * Copyright (c) 1999, 2010, Oracle and/or its affiliates.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*

Copyright 1987, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

Except as contained in this notice, the name of a copyright holder
shall not be used in advertising or otherwise to promote the sale, use
or other dealings in this Software without prior written authorization
of the copyright holder.

*/


/*
 * xwininfo.c	- MIT Project Athena, X Window system window
 *		  information utility.
 *
 *
 *	This program will report all relevant information
 *	about a specific window.
 *
 *  Author:	Mark Lillibridge, MIT Project Athena
 *		16-Jun-87
 */

#include "config.h"

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#ifdef USE_XCB_ICCCM
# include <xcb/xcb_icccm.h>
#endif
#include <xcb/shape.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <langinfo.h>
#ifdef HAVE_ICONV
# include <iconv.h>
#endif
#include <ctype.h>
#include <errno.h>

/*

Copyright 1993, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

/*
 * dsimple.h: This file contains the definitions needed to use the
 *            functions in dsimple.c.  It also declares the global
 *            variable program_name which is needed to use dsimple.c.
 *
 * Written by Mark Lillibridge for Xlib.   Last updated 7/1/87
 * Ported to XCB over two decades later.
 */

#include <X11/Xfuncproto.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

typedef enum { False = 0, True } Bool;

    /* Global variables used by routines in dsimple.c */

extern const char *program_name;             /* Name of this program */

    /* Declarations for functions in dsimple.c */

const char *Get_Display_Name (const char *displayname);
void Setup_Display_And_Screen (const char *displayname,
			       xcb_connection_t **dpy, xcb_screen_t **screen);

xcb_window_t Select_Window (xcb_connection_t *, const xcb_screen_t *, int);
xcb_window_t Window_With_Name (xcb_connection_t *, xcb_window_t, const char *);

void Fatal_Error (const char *, ...) _X_NORETURN _X_ATTRIBUTE_PRINTF(1, 2) _X_COLD;

void Print_X_Error (xcb_connection_t *, xcb_generic_error_t *);

struct atom_cache_entry *Intern_Atom (xcb_connection_t *, const char *);
xcb_atom_t Get_Atom (xcb_connection_t *, const char *);
const char *Get_Atom_Name (xcb_connection_t *, xcb_atom_t);

/* Include routines to handle parsing defaults */
/*
 * Copyright 2007 Kim woelders
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */
#include <xcb/xcb.h>
#include <xcb/xproto.h>

#include <stdlib.h>
#include <string.h>

static xcb_atom_t atom_wm_state = XCB_ATOM_NONE;

/*
 * Check if window has given property
 */
static Bool
Window_Has_Property(xcb_connection_t * dpy, xcb_window_t win, xcb_atom_t atom)
{
    xcb_get_property_cookie_t prop_cookie;
    xcb_get_property_reply_t *prop_reply;

    prop_cookie = xcb_get_property (dpy, False, win, atom,
                                    XCB_GET_PROPERTY_TYPE_ANY, 0, 0);

    prop_reply = xcb_get_property_reply (dpy, prop_cookie, NULL);

    if (prop_reply) {
        xcb_atom_t reply_type = prop_reply->type;
        free (prop_reply);
        if (reply_type != XCB_NONE)
            return True;
    }

    return False;
}

/*
 * Check if window is viewable
 */
static Bool
Window_Is_Viewable(xcb_connection_t * dpy, xcb_window_t win)
{
    Bool ok = False;
    xcb_get_window_attributes_cookie_t attr_cookie;
    xcb_get_window_attributes_reply_t *xwa;

    attr_cookie = xcb_get_window_attributes (dpy, win);
    xwa = xcb_get_window_attributes_reply (dpy, attr_cookie, NULL);

    if (xwa) {
        ok = (xwa->_class == XCB_WINDOW_CLASS_INPUT_OUTPUT) &&
            (xwa->map_state == XCB_MAP_STATE_VIEWABLE);
        free (xwa);
    }

    return ok;
}

/*
 * Find a window that has WM_STATE set in the window tree below win.
 * Unmapped/unviewable windows are not considered valid matches.
 * Children are searched in top-down stacking order.
 * The first matching window is returned, None if no match is found.
 */
static xcb_window_t
Find_Client_In_Children(xcb_connection_t * dpy, xcb_window_t win)
{
    xcb_query_tree_cookie_t qt_cookie;
    xcb_query_tree_reply_t *tree;
    xcb_window_t *children;
    unsigned int n_children;
    int i;

    qt_cookie = xcb_query_tree (dpy, win);
    tree = xcb_query_tree_reply (dpy, qt_cookie, NULL);
    if (!tree)
        return XCB_WINDOW_NONE;
    n_children = xcb_query_tree_children_length (tree);
    if (!n_children) {
        free (tree);
        return XCB_WINDOW_NONE;
    }
    children = xcb_query_tree_children (tree);

    /* Check each child for WM_STATE and other validity */
    win = XCB_WINDOW_NONE;
    for (i = (int) n_children - 1; i >= 0; i--) {
        if (!Window_Is_Viewable(dpy, children[i])) {
            /* Don't bother descending into this one */
            children[i] = XCB_WINDOW_NONE;
            continue;
        }
        if (!Window_Has_Property(dpy, children[i], atom_wm_state))
            continue;

        /* Got one */
        win = children[i];
        goto done;
    }

    /* No children matched, now descend into each child */
    for (i = (int) n_children - 1; i >= 0; i--) {
        if (children[i] == XCB_WINDOW_NONE)
            continue;
        win = Find_Client_In_Children(dpy, children[i]);
        if (win != XCB_WINDOW_NONE)
            break;
    }

  done:
    free (tree); /* includes children */

    return win;
}

/*
 * Find virtual roots (_NET_VIRTUAL_ROOTS)
 */
static xcb_window_t *
Find_Roots(xcb_connection_t * dpy, xcb_window_t root, unsigned int *num)
{
    xcb_atom_t atom_virtual_root;

    xcb_get_property_cookie_t prop_cookie;
    xcb_get_property_reply_t *prop_reply;

    xcb_window_t *prop_ret = NULL;

    *num = 0;

    atom_virtual_root = Get_Atom (dpy, "_NET_VIRTUAL_ROOTS");
    if (atom_virtual_root == XCB_ATOM_NONE)
        return NULL;

    prop_cookie = xcb_get_property (dpy, False, root, atom_virtual_root,
                                    XCB_ATOM_WINDOW, 0, 0x7fffffff);
    prop_reply = xcb_get_property_reply (dpy, prop_cookie, NULL);
    if (!prop_reply)
        return NULL;

    if ((prop_reply->value_len > 0) && (prop_reply->type == XCB_ATOM_WINDOW)
        && (prop_reply->format == 32)) {
        int length = xcb_get_property_value_length (prop_reply);
        prop_ret = malloc(length);
        if (prop_ret) {
            memcpy (prop_ret, xcb_get_property_value(prop_reply), length);
            *num = prop_reply->value_len;
        }
    }
    free (prop_reply);

    return prop_ret;
}

/*
 * Find child window at pointer location
 */
static xcb_window_t
Find_Child_At_Pointer(xcb_connection_t * dpy, xcb_window_t win)
{
    xcb_window_t child_return = XCB_WINDOW_NONE;

    xcb_query_pointer_cookie_t qp_cookie;
    xcb_query_pointer_reply_t *qp_reply;

    qp_cookie = xcb_query_pointer (dpy, win);
    qp_reply = xcb_query_pointer_reply (dpy, qp_cookie, NULL);

    if (qp_reply) {
        child_return = qp_reply->child;
        free (qp_reply);
    }

    return child_return;
}

/*
 * Find client window at pointer location
 *
 * root   is the root window.
 * subwin is the subwindow reported by a ButtonPress event on root.
 *
 * If the WM uses virtual roots subwin may be a virtual root.
 * If so, we descend the window stack at the pointer location and assume the
 * child is the client or one of its WM frame windows.
 * This will of course work only if the virtual roots are children of the real
 * root.
 */
xcb_window_t
Find_Client(xcb_connection_t * dpy, xcb_window_t root, xcb_window_t subwin)
{
    xcb_window_t *roots;
    unsigned int i, n_roots;
    xcb_window_t win;

    /* Check if subwin is a virtual root */
    roots = Find_Roots(dpy, root, &n_roots);
    for (i = 0; i < n_roots; i++) {
        if (subwin != roots[i])
            continue;
        win = Find_Child_At_Pointer(dpy, subwin);
        if (win == XCB_WINDOW_NONE) {
            free (roots);
            return subwin;      /* No child - Return virtual root. */
        }
        subwin = win;
        break;
    }
    free (roots);

    if (atom_wm_state == XCB_ATOM_NONE) {
        atom_wm_state = Get_Atom(dpy, "WM_STATE");
        if (atom_wm_state == XCB_ATOM_NONE)
            return subwin;
    }

    /* Check if subwin has WM_STATE */
    if (Window_Has_Property(dpy, subwin, atom_wm_state))
        return subwin;

    /* Attempt to find a client window in subwin's children */
    win = Find_Client_In_Children(dpy, subwin);
    if (win != XCB_WINDOW_NONE)
        return win;             /* Found a client */

    /* Did not find a client */
    return subwin;
}



/*
 * Copyright (c) 2010, 2023, Oracle and/or its affiliates.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*

Copyright 1993, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#include "config.h"

#include <xcb/xcb.h>
#include <xcb/xproto.h>
#ifdef USE_XCB_ICCCM
# include <xcb/xcb_icccm.h>
#endif
#ifdef USE_XCB_ERRORS
# include <xcb/xcb_errors.h>
#endif
#include <X11/cursorfont.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/*
 * Just_display: A group of routines designed to make the writing of simple
 *               X11 applications which open a display but do not open
 *               any windows much faster and easier.  Unless a routine says
 *               otherwise, it may be assumed to require program_name
 *               to be already defined on entry.
 *
 * Written by Mark Lillibridge.   Last updated 7/1/87
 */

#ifdef USE_XCB_ERRORS
xcb_errors_context_t *error_context;
#endif

/* This stuff is defined in the calling program by dsimple.h */
const char    *program_name = "unknown_program";

/*
 * Get_Display_Name (argc, argv) - return string representing display name
 * that would be used given the specified argument (i.e. if it's NULL, check
 * getenv("DISPLAY") - always returns a non-NULL pointer, though it may be
 * an unwritable constant, so is safe to printf() on platforms that crash
 * on NULL printf arguments.
 */
const char *Get_Display_Name (const char *display_name)
{
    const char *name = display_name;

    if (!name) {
	name = getenv ("DISPLAY");
	if (!name)
	    name = "";
    }
    return (name);
}


/*
 * Setup_Display_And_Screen: This routine opens up the correct display (i.e.,
 *                           it calls Get_Display_Name) and then stores a
 *                           pointer to it in dpy.  The default screen
 *                           for this display is then stored in screen.
 */
void Setup_Display_And_Screen (
    const char *display_name,
    xcb_connection_t **dpy,	/* MODIFIED */
    xcb_screen_t **screen)	/* MODIFIED */
{
    int screen_number, err;

    /* Open Display */
    *dpy = xcb_connect (display_name, &screen_number);
    if ((err = xcb_connection_has_error (*dpy)) != 0) {
        switch (err) {
        case XCB_CONN_CLOSED_MEM_INSUFFICIENT:
            Fatal_Error ("Failed to allocate memory in xcb_connect");
        case XCB_CONN_CLOSED_PARSE_ERR:
            Fatal_Error ("unable to parse display name \"%s\"",
                         Get_Display_Name(display_name) );
#ifdef XCB_CONN_CLOSED_INVALID_SCREEN
        case XCB_CONN_CLOSED_INVALID_SCREEN:
            Fatal_Error ("invalid screen %d in display \"%s\"",
                         screen_number, Get_Display_Name(display_name));
#endif
        default:
            Fatal_Error ("unable to open display \"%s\"",
                         Get_Display_Name(display_name) );
        }
    }

#ifdef USE_XCB_ERRORS
    if (xcb_errors_context_new(*dpy, &error_context) != 0) {
	fprintf (stderr, "%s: unable to load xcb-errors\n\n",
                 program_name);
    }
#endif

    if (screen) {
	/* find our screen */
	const xcb_setup_t *setup = xcb_get_setup(*dpy);
	xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(setup);
	int screen_count = xcb_setup_roots_length(setup);
	if (screen_count <= screen_number)
	{
	    Fatal_Error ("unable to access screen %d, max is %d",
			 screen_number, screen_count-1 );
	}

	for (int i = 0; i < screen_number; i++)
	    xcb_screen_next(&screen_iter);
	*screen = screen_iter.data;
    }
}

/*
 * xcb equivalent of XCreateFontCursor
 */
static xcb_cursor_t
Create_Font_Cursor (xcb_connection_t *dpy, uint16_t glyph)
{
    static xcb_font_t cursor_font;
    xcb_cursor_t cursor;

    if (!cursor_font) {
	cursor_font = xcb_generate_id (dpy);
	xcb_open_font (dpy, cursor_font, strlen ("cursor"), "cursor");
    }

    cursor = xcb_generate_id (dpy);
    xcb_create_glyph_cursor (dpy, cursor, cursor_font, cursor_font,
			     glyph, glyph + 1,
                             0, 0, 0, 0xffff, 0xffff, 0xffff);  /* rgb, rgb */

    return cursor;
}

/*
 * Routine to let user select a window using the mouse
 */

xcb_window_t Select_Window(xcb_connection_t *dpy,
			   const xcb_screen_t *screen,
			   int descend)
{
    xcb_cursor_t cursor;
    xcb_window_t target_win = XCB_WINDOW_NONE;
    xcb_window_t root = screen->root;
    int buttons = 0;
    xcb_generic_error_t *err;
    xcb_grab_pointer_cookie_t grab_cookie;
    xcb_grab_pointer_reply_t *grab_reply;

    /* Make the target cursor */
    cursor = Create_Font_Cursor (dpy, XC_crosshair);

    /* Grab the pointer using target cursor, letting it room all over */
    grab_cookie = xcb_grab_pointer
	(dpy, False, root,
	 XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE,
	 XCB_GRAB_MODE_SYNC, XCB_GRAB_MODE_ASYNC,
	 root, cursor, XCB_TIME_CURRENT_TIME);
    grab_reply = xcb_grab_pointer_reply (dpy, grab_cookie, &err);
    if (grab_reply->status != XCB_GRAB_STATUS_SUCCESS)
	Fatal_Error ("Can't grab the mouse.");

    /* Let the user select a window... */
    while ((target_win == XCB_WINDOW_NONE) || (buttons != 0)) {
	/* allow one more event */
	xcb_generic_event_t *event;

	xcb_allow_events (dpy, XCB_ALLOW_SYNC_POINTER, XCB_TIME_CURRENT_TIME);
	xcb_flush (dpy);
	event = xcb_wait_for_event (dpy);
	if (event == NULL)
	    Fatal_Error ("Fatal IO error");
	switch (event->response_type & 0x7f) {
	case XCB_BUTTON_PRESS:
	{
	    xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;

	    if (target_win == XCB_WINDOW_NONE) {
		target_win = bp->child; /* window selected */
		if (target_win == XCB_WINDOW_NONE)
		    target_win = root;
	    }
	    buttons++;
	    break;
	}
	case XCB_BUTTON_RELEASE:
	    if (buttons > 0) /* there may have been some down before we started */
		buttons--;
	    break;
	default:
	    /* just discard all other events */
	    break;
	}
	free (event);
    }

    xcb_ungrab_pointer (dpy, XCB_TIME_CURRENT_TIME); /* Done with pointer */

    if (!descend || (target_win == root))
	return (target_win);

    target_win = Find_Client (dpy, root, target_win);

    return (target_win);
}


/*
 * Window_With_Name: routine to locate a window with a given name on a display.
 *                   If no window with the given name is found, 0 is returned.
 *                   If more than one window has the given name, the first
 *                   one found will be returned.  Only top and its subwindows
 *                   are looked at.  Normally, top should be the RootWindow.
 */

struct wininfo_cookies {
    xcb_get_property_cookie_t get_net_wm_name;
    xcb_get_property_cookie_t get_wm_name;
    xcb_query_tree_cookie_t query_tree;
};

#ifndef USE_XCB_ICCCM
# define xcb_icccm_get_wm_name(Dpy, Win) \
    xcb_get_property (Dpy, False, Win, XCB_ATOM_WM_NAME, \
		      XCB_GET_PROPERTY_TYPE_ANY, 0, BUFSIZ)
#endif

static xcb_atom_t atom_net_wm_name, atom_utf8_string;

# define xcb_get_net_wm_name(Dpy, Win)			 \
    xcb_get_property (Dpy, False, Win, atom_net_wm_name, \
		      atom_utf8_string, 0, BUFSIZ)


static xcb_window_t
recursive_Window_With_Name  (
    xcb_connection_t *dpy,
    xcb_window_t window,
    struct wininfo_cookies *cookies,
    const char *name,
    size_t namelen)
{
    xcb_window_t *children;
    unsigned int nchildren;
    unsigned int i;
    xcb_window_t w = 0;
    xcb_generic_error_t *err;
    xcb_query_tree_reply_t *tree;
    struct wininfo_cookies *child_cookies;
    xcb_get_property_reply_t *prop;

    if (cookies->get_net_wm_name.sequence) {
	prop = xcb_get_property_reply (dpy, cookies->get_net_wm_name, &err);

	if (prop) {
	    if (prop->type == atom_utf8_string) {
		const char *prop_name = xcb_get_property_value (prop);
		int prop_name_len = xcb_get_property_value_length (prop);

		/* can't use strcmp, since prop.name is not null terminated */
		if ((namelen == (size_t) prop_name_len) &&
		    memcmp (prop_name, name, namelen) == 0) {
		    w = window;
		}
	    }
	    free (prop);
	} else if (err) {
	    if (err->response_type == 0)
		Print_X_Error (dpy, err);
	    return 0;
	}
    }

    if (w) {
	xcb_discard_reply (dpy, cookies->get_wm_name.sequence);
    } else {
#ifdef USE_XCB_ICCCM
	xcb_icccm_get_text_property_reply_t nameprop;

	if (xcb_icccm_get_wm_name_reply (dpy, cookies->get_wm_name,
					 &nameprop, &err)) {
	    /* can't use strcmp, since nameprop.name is not null terminated */
	    if ((namelen == (size_t) nameprop.name_len) &&
		memcmp (nameprop.name, name, namelen) == 0) {
		w = window;
	    }

	    xcb_icccm_get_text_property_reply_wipe (&nameprop);
	}
#else
	prop = xcb_get_property_reply (dpy, cookies->get_wm_name, &err);

	if (prop) {
	    if (prop->type == XCB_ATOM_STRING) {
		const char *prop_name = xcb_get_property_value (prop);
		int prop_name_len = xcb_get_property_value_length (prop);

		/* can't use strcmp, since prop.name is not null terminated */
		if ((namelen == (size_t) prop_name_len) &&
		    memcmp (prop_name, name, namelen) == 0) {
		    w = window;
		}
	    }
	    free (prop);
	}
#endif
	else if (err) {
	    if (err->response_type == 0)
		Print_X_Error (dpy, err);
	    return 0;
	}
    }

    if (w)
    {
	xcb_discard_reply (dpy, cookies->query_tree.sequence);
	return w;
    }

    tree = xcb_query_tree_reply (dpy, cookies->query_tree, &err);
    if (!tree) {
	if (err->response_type == 0)
	    Print_X_Error (dpy, err);
	return 0;
    }

    nchildren = xcb_query_tree_children_length (tree);
    children = xcb_query_tree_children (tree);
    child_cookies = calloc(nchildren, sizeof(struct wininfo_cookies));

    if (child_cookies == NULL)
	Fatal_Error("Failed to allocate memory in recursive_Window_With_Name");

    for (i = 0; i < nchildren; i++) {
	if (atom_net_wm_name && atom_utf8_string)
	    child_cookies[i].get_net_wm_name =
		xcb_get_net_wm_name (dpy, children[i]);
	child_cookies[i].get_wm_name = xcb_icccm_get_wm_name (dpy, children[i]);
	child_cookies[i].query_tree = xcb_query_tree (dpy, children[i]);
    }
    xcb_flush (dpy);

    for (i = 0; i < nchildren; i++) {
	w = recursive_Window_With_Name (dpy, children[i],
					&child_cookies[i], name, namelen);
	if (w)
	    break;
    }

    if (w)
    {
	/* clean up remaining replies */
	for (/* keep previous i */; i < nchildren; i++) {
	    if (child_cookies[i].get_net_wm_name.sequence)
		xcb_discard_reply (dpy,
				   child_cookies[i].get_net_wm_name.sequence);
	    xcb_discard_reply (dpy, child_cookies[i].get_wm_name.sequence);
	    xcb_discard_reply (dpy, child_cookies[i].query_tree.sequence);
	}
    }

    free (child_cookies);
    free (tree); /* includes storage for children[] */
    return (w);
}

xcb_window_t
Window_With_Name (
    xcb_connection_t *dpy,
    xcb_window_t top,
    const char *name)
{
    struct wininfo_cookies cookies;

    atom_net_wm_name = Get_Atom (dpy, "_NET_WM_NAME");
    atom_utf8_string = Get_Atom (dpy, "UTF8_STRING");

    if (atom_net_wm_name && atom_utf8_string)
	cookies.get_net_wm_name = xcb_get_net_wm_name (dpy, top);
    else
	cookies.get_net_wm_name.sequence = 0;
    cookies.get_wm_name = xcb_icccm_get_wm_name (dpy, top);
    cookies.query_tree = xcb_query_tree (dpy, top);
    xcb_flush (dpy);
    return recursive_Window_With_Name(dpy, top, &cookies, name, strlen(name));
}


/*
 * Standard fatal error routine - call like printf
 */
void Fatal_Error (const char *msg, ...)
{
    va_list args;
    fflush (stdout);
    fflush (stderr);
    fprintf (stderr, "%s: error: ", program_name);
    va_start (args, msg);
    vfprintf (stderr, msg, args);
    va_end (args);
    fprintf (stderr, "\n");
    exit (EXIT_FAILURE);
}

/*
 * Descriptions for core protocol error codes
 *
 * Since 0 is not used for an error code in X, we use it for unknown error.
 */
#define UNKNOWN_ERROR 0
#define LAST_ERROR XCB_IMPLEMENTATION

static const char *error_desc[] = {
    [UNKNOWN_ERROR] = "Unknown error",
    [XCB_REQUEST] = "Bad Request",
    [XCB_VALUE] = "Bad Value",
    [XCB_WINDOW] = "Bad Window",
    [XCB_PIXMAP] = "Bad Pixmap",
    [XCB_ATOM] = "Bad Atom",
    [XCB_CURSOR] = "Bad Cursor",
    [XCB_FONT] = "Bad Font",
    [XCB_MATCH] = "Bad Match",
    [XCB_DRAWABLE] = "Bad Drawable",
    [XCB_ACCESS] = "Access Denied",
    [XCB_ALLOC] = "Server Memory Allocation Failure",
    [XCB_COLORMAP] = "Bad Color",
    [XCB_G_CONTEXT] = "Bad GC",
    [XCB_ID_CHOICE] = "Bad XID",
    [XCB_NAME] = "Bad Name",
    [XCB_LENGTH] = "Bad Request Length",
    [XCB_IMPLEMENTATION] = "Server Implementation Failure",
};

/*
 * Print X error information like the default Xlib error handler
 */
void
Print_X_Error (
    xcb_connection_t *dpy,
    xcb_generic_error_t *err
    )
{
    const char *error = NULL;
    const char *extension = NULL;
    const char *value_type = NULL;
    const char *major_name = NULL;
    const char *minor_name = NULL;

    if ((err == NULL) || (err->response_type != 0)) /* not an error */
	return;

#ifdef USE_XCB_ERRORS
    if (error_context != NULL) {
	error = xcb_errors_get_name_for_error(error_context, err->error_code,
					      &extension);
	major_name = xcb_errors_get_name_for_major_code(error_context,
							err->major_code);
	minor_name = xcb_errors_get_name_for_minor_code(error_context,
							err->major_code,
							err->minor_code);
    }
    /* Fallback to old code if xcb-errors wasn't initialized */
    else
#endif
    if (err->error_code >= 128)
    {
	error = "Unknown extension error";
    }
    else
    {
	if (err->error_code > 0 && err->error_code <= LAST_ERROR) {
	    error = error_desc[err->error_code];
	} else {
	    error = error_desc[UNKNOWN_ERROR];
	}
    }

    fprintf (stderr, "X Error: %d: %s\n", err->error_code, error);
    if (extension != NULL) {
	fprintf (stderr, "  Request extension: %s\n", extension);
    }

    fprintf (stderr, "  Request Major code: %d", err->major_code);
    if (major_name != NULL) {
	fprintf (stderr, " (%s)", major_name);
    }
    fputs ("\n", stderr);

    if (err->major_code >= 128)
    {
	fprintf (stderr, "  Request Minor code: %d", err->minor_code);
	if (minor_name != NULL) {
	    fprintf (stderr, " (%s)", minor_name);
	}
	fputs ("\n", stderr);
    }

    switch (err->error_code)
    {
    case XCB_VALUE:
	value_type = "Value";
	break;
    case XCB_ATOM:
	value_type = "AtomID";
	break;
    case XCB_WINDOW:
    case XCB_PIXMAP:
    case XCB_CURSOR:
    case XCB_FONT:
    case XCB_DRAWABLE:
    case XCB_COLORMAP:
    case XCB_G_CONTEXT:
    case XCB_ID_CHOICE:
	value_type = "ResourceID";
	break;
    default:
	value_type = NULL;
    }
    if (value_type != NULL) {
	fprintf (stderr, "  %s in failed request: 0x%x\n",
		 value_type, err->resource_id);
    }

    fprintf (stderr, "  Serial number of failed request: %d\n",
	     err->full_sequence);
}

/*
 * Cache for atom lookups in either direction
 */
struct atom_cache_entry {
    xcb_atom_t atom;
    const char *name;
    xcb_intern_atom_cookie_t intern_atom;
    struct atom_cache_entry *next;
};

static struct atom_cache_entry *atom_cache;

/*
 * Send a request to the server for an atom by name
 * Does not create the atom if it is not already present
 */
struct atom_cache_entry *Intern_Atom (xcb_connection_t * dpy, const char *name)
{
    struct atom_cache_entry *a;

    for (a = atom_cache ; a != NULL ; a = a->next) {
	if (strcmp (a->name, name) == 0)
	    return a; /* already requested or found */
    }

    a = calloc(1, sizeof(struct atom_cache_entry));
    if (a != NULL) {
	a->name = name;
	a->intern_atom = xcb_intern_atom (dpy, False, strlen (name), (name));
	a->next = atom_cache;
	atom_cache = a;
    }
    return a;
}

/* Get an atom by name when it is needed. */
xcb_atom_t Get_Atom (xcb_connection_t * dpy, const char *name)
{
    struct atom_cache_entry *a = Intern_Atom (dpy, name);

    if (a == NULL)
	return XCB_ATOM_NONE;

    if (a->atom == XCB_ATOM_NONE) {
	xcb_intern_atom_reply_t *reply;

	reply = xcb_intern_atom_reply(dpy, a->intern_atom, NULL);
	if (reply) {
	    a->atom = reply->atom;
	    free (reply);
	} else {
	    a->atom = (xcb_atom_t) -1;
	}
    }
    if (a->atom == (xcb_atom_t) -1) /* internal error */
	return XCB_ATOM_NONE;

    return a->atom;
}

/* Get the name for an atom when it is needed. */
const char *Get_Atom_Name (xcb_connection_t * dpy, xcb_atom_t atom)
{
    struct atom_cache_entry *a;

    for (a = atom_cache ; a != NULL ; a = a->next) {
	if (a->atom == atom)
	    return a->name; /* already requested or found */
    }

    a = calloc(1, sizeof(struct atom_cache_entry));
    if (a != NULL) {
	xcb_get_atom_name_cookie_t cookie = xcb_get_atom_name (dpy, atom);
	xcb_get_atom_name_reply_t *reply
	    = xcb_get_atom_name_reply (dpy, cookie, NULL);

	a->atom = atom;
	if (reply) {
	    int len = xcb_get_atom_name_name_length (reply);
	    char *name = malloc(len + 1);
	    if (name) {
		memcpy (name, xcb_get_atom_name_name (reply), len);
		name[len] = '\0';
		a->name = name;
	    }
	    free (reply);
	}

	a->next = atom_cache;
	atom_cache = a;

	return a->name;
    }
    return NULL;
}


typedef struct {
    long code;
    const char *name;
} binding;

#ifndef USE_XCB_ICCCM
/* Once xcb-icccm's API is stable, this should be replaced by
   xcb_size_hints_t & xcb_size_hints_flags_t */
typedef struct {
  /** User specified flags */
  uint32_t flags;
  /** User-specified position */
  int32_t x, y;
  /** User-specified size */
  int32_t width, height;
  /** Program-specified minimum size */
  int32_t min_width, min_height;
  /** Program-specified maximum size */
  int32_t max_width, max_height;
  /** Program-specified resize increments */
  int32_t width_inc, height_inc;
  /** Program-specified minimum aspect ratios */
  int32_t min_aspect_num, min_aspect_den;
  /** Program-specified maximum aspect ratios */
  int32_t max_aspect_num, max_aspect_den;
  /** Program-specified base size */
  int32_t base_width, base_height;
  /** Program-specified window gravity */
  uint32_t win_gravity;
} wm_size_hints_t;

# define xcb_size_hints_t wm_size_hints_t

typedef struct {
  /** Marks which fields in this structure are defined */
  int32_t flags;
  /** Does this application rely on the window manager to get keyboard
      input? */
  uint32_t input;
  /** See below */
  int32_t initial_state;
  /** Pixmap to be used as icon */
  xcb_pixmap_t icon_pixmap;
  /** Window to be used as icon */
  xcb_window_t icon_window;
  /** Initial position of icon */
  int32_t icon_x, icon_y;
  /** Icon mask bitmap */
  xcb_pixmap_t icon_mask;
  /* Identifier of related window group */
  xcb_window_t window_group;
} wm_hints_t;

#define xcb_icccm_wm_hints_t wm_hints_t

enum {
  /* xcb_size_hints_flags_t */
  XCB_ICCCM_SIZE_HINT_US_POSITION = 1 << 0,
  XCB_ICCCM_SIZE_HINT_US_SIZE = 1 << 1,
  XCB_ICCCM_SIZE_HINT_P_POSITION = 1 << 2,
  XCB_ICCCM_SIZE_HINT_P_SIZE = 1 << 3,
  XCB_ICCCM_SIZE_HINT_P_MIN_SIZE = 1 << 4,
  XCB_ICCCM_SIZE_HINT_P_MAX_SIZE = 1 << 5,
  XCB_ICCCM_SIZE_HINT_P_RESIZE_INC = 1 << 6,
  XCB_ICCCM_SIZE_HINT_P_ASPECT = 1 << 7,
  XCB_ICCCM_SIZE_HINT_BASE_SIZE = 1 << 8,
  XCB_ICCCM_SIZE_HINT_P_WIN_GRAVITY = 1 << 9,
  /* xcb_wm_state_t */
  XCB_ICCCM_WM_STATE_WITHDRAWN = 0,
  XCB_ICCCM_WM_STATE_NORMAL = 1,
  XCB_ICCCM_WM_STATE_ICONIC = 3,
  /* xcb_wm_t */
  XCB_ICCCM_WM_HINT_INPUT = (1L << 0),
  XCB_ICCCM_WM_HINT_STATE = (1L << 1),
  XCB_ICCCM_WM_HINT_ICON_PIXMAP = (1L << 2),
  XCB_ICCCM_WM_HINT_ICON_WINDOW = (1L << 3),
  XCB_ICCCM_WM_HINT_ICON_POSITION = (1L << 4),
  XCB_ICCCM_WM_HINT_ICON_MASK = (1L << 5),
  XCB_ICCCM_WM_HINT_WINDOW_GROUP = (1L << 6),
  XCB_ICCCM_WM_HINT_X_URGENCY = (1L << 8)
};

/* Once xcb-icccm's API is stable, these should be replaced by calls to it */
# define GET_TEXT_PROPERTY(Dpy, Win, Atom) \
    xcb_get_property (Dpy, False, Win, Atom, XCB_GET_PROPERTY_TYPE_ANY, 0, BUFSIZ)
# define xcb_icccm_get_wm_name(Dpy, Win) \
    GET_TEXT_PROPERTY(Dpy, Win, XCB_ATOM_WM_NAME)

# define xcb_icccm_get_wm_class(Dpy, Win) \
    xcb_get_property (Dpy, False, Win, XCB_ATOM_WM_CLASS, XCB_ATOM_STRING, 0, BUFSIZ)
# define xcb_icccm_get_wm_hints(Dpy, Win) \
    xcb_get_property(Dpy, False, Win, XCB_ATOM_WM_HINTS, XCB_ATOM_WM_HINTS, 0, 9)

# define xcb_icccm_get_wm_size_hints(Dpy, Win, Atom) \
    xcb_get_property (Dpy, False, Win, Atom, XCB_ATOM_WM_SIZE_HINTS, 0, 18)
# define xcb_icccm_get_wm_normal_hints(Dpy, Win) \
    xcb_icccm_get_wm_size_hints(Dpy, Win, XCB_ATOM_WM_NORMAL_HINTS)
#endif

/* Possibly in xcb-emwh in the future? */
static xcb_atom_t atom_net_wm_name, atom_utf8_string;
static xcb_atom_t atom_net_wm_desktop, atom_net_wm_window_type,
    atom_net_wm_state, atom_net_wm_pid, atom_net_frame_extents;
static xcb_get_property_cookie_t get_net_wm_name (xcb_connection_t *,
						  xcb_window_t);

/* Information we keep track of for each window to allow prefetching/reusing */
struct wininfo {
    xcb_window_t			window;

    /* cookies for requests we've sent */
    xcb_get_geometry_cookie_t		geometry_cookie;
    xcb_get_property_cookie_t		net_wm_name_cookie;
    xcb_get_property_cookie_t		wm_name_cookie;
    xcb_get_property_cookie_t		wm_class_cookie;
    xcb_translate_coordinates_cookie_t	trans_coords_cookie;
    xcb_query_tree_cookie_t		tree_cookie;
    xcb_get_window_attributes_cookie_t	attr_cookie;
    xcb_get_property_cookie_t		normal_hints_cookie;
    xcb_get_property_cookie_t		hints_cookie;
    xcb_get_property_cookie_t		wm_desktop_cookie;
    xcb_get_property_cookie_t		wm_window_type_cookie;
    xcb_get_property_cookie_t		wm_state_cookie;
    xcb_get_property_cookie_t		wm_pid_cookie;
    xcb_get_property_cookie_t		wm_client_machine_cookie;
    xcb_get_property_cookie_t		frame_extents_cookie;
    xcb_get_property_cookie_t		zoom_cookie;

    /* cached results from previous requests */
    xcb_get_geometry_reply_t *		geometry;
    xcb_get_window_attributes_reply_t *	win_attributes;
    xcb_size_hints_t *			normal_hints;
};

static void scale_init (xcb_screen_t *scrn);
static char *nscale (int, int, int, char *, size_t);
static char *xscale (int);
static char *yscale (int);
static char *bscale (int);
int main (int, char **);
static const char *LookupL (long, const binding *);
static const char *Lookup (int, const binding *);
static void Display_Window_Id (struct wininfo *, Bool);
static void Display_Stats_Info (struct wininfo *);
static void Display_Bits_Info (struct wininfo *);
static void Display_Event_Mask (long);
static void Display_Events_Info (struct wininfo *);
static void Display_Tree_Info (struct wininfo *, int);
static void display_tree_info_1 (struct wininfo *, int, int);
static void Display_Hints (xcb_size_hints_t *);
static void Display_Size_Hints (struct wininfo *);
static void Display_Window_Shape (xcb_window_t);
static void Display_WM_Info (struct wininfo *);
static void wininfo_wipe (struct wininfo *);

static Bool window_id_format_dec = False;

#ifdef HAVE_ICONV
static iconv_t iconv_from_utf8;
#endif
static const char *user_encoding;
static void print_utf8 (const char *, const char *, size_t, const char *);
static char *get_friendly_name (const char *, const char *);

static xcb_connection_t *dpy;
static xcb_screen_t *screen;
static xcb_generic_error_t *err;

#ifndef HAVE_STRLCAT
static size_t strlcat (char *dst, const char *src, size_t dstsize)
{
    size_t sd = strlen (dst);
    size_t ss = strlen (src);
    size_t s = sd + ss;

    if (s < dstsize) {
	strcpy (dst + sd, src);
    } else {
	strncpy (dst + sd, src, dstsize-sd-1);
	dst[dstsize] = '\0';
    }
    return s;
}
#endif

/*
 * Report the syntax for calling xwininfo:
 */
_X_NORETURN _X_COLD
static void
usage (void)
{
    fprintf (stderr,
	     "usage:  %s [-options ...]\n\n"
	     "where options include:\n"
	     "    -help                 print this message\n"
	     "    -version              print version message\n"
	     "    -d[isplay] <host:dpy> X server to contact\n"
	     "    -root                 use the root window\n"
	     "    -id <wdid>            use the window with the specified id\n"
	     "    -name <wdname>        use the window with the specified name\n"
	     "    -int                  print window id in decimal\n"
	     "    -children             print parent and child identifiers\n"
	     "    -tree                 print children identifiers recursively\n"
	     "    -stats                print window geometry [DEFAULT]\n"
	     "    -bits                 print window pixel information\n"
	     "    -events               print events selected for on window\n"
	     "    -size                 print size hints\n"
	     "    -wm                   print window manager hints\n"
	     "    -shape                print shape extents\n"
	     "    -frame                don't ignore window manager frames\n"
	     "    -english              print sizes in english units\n"
	     "    -metric               print sizes in metric units\n"
	     "    -all                  -tree, -stats, -bits, -events, -wm, -size, -shape\n"
	     "\n",
	     program_name);
    exit (1);
}

/*
 * pixel to inch, metric converter.
 * Hacked in by Mark W. Eichin <eichin@athena> [eichin:19880619.1509EST]
 *
 * Simply put: replace the old numbers with string print calls.
 * Returning a local string is ok, since we only ever get called to
 * print one x and one y, so as long as they don't collide, they're
 * fine. This is not meant to be a general purpose routine.
 *
 */

static int xp = 0, xmm = 0;
static int yp = 0, ymm = 0;
static int bp = 0, bmm = 0;
static int english = 0, metric = 0;

static void
scale_init (xcb_screen_t *scale_screen)
{
    xp = scale_screen->width_in_pixels;
    yp = scale_screen->height_in_pixels;
    xmm = scale_screen->width_in_millimeters;
    ymm = scale_screen->height_in_millimeters;
    bp  = xp  + yp;
    bmm = xmm + ymm;
}

#define MILE (5280*12)
#define YARD (3*12)
#define FOOT (12)

static char *
nscale (int n, int np, int nmm, char *nbuf, size_t nbufsize)
{
    snprintf (nbuf, nbufsize, "%d", n);

    if (metric||english) {
	int s = strlcat (nbuf, " (", nbufsize);

	if (metric) {
	    snprintf (nbuf+s, nbufsize-s, "%.2f mm%s",
		      ((double) n) * nmm/np , english ? "; " : "");
	}
	if (english) {
	    double inch_frac;
	    Bool printed_anything = False;
	    int inr;

	    inch_frac = ((double) n)*(nmm/25.4)/np;
	    inr = (int)inch_frac;
	    inch_frac -= (double)inr;
	    if (inr >= MILE) {
		int mi = inr/MILE;
		inr %= MILE;
		s = strlen (nbuf);
		snprintf (nbuf+s, nbufsize-s, "%d %s(?!?)",
			  mi, (mi == 1) ? "mile" : "miles");
		printed_anything = True;
	    }
	    if (inr >= YARD) {
		int yar = inr/YARD;
		inr %= YARD;
		if (printed_anything)
		    strlcat (nbuf, ", ", nbufsize);
		s = strlen (nbuf);
		snprintf (nbuf+s, nbufsize-s, "%d %s",
			 yar, (yar==1) ? "yard" : "yards");
		printed_anything = True;
	    }
	    if (inr >= FOOT) {
		int ft = inr/FOOT;
		inr  %= FOOT;
		if (printed_anything)
		    strlcat (nbuf, ", ", nbufsize);
		s = strlen (nbuf);
		snprintf (nbuf+s, nbufsize-s, "%d %s",
			 ft, (ft==1) ? "foot" : "feet");
		printed_anything = True;
	    }
	    if (!printed_anything || inch_frac != 0.0 || inr != 0) {
		if (printed_anything)
		    strlcat (nbuf, ", ", nbufsize);
		s = strlen (nbuf);
		snprintf (nbuf+s, nbufsize-s, "%.2f inches", inr+inch_frac);
	    }
	}
	strlcat (nbuf, ")", nbufsize);
    }
    return (nbuf);
}

static char xbuf[BUFSIZ];
static char *
xscale (int x)
{
    return (nscale (x, xp, xmm, xbuf, sizeof(xbuf)));
}

static char ybuf[BUFSIZ];
static char *
yscale (int y)
{
    return (nscale (y, yp, ymm, ybuf, sizeof(ybuf)));
}

static char bbuf[BUFSIZ];
static char *
bscale (int b)
{
    return (nscale (b, bp, bmm, bbuf, sizeof(bbuf)));
}

static const char *
window_id_str (xcb_window_t id)
{
    static char str[20];

    if (window_id_format_dec)
	snprintf (str, sizeof(str), "%u", id);
    else
	snprintf (str, sizeof(str), "0x%x", id);

    return str;
}

/* end of pixel to inch, metric converter */

int
main (int argc, char **argv)
{
    int tree = 0, stats = 0, bits = 0, events = 0, wm = 0, size = 0, shape = 0;
    int frame = 0, children = 0;
    int use_root = 0;
    xcb_window_t window = 0;
    char *display_name = NULL;
    const char *window_name = NULL;
    struct wininfo wininfo;
    struct wininfo *w = &wininfo;

    program_name = argv[0];

    if (!setlocale (LC_ALL, ""))
	fprintf (stderr, "%s: can not set locale properly\n", program_name);
    user_encoding = nl_langinfo (CODESET);
    if (user_encoding == NULL)
	user_encoding = "unknown encoding";

    memset (w, 0, sizeof(struct wininfo));

    /* Handle our command line arguments */
    for (int i = 1; i < argc; i++) {
	if (!strcmp (argv[i], "-help"))
	    usage ();
	if (!strcmp (argv[i], "-display") || !strcmp (argv[i], "-d")) {
	    if (++i >= argc)
		Fatal_Error("-display requires argument");
	    display_name = argv[i];
	    continue;
	}
	if (!strcmp (argv[i], "-root")) {
	    use_root = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-id")) {
	    if (++i >= argc)
		Fatal_Error("-id requires argument");
	    window = strtoul(argv[i], NULL, 0);
	    continue;
	}
	if (!strcmp (argv[i], "-name")) {
	    if (++i >= argc)
		Fatal_Error("-name requires argument");
	    window_name = argv[i];
	    continue;
	}
	if (!strcmp (argv[i], "-int")) {
	    window_id_format_dec = True;
	    continue;
	}
	if (!strcmp (argv[i], "-children")) {
	    children = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-tree")) {
	    tree = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-stats")) {
	    stats = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-bits")) {
	    bits = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-events")) {
	    events = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-wm")) {
	    wm = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-frame")) {
	    frame = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-size")) {
	    size = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-shape")) {
	    shape = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-english")) {
	    english = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-metric")) {
	    metric = 1;
	    continue;
	}
	if (!strcmp (argv[i], "-all")) {
	    tree = stats = bits = events = wm = size = shape = 1;
	    continue;
	}
	if (!strcmp(argv[i], "-version")) {
	    puts(PACKAGE_STRING);
	    exit(0);
	}
	fprintf (stderr, "%s: unrecognized argument %s\n\n",
		 program_name, argv[i]);
	usage ();
    }

    Setup_Display_And_Screen (display_name, &dpy, &screen);

    /* preload atoms we may need later */
    Intern_Atom (dpy, "_NET_WM_NAME");
    Intern_Atom (dpy, "UTF8_STRING");
    if (wm) {
	Intern_Atom (dpy, "_NET_WM_DESKTOP");
	Intern_Atom (dpy, "_NET_WM_WINDOW_TYPE");
	Intern_Atom (dpy, "_NET_WM_STATE");
	Intern_Atom (dpy, "_NET_WM_PID");
	Intern_Atom (dpy, "_NET_FRAME_EXTENTS");
    }
    /* initialize scaling data */
    scale_init(screen);

    if (use_root)
	window = screen->root;
    else if (window_name) {
	window = Window_With_Name (dpy, screen->root, window_name);
	if (!window)
	    Fatal_Error ("No window with name \"%s\" exists!", window_name);
    }

    /* If no window selected on command line, let user pick one the hard way */
    if (!window) {
	printf ("\n"
		"xwininfo: Please select the window about which you\n"
		"          would like information by clicking the\n"
		"          mouse in that window.\n");
	Intern_Atom (dpy, "_NET_VIRTUAL_ROOTS");
	Intern_Atom (dpy, "WM_STATE");
	window = Select_Window (dpy, screen, !frame);
    }

    /*
     * Do the actual displaying as per parameters
     */
    if (!(children || tree || bits || events || wm || size))
	stats = 1;

    /*
     * make sure that the window is valid
     */
    {
	xcb_get_geometry_cookie_t gg_cookie =
	    xcb_get_geometry (dpy, window);

	w->geometry = xcb_get_geometry_reply(dpy, gg_cookie, &err);

	if (!w->geometry) {
	    if (err)
		Print_X_Error (dpy, err);

	    Fatal_Error ("No such window with id %s.", window_id_str (window));
	}
    }

    /* Send requests to prefetch data we'll need */
    w->window = window;
    w->net_wm_name_cookie = get_net_wm_name (dpy, window);
    w->wm_name_cookie = xcb_icccm_get_wm_name (dpy, window);
    if (children || tree)
	w->tree_cookie = xcb_query_tree (dpy, window);
    if (stats) {
	w->trans_coords_cookie =
	    xcb_translate_coordinates (dpy, window, w->geometry->root,
				       -(w->geometry->border_width),
				       -(w->geometry->border_width));
    }
    if (stats || bits || events)
	w->attr_cookie = xcb_get_window_attributes (dpy, window);
    if (stats || size)
	w->normal_hints_cookie = xcb_icccm_get_wm_normal_hints (dpy, window);
    if (wm) {
	w->hints_cookie = xcb_icccm_get_wm_hints(dpy, window);

	atom_net_wm_desktop = Get_Atom (dpy, "_NET_WM_DESKTOP");
	if (atom_net_wm_desktop) {
	    w->wm_desktop_cookie = xcb_get_property
		(dpy, False, window, atom_net_wm_desktop,
		 XCB_ATOM_CARDINAL, 0, 4);
	}

	atom_net_wm_window_type	= Get_Atom (dpy, "_NET_WM_WINDOW_TYPE");
	if (atom_net_wm_window_type) {
	    w->wm_window_type_cookie = xcb_get_property
		(dpy, False, window, atom_net_wm_window_type,
		 XCB_ATOM_ATOM, 0, BUFSIZ);
	}

	atom_net_wm_state = Get_Atom (dpy, "_NET_WM_STATE");
	if (atom_net_wm_state) {
	    w->wm_state_cookie = xcb_get_property
		(dpy, False, window, atom_net_wm_state,
		 XCB_ATOM_ATOM, 0, BUFSIZ);
	}

	atom_net_wm_pid	= Get_Atom (dpy, "_NET_WM_PID");
	if (atom_net_wm_pid) {
	    w->wm_pid_cookie = xcb_get_property
		(dpy, False, window, atom_net_wm_pid,
		 XCB_ATOM_CARDINAL, 0, BUFSIZ);
	    w->wm_client_machine_cookie = xcb_get_property
		(dpy, False, window, XCB_ATOM_WM_CLIENT_MACHINE,
		 XCB_GET_PROPERTY_TYPE_ANY, 0, BUFSIZ);
	}

	atom_net_frame_extents = Get_Atom (dpy, "_NET_FRAME_EXTENTS");
	if (atom_net_frame_extents) {
	    w->frame_extents_cookie = xcb_get_property
		(dpy, False, window, atom_net_frame_extents,
		 XCB_ATOM_CARDINAL, 0, 4 * 4);
	}
    }
    if (size)
	w->zoom_cookie = xcb_icccm_get_wm_size_hints (dpy, window,
						      XCB_ATOM_WM_ZOOM_HINTS);
    xcb_flush (dpy);

    printf ("\nxwininfo: Window id: ");
    Display_Window_Id (w, True);
    if (children || tree)
	Display_Tree_Info (w, tree);
    if (stats)
	Display_Stats_Info (w);
    if (bits)
	Display_Bits_Info (w);
    if (events)
	Display_Events_Info (w);
    if (wm)
	Display_WM_Info (w);
    if (size)
	Display_Size_Hints (w);
    if (shape)
	Display_Window_Shape (window);
    printf ("\n");

    wininfo_wipe (w);
    xcb_disconnect (dpy);
#ifdef HAVE_ICONV
    if (iconv_from_utf8 && (iconv_from_utf8 != (iconv_t) -1)) {
	iconv_close (iconv_from_utf8);
    }
#endif
    exit (0);
}

/* Ensure win_attributes field is filled in */
static xcb_get_window_attributes_reply_t *
fetch_win_attributes (struct wininfo *w)
{
    if (!w->win_attributes) {
	w->win_attributes =
	    xcb_get_window_attributes_reply (dpy, w->attr_cookie, &err);

	if (!w->win_attributes) {
	    Print_X_Error (dpy, err);
	    Fatal_Error ("Can't get window attributes.");
	}
    }
    return w->win_attributes;
}

#ifndef USE_XCB_ICCCM
static Bool
wm_size_hints_reply (xcb_connection_t *wshr_dpy, xcb_get_property_cookie_t cookie,
		     wm_size_hints_t *hints_return, xcb_generic_error_t **wshr_err)
{
    xcb_get_property_reply_t *prop = xcb_get_property_reply (wshr_dpy, cookie, wshr_err);
    size_t length;

    if (!prop || (prop->type != XCB_ATOM_WM_SIZE_HINTS) ||
	(prop->format != 32)) {
	free (prop);
	return False;
    }

    memset (hints_return, 0, sizeof(wm_size_hints_t));

    length = (size_t) xcb_get_property_value_length(prop);
    if (length > sizeof(wm_size_hints_t))
	length = sizeof(wm_size_hints_t);
    memcpy (hints_return, xcb_get_property_value (prop), length);

    free (prop);
    return True;
}

#define xcb_icccm_get_wm_normal_hints_reply wm_size_hints_reply
#define xcb_icccm_get_wm_size_hints_reply wm_size_hints_reply
#endif



/* Ensure normal_hints field is filled in */
static xcb_size_hints_t *
fetch_normal_hints (struct wininfo *w, xcb_size_hints_t *hints_return)
{
    if (!w->normal_hints) {
	xcb_size_hints_t hints;

	if (xcb_icccm_get_wm_normal_hints_reply (dpy, w->normal_hints_cookie,
						 &hints, NULL)) {
	    w->normal_hints = malloc (sizeof(xcb_size_hints_t));
	    if (w->normal_hints)
		memcpy(w->normal_hints, &hints, sizeof(xcb_size_hints_t));
	}
    }
    if (hints_return && w->normal_hints)
	memcpy(hints_return, w->normal_hints, sizeof(xcb_size_hints_t));
    return w->normal_hints;
}


/*
 * Lookup: lookup a code in a table.
 */

static const char *
LookupL (long code, const binding *table)
{
    const char *name = NULL;

    while (table->name) {
	if (table->code == code) {
	    name = table->name;
	    break;
	}
	table++;
    }

    if (name == NULL) {
	static char _lookup_buffer[100];

	snprintf (_lookup_buffer, sizeof(_lookup_buffer),
		  "unknown (code = %ld. = 0x%lx)", code, code);
	name = _lookup_buffer;
    }

    return (name);
}

static const char *
Lookup (int code, const binding *table)
{
    return LookupL ((long)code, table);
}

/*
 * Routine to display a window id in dec/hex with name if window has one
 *
 * Requires wininfo members initialized: window, wm_name_cookie
 */

static void
Display_Window_Id (struct wininfo *w, Bool newline_wanted)
{
#ifdef USE_XCB_ICCCM
    xcb_icccm_get_text_property_reply_t wmn_reply;
    uint8_t got_reply = False;
#endif
    xcb_get_property_reply_t *prop;
    const char *wm_name = NULL;
    unsigned int wm_name_len = 0;
    xcb_atom_t wm_name_encoding = XCB_NONE;

    printf ("%s", window_id_str (w->window));

    if (!w->window) {
	printf (" (none)");
    } else {
	if (w->window == screen->root) {
	    printf (" (the root window)");
	}
	/* Get window name if any */
	prop = xcb_get_property_reply (dpy, w->net_wm_name_cookie, NULL);
	if (prop && (prop->type != XCB_NONE)) {
	    wm_name = xcb_get_property_value (prop);
	    wm_name_len = xcb_get_property_value_length (prop);
	    wm_name_encoding = prop->type;
	} else { /* No _NET_WM_NAME, check WM_NAME */
#ifdef USE_XCB_ICCCM
	    got_reply = xcb_icccm_get_wm_name_reply (dpy, w->wm_name_cookie,
						     &wmn_reply, NULL);
	    if (got_reply) {
		wm_name = wmn_reply.name;
		wm_name_len = wmn_reply.name_len;
		wm_name_encoding = wmn_reply.encoding;
	    }
#else
	    prop = xcb_get_property_reply (dpy, w->wm_name_cookie, NULL);
	    if (prop && (prop->type != XCB_NONE)) {
		wm_name = xcb_get_property_value (prop);
		wm_name_len = xcb_get_property_value_length (prop);
		wm_name_encoding = prop->type;
	    }
#endif
	}
	if (wm_name_len == 0) {
	    printf (" (has no name)");
        } else {
	    if (wm_name_encoding == XCB_ATOM_STRING) {
		printf (" \"%.*s\"", wm_name_len, wm_name);
	    } else if (wm_name_encoding == atom_utf8_string) {
		print_utf8 (" \"", wm_name, wm_name_len,  "\"");
	    } else {
		/* Encodings we don't support, including COMPOUND_TEXT */
		const char *enc_name = Get_Atom_Name (dpy, wm_name_encoding);
		if (enc_name) {
		    printf (" (name in unsupported encoding %s)", enc_name);
		} else {
		    printf (" (name in unsupported encoding ATOM 0x%x)",
			    wm_name_encoding);
		}
	    }
	}
#ifdef USE_XCB_ICCCM
	if (got_reply)
	    xcb_icccm_get_text_property_reply_wipe (&wmn_reply);
#else
	free (prop);
#endif
    }

    if (newline_wanted)
	printf ("\n");

    return;
}


/*
 * Display Stats on window
 */
static const binding _window_classes[] = {
	{ XCB_WINDOW_CLASS_INPUT_OUTPUT, "InputOutput" },
	{ XCB_WINDOW_CLASS_INPUT_ONLY, "InputOnly" },
        { 0, NULL } };

static const binding _map_states[] = {
	{ XCB_MAP_STATE_UNMAPPED,	"IsUnMapped" },
	{ XCB_MAP_STATE_UNVIEWABLE,	"IsUnviewable" },
	{ XCB_MAP_STATE_VIEWABLE,	"IsViewable" },
	{ 0, NULL } };

static const binding _backing_store_states[] = {
	{ XCB_BACKING_STORE_NOT_USEFUL, "NotUseful" },
	{ XCB_BACKING_STORE_WHEN_MAPPED,"WhenMapped" },
	{ XCB_BACKING_STORE_ALWAYS,	"Always" },
	{ 0, NULL } };

static const binding _bit_gravity_states[] = {
	{ XCB_GRAVITY_BIT_FORGET,	"ForgetGravity" },
	{ XCB_GRAVITY_NORTH_WEST,	"NorthWestGravity" },
	{ XCB_GRAVITY_NORTH,		"NorthGravity" },
	{ XCB_GRAVITY_NORTH_EAST,	"NorthEastGravity" },
	{ XCB_GRAVITY_WEST,		"WestGravity" },
	{ XCB_GRAVITY_CENTER,		"CenterGravity" },
	{ XCB_GRAVITY_EAST,		"EastGravity" },
	{ XCB_GRAVITY_SOUTH_WEST,	"SouthWestGravity" },
	{ XCB_GRAVITY_SOUTH,		"SouthGravity" },
	{ XCB_GRAVITY_SOUTH_EAST,	"SouthEastGravity" },
	{ XCB_GRAVITY_STATIC,		"StaticGravity" },
	{ 0, NULL }};

static const binding _window_gravity_states[] = {
	{ XCB_GRAVITY_WIN_UNMAP,	"UnmapGravity" },
	{ XCB_GRAVITY_NORTH_WEST,	"NorthWestGravity" },
	{ XCB_GRAVITY_NORTH,		"NorthGravity" },
	{ XCB_GRAVITY_NORTH_EAST,	"NorthEastGravity" },
	{ XCB_GRAVITY_WEST,		"WestGravity" },
	{ XCB_GRAVITY_CENTER,		"CenterGravity" },
	{ XCB_GRAVITY_EAST,		"EastGravity" },
	{ XCB_GRAVITY_SOUTH_WEST,	"SouthWestGravity" },
	{ XCB_GRAVITY_SOUTH,		"SouthGravity" },
	{ XCB_GRAVITY_SOUTH_EAST,	"SouthEastGravity" },
	{ XCB_GRAVITY_STATIC,		"StaticGravity" },
	{ 0, NULL }};

static const binding _visual_classes[] = {
	{ XCB_VISUAL_CLASS_STATIC_GRAY,	"StaticGray" },
	{ XCB_VISUAL_CLASS_GRAY_SCALE,	"GrayScale" },
	{ XCB_VISUAL_CLASS_STATIC_COLOR,"StaticColor" },
	{ XCB_VISUAL_CLASS_PSEUDO_COLOR,"PseudoColor" },
	{ XCB_VISUAL_CLASS_TRUE_COLOR,	"TrueColor" },
	{ XCB_VISUAL_CLASS_DIRECT_COLOR,"DirectColor" },
	{ 0, NULL }};

/*
 * Requires wininfo members initialized:
 *   window, geometry, attr_cookie, trans_coords_cookie, normal_hints_cookie
 */
static void
Display_Stats_Info (struct wininfo *w)
{
    // PRE: screen != NULL
    xcb_translate_coordinates_reply_t *trans_coords;
    xcb_get_window_attributes_reply_t *win_attributes;
    xcb_size_hints_t hints;

    int dw = screen->width_in_pixels, dh = screen->height_in_pixels;
    int rx, ry, xright, ybelow;
    int showright = 0, showbelow = 0;
    xcb_window_t wmframe, parent;

    trans_coords =
	xcb_translate_coordinates_reply (dpy, w->trans_coords_cookie, NULL);
    if (!trans_coords)
	Fatal_Error ("Can't get translated coordinates.");

    rx = (int16_t)trans_coords->dst_x;
    ry = (int16_t)trans_coords->dst_y;
    free (trans_coords);

    xright = (dw - rx - w->geometry->border_width * 2 -
	      w->geometry->width);
    ybelow = (dh - ry - w->geometry->border_width * 2 -
	      w->geometry->height);


    printf ("\n");
    printf ("  Absolute upper-left X:  %s\n", xscale (rx));
    printf ("  Absolute upper-left Y:  %s\n", yscale (ry));
    printf ("  Relative upper-left X:  %s\n", xscale (w->geometry->x));
    printf ("  Relative upper-left Y:  %s\n", yscale (w->geometry->y));
    printf ("  Width: %s\n", xscale (w->geometry->width));
    printf ("  Height: %s\n", yscale (w->geometry->height));
    printf ("  Depth: %d\n", w->geometry->depth);

    win_attributes = fetch_win_attributes (w);

    printf ("  Visual: 0x%lx\n", (unsigned long) win_attributes->visual);
    if (screen)
    {
	xcb_depth_iterator_t depth_iter;
	xcb_visualtype_t  *visual_type = NULL;

	depth_iter = xcb_screen_allowed_depths_iterator (screen);
	for (; depth_iter.rem; xcb_depth_next (&depth_iter)) {
	    xcb_visualtype_iterator_t visual_iter;

	    visual_iter = xcb_depth_visuals_iterator (depth_iter.data);
	    for (; visual_iter.rem; xcb_visualtype_next (&visual_iter)) {
        // POST: "visual_iter is within the bounds of the object"
		if (win_attributes->visual == visual_iter.data->visual_id) {
		    visual_type = visual_iter.data;
		    break;
		}
	    }
	}
	if (visual_type)
	    printf ("  Visual Class: %s\n", Lookup (visual_type->_class,
						    _visual_classes));
    }

    printf ("  Border width: %s\n", bscale (w->geometry->border_width));
    printf ("  Class: %s\n",
	    Lookup (win_attributes->_class, _window_classes));
    printf ("  Colormap: 0x%lx (%sinstalled)\n",
	    (unsigned long) win_attributes->colormap,
	    win_attributes->map_is_installed ? "" : "not ");
    printf ("  Bit Gravity State: %s\n",
	    Lookup (win_attributes->bit_gravity, _bit_gravity_states));
    printf ("  Window Gravity State: %s\n",
	    Lookup (win_attributes->win_gravity, _window_gravity_states));
    printf ("  Backing Store State: %s\n",
	    Lookup (win_attributes->backing_store, _backing_store_states));
    printf ("  Save Under State: %s\n",
	    win_attributes->save_under ? "yes" : "no");
    printf ("  Map State: %s\n",
	    Lookup (win_attributes->map_state, _map_states));
    printf ("  Override Redirect State: %s\n",
	    win_attributes->override_redirect ? "yes" : "no");
    printf ("  Corners:  +%d+%d  -%d+%d  -%d-%d  +%d-%d\n",
	    rx, ry, xright, ry, xright, ybelow, rx, ybelow);

    /*
     * compute geometry string that would recreate window
     */
    printf ("  -geometry ");

    /* compute size in appropriate units */
    if (!fetch_normal_hints (w, &hints))
	hints.flags = 0;

    if ((hints.flags & XCB_ICCCM_SIZE_HINT_P_RESIZE_INC)  &&
	(hints.width_inc != 0)  && (hints.height_inc != 0)) {
	if (hints.flags &
	    (XCB_ICCCM_SIZE_HINT_BASE_SIZE|XCB_ICCCM_SIZE_HINT_P_MIN_SIZE)) {
	    if (hints.flags & XCB_ICCCM_SIZE_HINT_BASE_SIZE) {
		w->geometry->width -= hints.base_width;
		w->geometry->height -= hints.base_height;
	    } else {
		/* ICCCM says MinSize is default for BaseSize */
		w->geometry->width -= hints.min_width;
		w->geometry->height -= hints.min_height;
	    }
	}
	printf ("%dx%d", w->geometry->width/hints.width_inc,
		w->geometry->height/hints.height_inc);
    } else
	printf ("%dx%d", w->geometry->width, w->geometry->height);

    if (!(hints.flags & XCB_ICCCM_SIZE_HINT_P_WIN_GRAVITY))
	hints.win_gravity = XCB_GRAVITY_NORTH_WEST; /* per ICCCM */
    /* find our window manager frame, if any */
    for (wmframe = parent = w->window; parent != 0 ; wmframe = parent) {
	xcb_query_tree_cookie_t qt_cookie;
	xcb_query_tree_reply_t *tree;

	qt_cookie = xcb_query_tree (dpy, wmframe);
	tree = xcb_query_tree_reply (dpy, qt_cookie, &err);
	if (!tree) {
	    Print_X_Error (dpy, err);
	    Fatal_Error ("Can't query window tree.");
	}
	parent = tree->parent;
	free (tree);
	if (parent == w->geometry->root || !parent)
	    break;
    }
    if (wmframe != w->window) {
	/* WM reparented, so find edges of the frame */
	/* Only works for ICCCM-compliant WMs, and then only if the
	   window has corner gravity.  We would need to know the original width
	   of the window to correctly handle the other gravities. */
	xcb_get_geometry_cookie_t geom_cookie;
	xcb_get_geometry_reply_t *frame_geometry;

	geom_cookie = xcb_get_geometry (dpy, wmframe);
	frame_geometry = xcb_get_geometry_reply (dpy, geom_cookie, &err);

	if (!frame_geometry) {
	    Print_X_Error (dpy, err);
	    Fatal_Error ("Can't get frame geometry.");
	}
	switch (hints.win_gravity) {
	    case XCB_GRAVITY_NORTH_WEST: case XCB_GRAVITY_SOUTH_WEST:
	    case XCB_GRAVITY_NORTH_EAST: case XCB_GRAVITY_SOUTH_EAST:
	    case XCB_GRAVITY_WEST:
		rx = frame_geometry->x;
	}
	switch (hints.win_gravity) {
	    case XCB_GRAVITY_NORTH_WEST: case XCB_GRAVITY_SOUTH_WEST:
	    case XCB_GRAVITY_NORTH_EAST: case XCB_GRAVITY_SOUTH_EAST:
	    case XCB_GRAVITY_EAST:
		xright = dw - frame_geometry->x - frame_geometry->width -
		    (2 * frame_geometry->border_width);
	}
	switch (hints.win_gravity) {
	    case XCB_GRAVITY_NORTH_WEST: case XCB_GRAVITY_SOUTH_WEST:
	    case XCB_GRAVITY_NORTH_EAST: case XCB_GRAVITY_SOUTH_EAST:
	    case XCB_GRAVITY_NORTH:
		ry = frame_geometry->y;
	}
	switch (hints.win_gravity) {
	    case XCB_GRAVITY_NORTH_WEST: case XCB_GRAVITY_SOUTH_WEST:
	    case XCB_GRAVITY_NORTH_EAST: case XCB_GRAVITY_SOUTH_EAST:
	    case XCB_GRAVITY_SOUTH:
		ybelow = dh - frame_geometry->y - frame_geometry->height -
		    (2 * frame_geometry->border_width);
	}
	free (frame_geometry);
    }
    /* If edge gravity, offer a corner on that edge (because the application
       programmer cares about that edge), otherwise offer upper left unless
       some other corner is close to an edge of the screen.
       (For corner gravity, assume gravity was set by XWMGeometry.
       For CenterGravity, it doesn't matter.) */
    if (hints.win_gravity == XCB_GRAVITY_EAST  ||
	(abs (xright) <= 100  &&  abs (xright) < abs (rx)
	 &&  hints.win_gravity != XCB_GRAVITY_WEST))
	showright = 1;
    if (hints.win_gravity == XCB_GRAVITY_SOUTH  ||
	(abs (ybelow) <= 100  &&  abs (ybelow) < abs (ry)
	 &&  hints.win_gravity != XCB_GRAVITY_NORTH))
	showbelow = 1;

    if (showright)
	printf ("-%d", xright);
    else
	printf ("+%d", rx);
    if (showbelow)
	printf ("-%d", ybelow);
    else
	printf ("+%d", ry);
    printf ("\n");
}


/*
 * Display bits info:
 */
static const binding _gravities[] = {
    /* WARNING: the first two of these have the same value - see code */
	{ XCB_GRAVITY_WIN_UNMAP,	"UnMapGravity" },
	{ XCB_GRAVITY_BIT_FORGET,	"ForgetGravity" },
	{ XCB_GRAVITY_NORTH_WEST,	"NorthWestGravity" },
	{ XCB_GRAVITY_NORTH,		"NorthGravity" },
	{ XCB_GRAVITY_NORTH_EAST,	"NorthEastGravity" },
	{ XCB_GRAVITY_WEST,		"WestGravity" },
	{ XCB_GRAVITY_CENTER,		"CenterGravity" },
	{ XCB_GRAVITY_EAST,		"EastGravity" },
	{ XCB_GRAVITY_SOUTH_WEST,	"SouthWestGravity" },
	{ XCB_GRAVITY_SOUTH,		"SouthGravity" },
	{ XCB_GRAVITY_SOUTH_EAST,	"SouthEastGravity" },
	{ XCB_GRAVITY_STATIC,		"StaticGravity" },
	{ 0, NULL } };

static const binding _backing_store_hint[] = {
	{ XCB_BACKING_STORE_NOT_USEFUL, "NotUseful" },
	{ XCB_BACKING_STORE_WHEN_MAPPED,"WhenMapped" },
	{ XCB_BACKING_STORE_ALWAYS,	"Always" },
	{ 0, NULL } };

static const binding _bool[] = {
	{ 0, "No" },
	{ 1, "Yes" },
	{ 0, NULL } };

/*
 * Requires wininfo members initialized:
 *   window, attr_cookie (or win_attributes)
 */
static void
Display_Bits_Info (struct wininfo * w)
{
    xcb_get_window_attributes_reply_t *win_attributes
	= fetch_win_attributes (w);

    printf ("\n");
    printf ("  Bit gravity: %s\n",
	    Lookup (win_attributes->bit_gravity, _gravities+1));
    printf ("  Window gravity: %s\n",
	    Lookup (win_attributes->win_gravity, _gravities));
    printf ("  Backing-store hint: %s\n",
	    Lookup (win_attributes->backing_store, _backing_store_hint));
    printf ("  Backing-planes to be preserved: 0x%lx\n",
	    (unsigned long) win_attributes->backing_planes);
    printf ("  Backing pixel: %ld\n",
	    (unsigned long) win_attributes->backing_pixel);
    printf ("  Save-unders: %s\n",
	    Lookup (win_attributes->save_under, _bool));
}


/*
 * Routine to display all events in an event mask
 */
static const binding _event_mask_names[] = {
	{ XCB_EVENT_MASK_KEY_PRESS,		"KeyPress" },
	{ XCB_EVENT_MASK_KEY_RELEASE,		"KeyRelease" },
	{ XCB_EVENT_MASK_BUTTON_PRESS,		"ButtonPress" },
	{ XCB_EVENT_MASK_BUTTON_RELEASE,	"ButtonRelease" },
	{ XCB_EVENT_MASK_ENTER_WINDOW,		"EnterWindow" },
	{ XCB_EVENT_MASK_LEAVE_WINDOW,		"LeaveWindow" },
	{ XCB_EVENT_MASK_POINTER_MOTION,	"PointerMotion" },
	{ XCB_EVENT_MASK_POINTER_MOTION_HINT,	"PointerMotionHint" },
	{ XCB_EVENT_MASK_BUTTON_1_MOTION,	"Button1Motion" },
	{ XCB_EVENT_MASK_BUTTON_2_MOTION,	"Button2Motion" },
	{ XCB_EVENT_MASK_BUTTON_3_MOTION,	"Button3Motion" },
	{ XCB_EVENT_MASK_BUTTON_4_MOTION,	"Button4Motion" },
	{ XCB_EVENT_MASK_BUTTON_5_MOTION,	"Button5Motion" },
	{ XCB_EVENT_MASK_BUTTON_MOTION,		"ButtonMotion" },
	{ XCB_EVENT_MASK_KEYMAP_STATE,		"KeymapState" },
	{ XCB_EVENT_MASK_EXPOSURE,		"Exposure" },
	{ XCB_EVENT_MASK_VISIBILITY_CHANGE,	"VisibilityChange" },
	{ XCB_EVENT_MASK_STRUCTURE_NOTIFY,	"StructureNotify" },
	{ XCB_EVENT_MASK_RESIZE_REDIRECT,	"ResizeRedirect" },
	{ XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY,	"SubstructureNotify" },
	{ XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT,	"SubstructureRedirect" },
	{ XCB_EVENT_MASK_FOCUS_CHANGE,		"FocusChange" },
	{ XCB_EVENT_MASK_PROPERTY_CHANGE,	"PropertyChange" },
	{ XCB_EVENT_MASK_COLOR_MAP_CHANGE,	"ColormapChange" },
	{ XCB_EVENT_MASK_OWNER_GRAB_BUTTON,	"OwnerGrabButton" },
	{ 0, NULL } };

static void
Display_Event_Mask (long mask)
{
    unsigned long bit, bit_mask;

    for (bit=0, bit_mask=1; bit < sizeof(long)*8; bit++, bit_mask <<= 1)
	if (mask & bit_mask)
	    printf ("      %s\n",
		    LookupL (bit_mask, _event_mask_names));
}


/*
 * Display info on events
 *
 * Requires wininfo members initialized:
 *   window, attr_cookie (or win_attributes)
 */
static void
Display_Events_Info (struct wininfo *w)
{
    xcb_get_window_attributes_reply_t *win_attributes
	= fetch_win_attributes (w);

    printf ("\n");
    printf ("  Someone wants these events:\n");
    Display_Event_Mask (win_attributes->all_event_masks);

    printf ("  Do not propagate these events:\n");
    Display_Event_Mask (win_attributes->do_not_propagate_mask);

    printf ("  Override redirection?: %s\n",
	    Lookup (win_attributes->override_redirect, _bool));
}


  /* left out visual stuff */
  /* left out colormap */
  /* left out map_installed */


/*
 * Display root, parent, and (recursively) children information
 * recurse - true to show children information
 *
 * Requires wininfo members initialized: window, tree_cookie
 */
static void
Display_Tree_Info (struct wininfo *w, int recurse)
{
    display_tree_info_1 (w, recurse, 0);
}

/*
 * level - recursion level
 */
static void
display_tree_info_1 (struct wininfo *w, int recurse, int level)
{
    unsigned int num_children;
    xcb_query_tree_reply_t *tree;

    tree = xcb_query_tree_reply (dpy, w->tree_cookie, &err);
    if (!tree) {
	Print_X_Error (dpy, err);
	Fatal_Error ("Can't query window tree.");
    }

    if (level == 0) {
	struct wininfo rw, pw;
	rw.window = tree->root;
	rw.net_wm_name_cookie = get_net_wm_name (dpy, rw.window);
	rw.wm_name_cookie = xcb_icccm_get_wm_name (dpy, rw.window);
	pw.window = tree->parent;
	pw.net_wm_name_cookie = get_net_wm_name (dpy, pw.window);
	pw.wm_name_cookie = xcb_icccm_get_wm_name (dpy, pw.window);
	xcb_flush (dpy);

	printf ("\n");
	printf ("  Root window id: ");
	Display_Window_Id (&rw, True);
	printf ("  Parent window id: ");
	Display_Window_Id (&pw, True);
    }

    num_children = xcb_query_tree_children_length (tree);

    if (level == 0  ||  num_children > 0) {
	printf ("     ");
	for (int j = 0; j < level; j++) printf ("   ");
	printf ("%d child%s%s\n", num_children, num_children == 1 ? "" : "ren",
		num_children ? ":" : ".");
    }

    if (num_children > 0) {
	xcb_window_t *child_list = xcb_query_tree_children (tree);
	struct wininfo *children
	    = calloc (num_children, sizeof(struct wininfo));

	if (children == NULL)
	    Fatal_Error ("Failed to allocate memory in display_tree_info");

	for (int i = (int)num_children - 1; i >= 0; i--) {
	    struct wininfo *cw = &children[i];

	    cw->window = child_list[i];
	    cw->net_wm_name_cookie = get_net_wm_name (dpy, child_list[i]);
	    cw->wm_name_cookie = xcb_icccm_get_wm_name (dpy, child_list[i]);
	    cw->wm_class_cookie = xcb_icccm_get_wm_class (dpy, child_list[i]);
	    cw->geometry_cookie = xcb_get_geometry (dpy, child_list[i]);
	    cw->trans_coords_cookie = xcb_translate_coordinates
		(dpy, child_list[i], tree->root, 0, 0);
	    if (recurse)
		cw->tree_cookie = xcb_query_tree (dpy, child_list[i]);
	}
	xcb_flush (dpy);

	for (int i = (int)num_children - 1; i >= 0; i--) {
	    struct wininfo *cw = &children[i];
	    Bool got_wm_class = False;
	    char *instance_name = NULL, *class_name = NULL;
	    int instance_name_len, class_name_len;
#ifdef USE_XCB_ICCCM
	    xcb_icccm_get_wm_class_reply_t classhint;
#else
	    xcb_get_property_reply_t *classprop;
#endif
	    xcb_get_geometry_reply_t *geometry;

	    printf ("     ");
	    for (int j = 0; j < level; j++) printf ("   ");
	    Display_Window_Id (cw, False);
	    printf (": (");

#ifdef USE_XCB_ICCCM
	    if (xcb_icccm_get_wm_class_reply (dpy, cw->wm_class_cookie,
					&classhint, NULL)) {
		got_wm_class = True;
		instance_name = classhint.instance_name;
		class_name = classhint.class_name;
		instance_name_len = strlen(instance_name);
		class_name_len = strlen(class_name);
	    }
#else
	    classprop = xcb_get_property_reply
		(dpy, cw->wm_class_cookie, NULL);
	    if (classprop) {
		if (classprop->type == XCB_ATOM_STRING &&
		    classprop->format == 8) {
		    int proplen = xcb_get_property_value_length (classprop);

		    instance_name = xcb_get_property_value (classprop);
		    instance_name_len = strnlen (instance_name, proplen);
		    if (instance_name_len < proplen) {
			class_name = instance_name + instance_name_len + 1;
			class_name_len = strnlen
			    (class_name, proplen - (instance_name_len + 1));
		    } else
			class_name_len = 0;
		    got_wm_class = True;
		}
		else
		    free (classprop);
	    }
#endif

	    if (got_wm_class) {
		if (instance_name)
		    printf ("\"%.*s\" ", instance_name_len, instance_name);
		else
		    printf ("(none) ");

		if (class_name)
		    printf ("\"%.*s\") ",  class_name_len, class_name);
		else
		    printf ("(none)) ");

#ifdef USE_XCB_ICCCM
		xcb_icccm_get_wm_class_reply_wipe (&classhint);
#else
		free (classprop);
#endif
	    } else
		printf (") ");

	    geometry = xcb_get_geometry_reply(dpy, cw->geometry_cookie, &err);
	    if (geometry) {
		xcb_translate_coordinates_reply_t *trans_coords;

		printf (" %ux%u+%d+%d", geometry->width, geometry->height,
					geometry->x, geometry->y);

		trans_coords = xcb_translate_coordinates_reply
		    (dpy, cw->trans_coords_cookie, &err);

		if (trans_coords) {
		    int16_t abs_x = (int16_t) trans_coords->dst_x;
		    int16_t abs_y = (int16_t) trans_coords->dst_y;
		    int border = geometry->border_width;

		    printf ("  +%d+%d", abs_x - border, abs_y - border);
		    free (trans_coords);
		} else if (err) {
		    Print_X_Error (dpy, err);
		}

		free (geometry);
	    } else if (err) {
		Print_X_Error (dpy, err);
	    }
	    printf ("\n");

	    if (recurse)
		display_tree_info_1 (cw, 1, level+1);

	    wininfo_wipe (cw);
	}
	free (children);
    }

    free (tree); /* includes storage for child_list[] */
}


/*
 * Display a set of size hints
 */
static void
Display_Hints (xcb_size_hints_t *hints)
{
    long flags;

    flags = hints->flags;

    if (flags & XCB_ICCCM_SIZE_HINT_US_POSITION)
	printf ("      User supplied location: %s, %s\n",
		xscale (hints->x), yscale (hints->y));

    if (flags & XCB_ICCCM_SIZE_HINT_P_POSITION)
	printf ("      Program supplied location: %s, %s\n",
		xscale (hints->x), yscale (hints->y));

    if (flags & XCB_ICCCM_SIZE_HINT_US_SIZE) {
	printf ("      User supplied size: %s by %s\n",
		xscale (hints->width), yscale (hints->height));
    }

    if (flags & XCB_ICCCM_SIZE_HINT_P_SIZE)
	printf ("      Program supplied size: %s by %s\n",
		xscale (hints->width), yscale (hints->height));

    if (flags & XCB_ICCCM_SIZE_HINT_P_MIN_SIZE)
	printf ("      Program supplied minimum size: %s by %s\n",
		xscale (hints->min_width), yscale (hints->min_height));

    if (flags & XCB_ICCCM_SIZE_HINT_P_MAX_SIZE)
	printf ("      Program supplied maximum size: %s by %s\n",
		xscale (hints->max_width), yscale (hints->max_height));

    if (flags & XCB_ICCCM_SIZE_HINT_BASE_SIZE) {
	printf ("      Program supplied base size: %s by %s\n",
		xscale (hints->base_width), yscale (hints->base_height));
    }

    if (flags & XCB_ICCCM_SIZE_HINT_P_RESIZE_INC) {
	printf ("      Program supplied x resize increment: %s\n",
		xscale (hints->width_inc));
	printf ("      Program supplied y resize increment: %s\n",
		yscale (hints->height_inc));
	if (hints->width_inc != 0 && hints->height_inc != 0) {
	    if (flags & XCB_ICCCM_SIZE_HINT_US_SIZE)
		printf ("      User supplied size in resize increments:  %s by %s\n",
			(xscale (hints->width / hints->width_inc)),
			(yscale (hints->height / hints->height_inc)));
	    if (flags & XCB_ICCCM_SIZE_HINT_P_SIZE)
		printf ("      Program supplied size in resize increments:  %s by %s\n",
			(xscale (hints->width / hints->width_inc)),
			(yscale (hints->height / hints->height_inc)));
	    if (flags & XCB_ICCCM_SIZE_HINT_P_MIN_SIZE)
		printf ("      Program supplied minimum size in resize increments: %s by %s\n",
			xscale (hints->min_width / hints->width_inc), yscale (hints->min_height / hints->height_inc));
	    if (flags & XCB_ICCCM_SIZE_HINT_BASE_SIZE)
		printf ("      Program supplied base size in resize increments:  %s by %s\n",
			(xscale (hints->base_width / hints->width_inc)),
			(yscale (hints->base_height / hints->height_inc)));
	}
    }

    if (flags & XCB_ICCCM_SIZE_HINT_P_ASPECT) {
	printf ("      Program supplied min aspect ratio: %s/%s\n",
		xscale (hints->min_aspect_num), yscale (hints->min_aspect_den));
	printf ("      Program supplied max aspect ratio: %s/%s\n",
		xscale (hints->max_aspect_num), yscale (hints->max_aspect_den));
    }

    if (flags & XCB_ICCCM_SIZE_HINT_P_WIN_GRAVITY) {
	printf ("      Program supplied window gravity: %s\n",
		Lookup (hints->win_gravity, _gravities));
    }
}


/*
 * Display Size Hints info
 */
static void
Display_Size_Hints (struct wininfo *w)
{
    xcb_size_hints_t hints;

    printf ("\n");
    if (!fetch_normal_hints (w, &hints))
	printf ("  No normal window size hints defined\n");
    else {
	printf ("  Normal window size hints:\n");
	Display_Hints (&hints);
    }

    if (!xcb_icccm_get_wm_size_hints_reply (dpy, w->zoom_cookie, &hints, NULL))
	printf ("  No zoom window size hints defined\n");
    else {
	printf ("  Zoom window size hints:\n");
	Display_Hints (&hints);
    }
}


static void
Display_Window_Shape (xcb_window_t window)
{
    const xcb_query_extension_reply_t *shape_query;
    xcb_shape_query_extents_cookie_t extents_cookie;
    xcb_shape_query_extents_reply_t *extents;

    shape_query = xcb_get_extension_data (dpy, &xcb_shape_id);
    if (!shape_query->present)
	return;

    printf ("\n");

    extents_cookie = xcb_shape_query_extents (dpy, window);
    extents = xcb_shape_query_extents_reply (dpy, extents_cookie, &err);

    if (!extents) {
	if (err)
	    Print_X_Error (dpy, err);
	else
	{
	    printf ("  No window shape defined\n");
	    printf ("  No border shape defined\n");
	}
	return;
    }

    if (!extents->bounding_shaped)
	printf ("  No window shape defined\n");
    else {
	printf ("  Window shape extents:  %sx%s",
		xscale (extents->bounding_shape_extents_width),
		yscale (extents->bounding_shape_extents_height));
	printf ("+%s+%s\n",
		xscale (extents->bounding_shape_extents_x),
		yscale (extents->bounding_shape_extents_y));
    }
    if (!extents->clip_shaped)
	printf ("  No border shape defined\n");
    else {
	printf ("  Border shape extents:  %sx%s",
		xscale (extents->clip_shape_extents_width),
		yscale (extents->clip_shape_extents_height));
	printf ("+%s+%s\n",
		xscale (extents->clip_shape_extents_x),
		yscale (extents->clip_shape_extents_y));
    }

    free (extents);
}

/*
 * Display Window Manager Info
 *
 * Requires wininfo members initialized:
 *   window, hints_cookie
 */
static const binding _state_hints[] = {
	{ XCB_ICCCM_WM_STATE_WITHDRAWN, "Withdrawn State" },
	{ XCB_ICCCM_WM_STATE_NORMAL, "Normal State" },
	{ XCB_ICCCM_WM_STATE_ICONIC, "Iconic State" },
/* xwininfo previously also reported the ZoomState & InactiveState,
   but ICCCM declared those obsolete long ago */
	{ 0, NULL } };

#ifndef USE_XCB_ICCCM
static Bool
wm_hints_reply (xcb_connection_t *whr_dpy, xcb_get_property_cookie_t cookie,
		wm_hints_t *hints_return, xcb_generic_error_t **whr_err)
{
    xcb_get_property_reply_t *prop = xcb_get_property_reply (whr_dpy, cookie, whr_err);
    size_t length;

    if (!prop || (prop->type != XCB_ATOM_WM_HINTS) || (prop->format != 32)) {
	free (prop);
	return False;
    }

    memset (hints_return, 0, sizeof(wm_hints_t));

    length = (size_t) xcb_get_property_value_length(prop);
    if (length > sizeof(wm_hints_t))
	length = sizeof(wm_hints_t);
    memcpy (hints_return, xcb_get_property_value (prop), length);

    free (prop);
    return True;
}

#define xcb_icccm_get_wm_hints_reply wm_hints_reply
#endif

static void
Display_Atom_Name (xcb_atom_t atom, const char *prefix)
{
    const char *atom_name = Get_Atom_Name (dpy, atom);

    if (atom_name) {
	char *friendly_name = get_friendly_name (atom_name, prefix);
	printf ("          %s\n", friendly_name);
	free (friendly_name);
    } else {
	printf ("          (unresolvable ATOM 0x%x)\n", atom);
    }
}

static void
Display_WM_Info (struct wininfo *w)
{
    xcb_icccm_wm_hints_t wmhints;
    long flags;

    printf ("\n");
    if (!xcb_icccm_get_wm_hints_reply(dpy, w->hints_cookie, &wmhints, &err))
    {
	printf ("  No window manager hints defined\n");
	if (err)
	    Print_X_Error (dpy, err);
	flags = 0;
    } else
	flags = wmhints.flags;

    printf ("  Window manager hints:\n");

    if (flags & XCB_ICCCM_WM_HINT_INPUT)
	printf ("      Client accepts input or input focus: %s\n",
		Lookup (wmhints.input, _bool));

    if (flags & XCB_ICCCM_WM_HINT_ICON_WINDOW) {
	struct wininfo iw;
	iw.window = wmhints.icon_window;
	iw.net_wm_name_cookie = get_net_wm_name (dpy, iw.window);
	iw.wm_name_cookie = xcb_icccm_get_wm_name (dpy, iw.window);

	printf ("      Icon window id: ");
	Display_Window_Id (&iw, True);
    }

    if (flags & XCB_ICCCM_WM_HINT_ICON_POSITION)
	printf ("      Initial icon position: %s, %s\n",
		xscale (wmhints.icon_x), yscale (wmhints.icon_y));

    if (flags & XCB_ICCCM_WM_HINT_STATE)
	printf ("      Initial state is %s\n",
		Lookup (wmhints.initial_state, _state_hints));

    if (atom_net_wm_desktop) {
	xcb_get_property_reply_t *prop;

	prop = xcb_get_property_reply (dpy, w->wm_desktop_cookie, NULL);
	if (prop && (prop->type != XCB_NONE)) {
	    uint32_t *desktop = xcb_get_property_value (prop);
	    if (*desktop == 0xFFFFFFFF) {
		printf ("      Displayed on all desktops\n");
	    } else {
		printf ("      Displayed on desktop %d\n", *desktop);
	    }
	}
	free (prop);
    }

    if (atom_net_wm_window_type) {
	xcb_get_property_reply_t *prop;

	prop = xcb_get_property_reply (dpy, w->wm_window_type_cookie,
				       NULL);
	if (prop && (prop->type != XCB_NONE) && (prop->value_len > 0)) {
	    xcb_atom_t *atoms = xcb_get_property_value (prop);
	    int atom_count = prop->value_len;

	    if (atom_count > 0) {
		printf ("      Window type:\n");
		for (int i = 0; i < atom_count; i++)
		    Display_Atom_Name (atoms[i], "_NET_WM_WINDOW_TYPE_");
	    }
	}
	free (prop);
    }

    if (atom_net_wm_state) {
	xcb_get_property_reply_t *prop;

	prop = xcb_get_property_reply (dpy, w->wm_state_cookie, NULL);
	if (prop && (prop->type != XCB_NONE) && (prop->value_len > 0)) {
	    xcb_atom_t *atoms = xcb_get_property_value (prop);
	    int atom_count = prop->value_len;

	    if (atom_count > 0) {
		printf ("      Window state:\n");
		for (int i = 0; i < atom_count; i++)
		    Display_Atom_Name (atoms[i], "_NET_WM_STATE_");
	    }
	}
	free (prop);
    }

    if (atom_net_wm_pid) {
	xcb_get_property_reply_t *prop;

	printf ("      Process id: ");
	prop = xcb_get_property_reply (dpy, w->wm_pid_cookie, NULL);
	if (prop && (prop->type == XCB_ATOM_CARDINAL)) {
	    uint32_t *pid = xcb_get_property_value (prop);
	    printf ("%d", *pid);
	} else {
	    printf ("(unknown)");
	}
	free (prop);

	prop = xcb_get_property_reply (dpy, w->wm_client_machine_cookie, NULL);
	if (prop && (prop->type == XCB_ATOM_STRING)) {
	    const char *hostname = xcb_get_property_value (prop);
	    int hostname_len = xcb_get_property_value_length (prop);
	    printf (" on host %.*s", hostname_len, hostname);
	}
	printf ("\n");
	free (prop);
    }

    if (atom_net_frame_extents) {
	xcb_get_property_reply_t *prop;

	prop = xcb_get_property_reply (dpy, w->frame_extents_cookie, NULL);
	if (prop && (prop->type == XCB_ATOM_CARDINAL)
	    && (prop->value_len == 4)) {
	    uint32_t *extents = xcb_get_property_value (prop);

	    printf ("      Frame extents: %d, %d, %d, %d\n",
		    extents[0], extents[1], extents[2], extents[3]);
	}
	free (prop);
    }
}

/* Frees all members of a wininfo struct, but not the struct itself */
static void
wininfo_wipe (struct wininfo *w)
{
    free (w->geometry);
    free (w->win_attributes);
    free (w->normal_hints);
}

/* Gets UTF-8 encoded EMWH property _NET_WM_NAME for a window */
static xcb_get_property_cookie_t
get_net_wm_name (xcb_connection_t *gnwn_dpy, xcb_window_t win)
{
    if (!atom_net_wm_name)
	atom_net_wm_name = Get_Atom (gnwn_dpy, "_NET_WM_NAME");

    if (!atom_utf8_string)
	atom_utf8_string = Get_Atom (gnwn_dpy, "UTF8_STRING");

    if (atom_net_wm_name && atom_utf8_string)
	return xcb_get_property (gnwn_dpy, False, win, atom_net_wm_name,
				 atom_utf8_string, 0, BUFSIZ);
    else {
	xcb_get_property_cookie_t dummy = { 0 };
	return dummy;
    }
}

/* [Copied from code added by Yang Zhao to xprop/xprop.c]
 *
 * Validate a string as UTF-8 encoded according to RFC 3629
 *
 * Simply, a unicode code point (up to 21-bits long) is encoded as follows:
 *
 *    Char. number range  |        UTF-8 octet sequence
 *       (hexadecimal)    |              (binary)
 *    --------------------+---------------------------------------------
 *    0000 0000-0000 007F | 0xxxxxxx
 *    0000 0080-0000 07FF | 110xxxxx 10xxxxxx
 *    0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
 *    0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * Validation is done left-to-right, and an error condition, if any, refers to
 * only the left-most problem in the string.
 *
 * Return values:
 *   UTF8_VALID: Valid UTF-8 encoded string
 *   UTF8_OVERLONG: Using more bytes than needed for a code point
 *   UTF8_SHORT_TAIL: Not enough bytes in a multi-byte sequence
 *   UTF8_LONG_TAIL: Too many bytes in a multi-byte sequence
 *   UTF8_FORBIDDEN_VALUE: Forbidden prefix or code point outside 0x10FFFF
 */
#define UTF8_VALID 0
#define UTF8_FORBIDDEN_VALUE 1
#define UTF8_OVERLONG 2
#define UTF8_SHORT_TAIL 3
#define UTF8_LONG_TAIL 4
static int
is_valid_utf8 (const char *string, size_t len)
{
    unsigned long codepoint;
    int rem = 0;

    for (size_t i = 0; i < len; i++) {
	unsigned char c = (unsigned char) string[i];

	/* Order of type check:
	 *   - Single byte code point
	 *   - Non-starting byte of multi-byte sequence
	 *   - Start of 2-byte sequence
	 *   - Start of 3-byte sequence
	 *   - Start of 4-byte sequence
	 */
	if (!(c & 0x80)) {
	    if (rem > 0) return UTF8_SHORT_TAIL;
	    rem = 0;
	    codepoint = c;
	} else if ((c & 0xC0) == 0x80) {
	    if (rem == 0) return UTF8_LONG_TAIL;
	    rem--;
	    codepoint |= (c & 0x3F) << (rem * 6);
	    if (codepoint == 0) return UTF8_OVERLONG;
	} else if ((c & 0xE0) == 0xC0) {
	    if (rem > 0) return UTF8_SHORT_TAIL;
	    rem = 1;
	    codepoint = (c & 0x1F) << 6;
	    if (codepoint == 0) return UTF8_OVERLONG;
	} else if ((c & 0xF0) == 0xE0) {
	    if (rem > 0) return UTF8_SHORT_TAIL;
	    rem = 2;
	    codepoint = (c & 0x0F) << 12;
	} else if ((c & 0xF8) == 0xF0) {
	    if (rem > 0) return UTF8_SHORT_TAIL;
	    rem = 3;
	    codepoint = (c & 0x07) << 18;
	    if (codepoint > 0x10FFFF) return UTF8_FORBIDDEN_VALUE;
	} else
	    return UTF8_FORBIDDEN_VALUE;
    }

    return UTF8_VALID;
}

/*
 * Converts a UTF-8 encoded string to the current locale encoding,
 * if possible, and prints it, with prefix before and suffix after.
 * Length of the string is specified in bytes, or -1 for going until '\0'
 */
static void
print_utf8 (const char *prefix, const char *u8str, size_t length, const char *suffix)
{
    size_t inlen = length;

    if (is_valid_utf8 (u8str, inlen) != UTF8_VALID) {
	printf (" (invalid UTF8_STRING)");
	return;
    }

    if (strcmp (user_encoding, "UTF-8") == 0) {
	/* Don't need to convert */
	printf ("%s", prefix);
	fwrite (u8str, 1, inlen, stdout);
	printf ("%s", suffix);
	return;
    }

#ifdef HAVE_ICONV
    if (!iconv_from_utf8) {
	iconv_from_utf8 = iconv_open (user_encoding, "UTF-8");
    }

    if (iconv_from_utf8 != (iconv_t) -1) {
	Bool done = True;
	ICONV_CONST char *inp = (ICONV_CONST char *) u8str;
	char convbuf[BUFSIZ];

	printf ("%s", prefix);
	do {
	    char *outp = convbuf;
	    size_t outlen = sizeof(convbuf);

	    int convres = iconv (iconv_from_utf8, &inp, &inlen, &outp, &outlen);

	    if ((convres == -1) && (errno == E2BIG)) {
		done = False;
		convres = 0;
	    }

	    if (convres == 0) {
		fwrite (convbuf, 1, sizeof(convbuf) - outlen, stdout);
	    } else {
		printf (" (failure in conversion from UTF8_STRING to %s)",
			user_encoding);
	    }
	} while (!done);
	printf ("%s", suffix);
    } else {
	printf (" (can't load iconv conversion for UTF8_STRING to %s)",
		user_encoding);
    }
#else
    printf (" (can't convert UTF8_STRING to %s)", user_encoding);
#endif
}

/*
 * Takes a string such as an atom name, strips the prefix, converts
 * underscores to spaces, lowercases all but the first letter of each word,
 * and returns it. The returned string should be freed by the caller.
 */
static char *
get_friendly_name (const char *string, const char *prefix)
{
    const char *name_start = string;
    char *lowered_name;
    Bool first = True;
    size_t prefix_len = strlen (prefix);

    if (strncmp (name_start, prefix, prefix_len) == 0) {
	name_start += prefix_len;
    }

    lowered_name = strdup (name_start);
    if (lowered_name == NULL)
	Fatal_Error ("Failed to allocate memory in get_friendly_name");

    for (char *n = lowered_name ; *n != 0 ; n++) {
	if (*n == '_') {
	    *n = ' ';
	    first = True;
	} else if (first) {
	    first = False;
	} else {
	    *n = tolower((unsigned char)*n);
	}
    }

    return lowered_name;
}

