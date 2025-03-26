XModifierKeymap *
XGetModifierMapping(register Display *dpy)
{
    xGetModifierMappingReply rep;
    _X_UNUSED register xReq *req;
    unsigned long nbytes;
    XModifierKeymap *res;

    LockDisplay(dpy);
    GetEmptyReq(GetModifierMapping, req);
    (void) _XReply (dpy, (xReply *)&rep, 0, xFalse);

    if (rep.length < (INT_MAX >> 2) &&
	(rep.length >> 1) == rep.numKeyPerModifier) {
	nbytes = (unsigned long)rep.length << 2;
	res = Xmalloc(sizeof (XModifierKeymap));
	if (res)
	    res->modifiermap = Xmalloc (nbytes);
    } else
	res = NULL;
    if ((! res) || (! res->modifiermap)) {
	Xfree(res);
	res = (XModifierKeymap *) NULL;
	_XEatDataWords(dpy, rep.length);
    } else {
	_XReadPad(dpy, (char *) res->modifiermap, (long) nbytes);
	res->max_keypermod = rep.numKeyPerModifier;
    }

    UnlockDisplay(dpy);
    SyncHandle();
    return (res);
}

/*
 * print the contents of the map
 */
void
PrintModifierMapping(XModifierKeymap *map, FILE *fp)
{
    // POST: map != NULL
    int k = 0;
    int keysyms_per_keycode = GetKeysymsPerKeycode();

    fprintf (fp,
    	     "%s:  up to %d keys per modifier, (keycodes in parentheses):\n\n", 
    	     ProgramName, map->max_keypermod);
    for (int i = 0; i < 8; i++) {
	fprintf(fp, "%-10s", modifier_table[i].name);

	for (int j = 0; j < map->max_keypermod; j++) {
	    if (map->modifiermap[k]) {
		KeySym ks;
		int index = 0;
		char *nm;
		do {
		    ks = XKeycodeToKeysym(dpy, map->modifiermap[k], index);
		    index++;
		} while ( !ks && index < keysyms_per_keycode);
		nm = XKeysymToString(ks);

		fprintf (fp, "%s  %s (0x%0x)", (j > 0 ? "," : ""), 
			 (nm ? nm : "BadKey"), map->modifiermap[k]);
	    }
	    k++;
	}
	fprintf(fp, "\n");
    }
    fprintf (fp, "\n");
    return;
}

static XModifierKeymap *map = NULL;

void
initialize_map (void)
{
    map = XGetModifierMapping (dpy);
    return;
}

void 
print_modifier_map(void)
{
    PrintModifierMapping (map, stdout);
    return;
}

int
main(int argc, char *argv[])
{
    // PRE: true
    
    int i;
    char *displayname = NULL;
    int status;
    Bool printMap = False;
    Bool printKeyTable = False;
    Bool printKeyTableExprs = False;
    Bool printPointerMap = False;
    Bool didAnything = False;

    ProgramName = argv[0];

    /*
     * scan the arg list once to find out which display to use
     */

    for (i = 1; i < argc; i++) {
	const char *arg = argv[i];

	if (arg[0] == '-') {
	    switch (arg[1]) {
	    case 'd':			/* -display host:dpy */
		if (++i >= argc) missing_arg(arg);
		displayname = argv[i];
		break;
	    case 'g':			/* -grammar */
		grammar_usage ();
		/*NOTREACHED*/
	    case 'h':			/* -help */
	    case '?':
		usage(0);
	    case 'v':
		if (strcmp(arg, "-version") == 0) {
		    puts("1.0.11");
		    exit(0);
		}
	    }
	}
    }

    dpy = XOpenDisplay (displayname);
    if (!dpy) {
	fprintf (stderr, "%s:  unable to open display '%s'\n",
		 ProgramName, XDisplayName (displayname));
	Exit (1);
    }

    XDisplayKeycodes (dpy, &min_keycode, &max_keycode);

    initialize_map ();

    /*
     * scan the arg list again to do the actual work (since it requires
     * the display being open.
     */

    for (i = 1; i < argc; i++) {
	char *arg = argv[i];

	if (arg[0] == '-') {
	    switch (arg[1]) {
	      case 'd':			/* -display host:dpy */
		++i;			/* handled above */
		continue;
	      case 'v':			/* -verbose */
		verbose = True;
		continue;
	      case 'q':			/* -quiet */
		verbose = False;
		continue;
	      case 'n':			/* -n (like make) */
		dontExecute = True;
		continue;
	      case 'e':			/* -e expression */
		didAnything = True;
		if (++i >= argc) missing_arg(arg);
		process_line (argv[i]);
		continue;
	      case 'p':			/* -p... */
		switch (arg[2]) {
		  case '\0':
		  case 'm':		/* -pm */
		    printMap = True;
		    break;
		  case 'k':		/* -pk, -pke */
		    switch (arg[3]) {
		    case '\0':
			printKeyTable = True;
			break;
		    case 'e':
			printKeyTableExprs = True;
			break;
		    default:
			unknown_arg(arg);
		    }
		    break;
		  case 'p':		/* -pp */
		    printPointerMap = True;
		    break;
		  default:
		    unknown_arg(arg);
		    /* NOTREACHED */
		}
		didAnything = True;
		continue;
	      case 'g':			/* -grammar */
		grammar_usage ();
		/*NOTREACHED*/
	      case '\0':		/* - (use standard input) */
		didAnything = True;
		process_file (NULL);
		continue;

	      /*
	       * provide old xmodmap args
	       */
	      case 'S':
		didAnything = True;
		process_line ("clear shift");
		continue;
	      case 'L':
		didAnything = True;
		process_line ("clear lock");
		continue;
	      case 'C':
		didAnything = True;
		process_line ("clear control");
		continue;
	      case '1':
	      case '2':
	      case '3':
	      case '4':
	      case '5': {
		  char cmd[11] = "clear modX";
		  cmd[9] = arg[1];
		  process_line (cmd);
		  continue;
	      }
	      case 's':
	      case 'l':
	      case 'c': {
		  char *cmd;
		  didAnything = True;
		  if (++i >= argc) missing_arg(arg);
		  if (asprintf (&cmd, "remove %s = %s",
				  ((arg[1] == 's') ? "shift" :
				   ((arg[1] == 'l') ? "lock" :
				    "control")), argv[i]) == -1)
		      FatalError("Could not allocate memory for remove cmd");
		  process_line (cmd);
		  continue;
	      }
	      default:
		unknown_arg(arg);
		/*NOTREACHED*/
	    }
	} else if (arg[0] == '+') {	/* old xmodmap args */
	    switch (arg[1]) {
	      case '1':
	      case '2':
	      case '3':
	      case '4':
	      case '5': {
		  char *cmd;
		  didAnything = True;
		  if (++i >= argc) missing_arg(arg);
		  if (asprintf (&cmd, "add mod%c = %s", arg[1], argv[i]) == -1)
		      FatalError("Could not allocate memory for add cmd");
		  process_line (cmd);
		  continue;
	      }
	      case 'S':
	      case 'L':
	      case 'C':
		arg[1] = tolower (arg[1]);
		/* fall through - to handler below */
	      case 's':
	      case 'l':
	      case 'c': {
		  char *cmd;
		  didAnything = True;
		  if (++i >= argc) missing_arg(arg);
		  if (asprintf (&cmd, "add %s = %s",
				  ((arg[1] == 's') ? "shift" :
				   ((arg[1] == 'l') ? "lock" :
				    "control")), argv[i]) == -1)
		      FatalError("Could not allocate memory for remove cmd");
		  process_line (cmd);
		  continue;
	      }
	      default:
		unknown_arg(arg);
	    }
	} else {
	    didAnything = True;
	    process_file (arg);
	    continue;
	}
    }					/* end for loop */

    /* for compatibility */
    if (!didAnything) printMap = True;

    /*
     * at this point, the work list has been built and we can view it or
     * execute it
     */

    if (dontExecute) {
	print_work_queue ();
	Exit (0);
    }

    if (parse_errors != 0) {
	fprintf (stderr, "%s:  %d error%s encountered, aborting.\n",
		 ProgramName, parse_errors,
		 (parse_errors == 1 ? "" : "s"));
	status = -1;	/* return an error condition */
    } else {
	status = execute_work_queue ();
    }

    if (printMap) {
	print_modifier_map ();
    }

    if (printKeyTable) {
	print_key_table (False);
    }

    if (printKeyTableExprs) {
	print_key_table (True);
    }

    if (printPointerMap) {
	print_pointer_map ();
    }

    Exit (status < 0 ? 1 : 0);

    /* Muffle gcc */
    return 0;
}

