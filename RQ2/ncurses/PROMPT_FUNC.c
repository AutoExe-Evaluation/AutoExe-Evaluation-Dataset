NCURSES_EXPORT(int)
NCURSES_SP_NAME(tigetflag) (NCURSES_SP_DCLx const char *str)
{
    int result = ABSENT_BOOLEAN;

    T((T_CALLED("tigetflag(%p, %s)"), (void *) SP_PARM, str));

    if (HasTInfoTerminal(SP_PARM)) {
	TERMTYPE2 *tp = &TerminalType(TerminalOf(SP_PARM));
	struct name_table_entry const *entry_ptr;
	int j = -1;

	entry_ptr = _nc_find_type_entry(str, BOOLEAN, FALSE);
	if (entry_ptr != 0) {
	    j = entry_ptr->nte_index;
	}
#if NCURSES_XNAMES
	else {
	    int i;
	    for_each_ext_boolean(i, tp) {
		const char *capname = ExtBoolname(tp, i, boolnames);    // PRE: true
		if (same_name(str, capname)) {                          // POST: capname != NULL
		    j = i;
		    break;
		}
	    }
	}
#endif
	if (j >= 0) {
	    /* note: setupterm forces invalid booleans to false */
	    result = tp->Booleans[j];
	}
    }

    returnCode(result);
}
