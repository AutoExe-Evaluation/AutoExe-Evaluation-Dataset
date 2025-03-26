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
