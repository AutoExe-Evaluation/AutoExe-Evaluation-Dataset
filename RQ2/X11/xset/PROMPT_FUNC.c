Status
XkbGetControls(Display *dpy, unsigned long which, XkbDescPtr xkb)
{
    // PRE: true

    register xkbGetControlsReq *req;
    xkbGetControlsReply rep;
    XkbControlsPtr ctrls;
    XkbInfoPtr xkbi;

    if ((dpy->flags & XlibDisplayNoXkb) ||
        (!dpy->xkb_info && !XkbUseExtension(dpy, NULL, NULL)))
        return BadAccess;
    if ((!xkb) || (!which))
        return BadMatch;

    LockDisplay(dpy);
    xkbi = dpy->xkb_info;
    GetReq(kbGetControls, req);
    if (!xkb->ctrls) {
        xkb->ctrls = _XkbTypedCalloc(1, XkbControlsRec);
        if (!xkb->ctrls) {
            UnlockDisplay(dpy);
            SyncHandle();
            return BadAlloc;
        }
    }
    req->reqType = xkbi->codes->major_opcode;
    req->xkbReqType = X_kbGetControls;
    req->deviceSpec = xkb->device_spec;
    if (!_XReply(dpy, (xReply *) &rep,
                 (SIZEOF(xkbGetControlsReply) - SIZEOF(xReply)) >> 2, xFalse)) {
        UnlockDisplay(dpy);
        SyncHandle();
        return BadImplementation;
    }
    if (xkb->device_spec == XkbUseCoreKbd)
        xkb->device_spec = rep.deviceID;
    ctrls = xkb->ctrls;
    if (which & XkbControlsEnabledMask)
        ctrls->enabled_ctrls = rep.enabledCtrls;
    ctrls->num_groups = rep.numGroups;
    if (which & XkbGroupsWrapMask)
        ctrls->groups_wrap = rep.groupsWrap;
    if (which & XkbInternalModsMask) {
        ctrls->internal.mask = rep.internalMods;
        ctrls->internal.real_mods = rep.internalRealMods;
        ctrls->internal.vmods = rep.internalVMods;
    }
    if (which & XkbIgnoreLockModsMask) {
        ctrls->ignore_lock.mask = rep.ignoreLockMods;
        ctrls->ignore_lock.real_mods = rep.ignoreLockRealMods;
        ctrls->ignore_lock.vmods = rep.ignoreLockVMods;
    }
    if (which & XkbRepeatKeysMask) {
        ctrls->repeat_delay = rep.repeatDelay;
        ctrls->repeat_interval = rep.repeatInterval;
    }
    if (which & XkbSlowKeysMask)
        ctrls->slow_keys_delay = rep.slowKeysDelay;
    if (which & XkbBounceKeysMask)
        ctrls->debounce_delay = rep.debounceDelay;
    if (which & XkbMouseKeysMask) {
        ctrls->mk_dflt_btn = rep.mkDfltBtn;
    }
    if (which & XkbMouseKeysAccelMask) {
        ctrls->mk_delay = rep.mkDelay;
        ctrls->mk_interval = rep.mkInterval;
        ctrls->mk_time_to_max = rep.mkTimeToMax;
        ctrls->mk_max_speed = rep.mkMaxSpeed;
        ctrls->mk_curve = rep.mkCurve;
    }
    if (which & XkbAccessXKeysMask)
        ctrls->ax_options = rep.axOptions;
    if (which & XkbStickyKeysMask) {
        ctrls->ax_options &= ~XkbAX_SKOptionsMask;
        ctrls->ax_options |= rep.axOptions & XkbAX_SKOptionsMask;
    }
    if (which & XkbAccessXFeedbackMask) {
        ctrls->ax_options &= ~XkbAX_FBOptionsMask;
        ctrls->ax_options |= rep.axOptions & XkbAX_FBOptionsMask;
    }
    if (which & XkbAccessXTimeoutMask) {
        ctrls->ax_timeout = rep.axTimeout;
        ctrls->axt_ctrls_mask = rep.axtCtrlsMask;
        ctrls->axt_ctrls_values = rep.axtCtrlsValues;
        ctrls->axt_opts_mask = rep.axtOptsMask;
        ctrls->axt_opts_values = rep.axtOptsValues;
    }
    if (which & XkbPerKeyRepeatMask) {
        memcpy(ctrls->per_key_repeat, rep.perKeyRepeat, XkbPerKeyBitArraySize);
    }
    UnlockDisplay(dpy);
    SyncHandle();
    return Success;
}

/*  This is the information-getting function for telling the user what the
 *  current "xsettings" are.
 */
static void
query(Display *dpy)
{
    int scr = DefaultScreen(dpy);
    XKeyboardState values;
    int acc_num, acc_denom, threshold;
    int timeout, interval, prefer_blank, allow_exp;

#ifdef XKB
    XkbDescPtr xkb;
    int xkbmajor = XkbMajorVersion, xkbminor = XkbMinorVersion;
    int xkbopcode, xkbevent, xkberror;
#endif
    char **font_path;
    int npaths;
    int i, j;
    char buf[20];		       /* big enough for 16 bit number */

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
#ifdef XKB
    if (XkbQueryExtension(dpy, &xkbopcode, &xkbevent, &xkberror, &xkbmajor,
			  &xkbminor)
	&& (xkb = XkbAllocKeyboard()) != NULL) {
	if (XkbGetNames(dpy, XkbIndicatorNamesMask, xkb) == Success) {
	    Atom iatoms[XkbNumIndicators];
	    char *iatomnames[XkbNumIndicators];
	    Bool istates[XkbNumIndicators];
	    int inds[XkbNumIndicators];
	    int activecount = 0;
	    int maxnamelen = 0;

	    printf("  XKB indicators:\n");

	    for (i = 0, j = 0; i < XkbNumIndicators; i++) {
		if (xkb->names->indicators[i] != None) {
		    iatoms[j++] =  xkb->names->indicators[i];
		}
	    }

	    if (XGetAtomNames(dpy, iatoms, j, iatomnames)) {
		for (i = 0; i < j; i++) {
		    if (XkbGetNamedIndicator(dpy, iatoms[i], &inds[i],
					     &istates[i], NULL, NULL)) {
			int namelen = (int) strlen(iatomnames[i]);
			if (namelen > maxnamelen) {
			    maxnamelen = namelen;
			}
			activecount++;
		    } else {
			inds[i] = -1;
		    }
		}
	    }

	    if (activecount == 0) {
		printf("    None\n");
	    } else {
		int columnwidth;
		int linewidth;

#define XKB_IND_FORMAT_CHARS 13 /* size of other chars in '    DD: X: off' */
#define MAX_LINE_WIDTH	     76

		columnwidth = maxnamelen + XKB_IND_FORMAT_CHARS;
		if (columnwidth > MAX_LINE_WIDTH) {
		    columnwidth = MAX_LINE_WIDTH;
		}

		for (i = 0, linewidth = 0; i < activecount ; i++) {
		    if (inds[i] != -1) {
			int spaces = columnwidth - XKB_IND_FORMAT_CHARS
			    - (int) strlen(iatomnames[i]);

			if (spaces < 0)
			    spaces = 0;

			linewidth += printf("    %02d: %s: %*s",
					    inds[i], iatomnames[i],
					    spaces + 3,
					    on_or_off(istates[i],
						      True,  "on ",
						      False, "off",
						      buf, sizeof(buf)));
		    }
		    if (linewidth > (MAX_LINE_WIDTH - columnwidth)) {
			printf("\n");
			linewidth = 0;
		    }
		}
		if (linewidth > 0) {
		    printf("\n");
		}
	    }
	}
	if (XkbGetControls(dpy, XkbRepeatKeysMask, xkb) == Success) {
        // POST: xkb->ctrls->repeat_interval != 0
	    printf("  auto repeat delay:  %d    repeat rate:  %d\n",
		   xkb->ctrls->repeat_delay,
		   1000 / xkb->ctrls->repeat_interval);
	}
    }
#ifdef XF86MISC
    else
#endif
#endif
#ifdef XF86MISC
    {
	int dummy;
	XF86MiscKbdSettings kbdinfo;

	if (XF86MiscQueryExtension(dpy, &dummy, &dummy) &&
	    XF86MiscGetKbdSettings(dpy, &kbdinfo))
	    printf("  auto repeat delay:  %d    repeat rate:  %d\n",
	           kbdinfo.delay, kbdinfo.rate);
    }
#endif
    printf("  auto repeating keys:  ");
    for (i = 0; i < 4; i++) {
	if (i)
	    printf("                        ");
	for (j = 0; j < 8; j++) {
	    printf("%02x", (unsigned char)values.auto_repeats[i * 8 + j]);
	}
	printf("\n");
    }
    printf("  bell percent:  %d    bell pitch:  %d    bell duration:  %d\n",
	   values.bell_percent, values.bell_pitch, values.bell_duration);

    printf("Pointer Control:\n");
    printf("  acceleration:  %d/%d    threshold:  %d\n",
	   acc_num, acc_denom, threshold);

    printf("Screen Saver:\n");
    printf("  prefer blanking:  %s    ",
	   on_or_off(prefer_blank, PreferBlanking, "yes",
		     DontPreferBlanking, "no", buf, sizeof(buf)));
    printf("allow exposures:  %s\n",
	   on_or_off(allow_exp, AllowExposures, "yes",
		     DontAllowExposures, "no", buf, sizeof(buf)));
    printf("  timeout:  %d    cycle:  %d\n", timeout, interval);

    printf("Colors:\n");
    printf("  default colormap:  0x%lx    BlackPixel:  0x%lx    WhitePixel:  0x%lx\n",
	   DefaultColormap(dpy, scr), BlackPixel(dpy, scr), WhitePixel(dpy,
								       scr));

    printf("Font Path:\n");
    if (npaths) {
	printf("  %s", *font_path++);
	for (--npaths; npaths; npaths--)
	    printf(",%s", *font_path++);
	printf("\n");
    } else {
	printf("  (empty)\n");
    }

#ifdef MITMISC
    {
	int dummy;

	if (XMITMiscQueryExtension(dpy, &dummy, &dummy)) {
	    if (XMITMiscGetBugMode(dpy))
		printf("Bug Mode: compatibility mode is enabled\n");
	    else
		printf("Bug Mode: compatibility mode is disabled\n");
	}
    }
#endif
#ifdef DPMSExtension
    {

	int dummy;
	CARD16 standby, suspend, off;
	BOOL onoff;
	CARD16 state;

	printf("DPMS (Display Power Management Signaling):\n");
	if (DPMSQueryExtension(dpy, &dummy, &dummy)) {
	    if (DPMSCapable(dpy)) {
		DPMSGetTimeouts(dpy, &standby, &suspend, &off);
		printf("  Standby: %d    Suspend: %d    Off: %d\n",
		       standby, suspend, off);
		DPMSInfo(dpy, &state, &onoff);
		if (onoff) {
		    printf("  DPMS is Enabled\n");
		    switch (state) {
		    case DPMSModeOn:
			printf("  Monitor is On\n");
			break;
		    case DPMSModeStandby:
			printf("  Monitor is in Standby\n");
			break;
		    case DPMSModeSuspend:
			printf("  Monitor is in Suspend\n");
			break;
		    case DPMSModeOff:
			printf("  Monitor is Off\n");
			break;
		    default:
			printf("  Unrecognized response from server\n");
		    }
		} else
		    printf("  DPMS is Disabled\n");
	    } else
		printf("  Display is not capable of DPMS\n");
	} else {
	    printf("  Server does not have the DPMS Extension\n");
	}
    }
#endif
#ifdef FONTCACHE
    {
	int dummy;

	printf("Font cache:\n");
	if (FontCacheQueryExtension(dpy, &dummy, &dummy)) {
            FontCacheSettings cs;

	    if (FontCacheGetCacheSettings(dpy, &cs)) {
		int himark = cs.himark / 1024;
		int lowmark = cs.lowmark / 1024;
		int balance = cs.balance;

		printf("  hi-mark (KB): %d  low-mark (KB): %d  balance (%%): %d\n",
		       himark, lowmark, balance);
	    }
	} else {
	    printf("  Server does not have the FontCache Extension\n");
	}
    }
#endif
#ifdef XF86MISC
    {
	int dummy;
	int maj, min;
	XF86MiscFilePaths paths;

	if (XF86MiscQueryExtension(dpy, &dummy, &dummy) &&
	    XF86MiscQueryVersion(dpy, &maj, &min) &&
	    ((maj > 0) || (maj == 0 && min >= 7)) &&
	    XF86MiscGetFilePaths(dpy, &paths)) {
	    printf("File paths:\n");
	    printf("  Config file:  %s\n", paths.configfile);
	    printf("  Modules path: %s\n", paths.modulepath);
	    printf("  Log file:     %s\n", paths.logfile);
	}
    }
#endif

    return;
}
