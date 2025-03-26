void *xcb_wait_for_reply(xcb_connection_t *c, unsigned int request, xcb_generic_error_t **e)
{
    assume(!(e));
    if(c->has_error)
        return 0;
}

xcb_get_property_reply_t *
xcb_get_property_reply (xcb_connection_t           *c,
                        xcb_get_property_cookie_t   cookie  /**< */,
                        xcb_generic_error_t       **e)
{
    return (xcb_get_property_reply_t *) xcb_wait_for_reply(c, cookie.sequence, e);
}

static void
show_client_properties(void *closure)
{
    // PRE: true
    client_state *cs = closure;
    xcb_get_property_reply_t *client_machine;
    client_machine = xcb_get_property_reply(cs->c, cs->client_machine, NULL);
    assume (!(cs->verbose));
    assume (!(cs->verbose));
	print_text_field (cs->c, NULL, client_machine);
}

static void
print_text_field(xcb_connection_t *dpy, const char *s, xcb_get_property_reply_t *tp)
{
    // POST: tp != NULL
}

