#define EXT_NAMES(tp,i,limit,index,table) table[i]
#define ExtBoolname(tp,i,names) EXT_NAMES(tp, i, BOOLCOUNT, (i - (tp->num_Booleans - tp->ext_Booleans)), names
#define same_name(a,b) !strcmp(a,b)
NCURSES_EXPORT(int)
NCURSES_SP_NAME(tigetflag) (NCURSES_SP_DCLx const char *str)
{
    if (HasTInfoTerminal(SP_PARM)) {
	TERMTYPE2 *tp = &TerminalType(TerminalOf(SP_PARM));
    if (entry_ptr != 0) {
    }
	else {
	    int i;
	    {
		const char *capname = ExtBoolname(tp, i, boolnames);	// PRE: true
		if (same_name(str, capname)) { 							// POST: capname != NULL
		}
	    }
	}
    }
}
