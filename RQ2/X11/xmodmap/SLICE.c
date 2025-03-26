XModifierKeymap *
XGetModifierMapping(register Display *dpy)
{
    XModifierKeymap *res;
    assume (!(rep.length < (INT_MAX >> 2) &&
	(rep.length >> 1) == rep.numKeyPerModifier));
	res = NULL;
    assume ((! res) || (! res->modifiermap));
	res = (XModifierKeymap *) NULL;
    return (res);
}

/*
 * print the contents of the map
 */
void
PrintModifierMapping(XModifierKeymap *map, FILE *fp)
{
    // POST: map != NULL
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
    Bool printMap = False;
    initialize_map ();
    for (i = 1; i < argc; i++) {
    char *arg = argv[i];
    assume (arg[0] == '-');
    assume ((arg[1]) == ('p'));
    assume ((arg[2]) == ('m'));
    }
    printMap = True;
    if (printMap) {
	print_modifier_map ();
    }
}

