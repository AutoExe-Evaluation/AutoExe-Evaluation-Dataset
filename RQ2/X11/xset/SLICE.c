Status
XkbGetControls(Display *dpy, unsigned long which, XkbDescPtr xkb)
{
    // PRE: true
    xkbGetControlsReply rep;
    XkbControlsPtr ctrls;
    assume (!((!xkb) || (!which)));
    assume (!(!xkb->ctrls));
    assume (!(!_XReply(dpy, (xReply *) &rep,
                 (SIZEOF(xkbGetControlsReply) - SIZEOF(xReply)) >> 2, xFalse)));
    assume (!(xkb->device_spec == XkbUseCoreKbd));
    ctrls = xkb->ctrls;
    ctrls->num_groups = rep.numGroups;
    if (which & XkbRepeatKeysMask) {
        ctrls->repeat_delay = rep.repeatDelay;
        ctrls->repeat_interval = rep.repeatInterval;
    }
    return Success;
}

static void
query(Display *dpy)
{
    XkbDescPtr xkb;
    int xkbmajor = XkbMajorVersion, xkbminor = XkbMinorVersion;
    int xkbopcode, xkbevent, xkberror;
    XGetKeyboardControl(dpy, &values);
    XGetPointerControl(dpy, &acc_num, &acc_denom, &threshold);
    XGetScreenSaver(dpy, &timeout, &interval, &prefer_blank, &allow_exp);
    font_path = XGetFontPath(dpy, &npaths);
    printf("Keyboard Control:\n");
    printf
	("  auto repeat:  %s    key click percent:  %d    LED mask:  %08lx\n",
	 on_or_off(values.global_auto_repeat, AutoRepeatModeOn, "on",
		   AutoRepeatModeOff, "off", buf, sizeof(buf)),
	 values.key_click_percent, values.led_mask);
    if (XkbQueryExtension(dpy, &xkbopcode, &xkbevent, &xkberror, &xkbmajor,
			  &xkbminor)
	&& (xkb = XkbAllocKeyboard()) != NULL) {
	if (XkbGetNames(dpy, XkbIndicatorNamesMask, xkb) == Success) {
	}
	if (XkbGetControls(dpy, XkbRepeatKeysMask, xkb) == Success) {
        // POST: xkb->ctrls->repeat_interval != 0
	}
    }
}
