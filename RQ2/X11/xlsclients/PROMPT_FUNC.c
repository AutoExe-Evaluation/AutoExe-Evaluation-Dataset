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

