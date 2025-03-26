void
xcb_visualtype_next (xcb_visualtype_iterator_t *i)
{
    --i->rem;
    ++i->data;
    i->index += sizeof(xcb_visualtype_t);
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

xcb_depth_iterator_t
xcb_screen_allowed_depths_iterator (const xcb_screen_t *R)
{
    xcb_depth_iterator_t i;
    i.data = (xcb_depth_t *) (R + 1);
    i.rem = R->allowed_depths_len;
    i.index = (char *) i.data - (char *) R;
    return i;
}

xcb_get_window_attributes_reply_t *
xcb_get_window_attributes_reply (xcb_connection_t                    *c,
                                 xcb_get_window_attributes_cookie_t   cookie  /**< */,
                                 xcb_generic_error_t                **e)
{
    return (xcb_get_window_attributes_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

static xcb_connection_t *dpy;
static xcb_screen_t *screen;

static xcb_get_window_attributes_reply_t *
fetch_win_attributes (struct wininfo *w)
{
    if (!w->win_attributes) {
	w->win_attributes =
	    xcb_get_window_attributes_reply (dpy, w->attr_cookie, &err);
	assume (!(!w->win_attributes));
    }
    return w->win_attributes;
}

static void
Display_Stats_Info (struct wininfo *w)
{
    // PRE: screen != NULL
    xcb_get_window_attributes_reply_t *win_attributes;
    win_attributes = fetch_win_attributes (w);
    if (screen)
    {
	xcb_depth_iterator_t depth_iter;
	depth_iter = xcb_screen_allowed_depths_iterator (screen);
	for (; depth_iter.rem; xcb_depth_next (&depth_iter)) {
	    xcb_visualtype_iterator_t visual_iter;
	    visual_iter = xcb_depth_visuals_iterator (depth_iter.data);
	    for (; visual_iter.rem; xcb_visualtype_next (&visual_iter)) {
                // POST: "visual_iter is within the bounds of the object"
		}
	    }
	}
}
