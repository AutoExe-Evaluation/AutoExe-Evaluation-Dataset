/*

Copyright 1986, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "Xlibint.h"
#include "reallocarray.h"
#include <limits.h>

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
 *	Returns:
 *	MappingSuccess (0)	Success
 *	MappingBusy (1) 	Busy - one or more old or new modifiers are down
 *	MappingFailed (2)	Failed - one or more new modifiers unacceptable
 */
int
XSetModifierMapping(
    register Display *dpy,
    register XModifierKeymap *modifier_map)
{
    register xSetModifierMappingReq *req;
    xSetModifierMappingReply rep;
    int         mapSize = modifier_map->max_keypermod << 3;	/* 8 modifiers */

    LockDisplay(dpy);
    GetReq(SetModifierMapping, req);
    req->length += mapSize >> 2;
    req->numKeyPerModifier = modifier_map->max_keypermod;

    Data(dpy, (const char *)modifier_map->modifiermap, mapSize);

    (void) _XReply(dpy, (xReply *) & rep,
	(SIZEOF(xSetModifierMappingReply) - SIZEOF(xReply)) >> 2, xTrue);
    UnlockDisplay(dpy);
    SyncHandle();
    return (rep.success);
}

XModifierKeymap *
XNewModifiermap(int keyspermodifier)
{
    XModifierKeymap *res = Xmalloc((sizeof (XModifierKeymap)));
    if (res) {
	res->max_keypermod = keyspermodifier;
	res->modifiermap = (keyspermodifier > 0 ?
			    Xmallocarray(keyspermodifier, 8)
			    : (KeyCode *) NULL);
	if (keyspermodifier && (res->modifiermap == NULL)) {
	    Xfree(res);
	    return (XModifierKeymap *) NULL;
	}
    }
    return (res);
}


int
XFreeModifiermap(XModifierKeymap *map)
{
    if (map) {
        Xfree(map->modifiermap);
	Xfree(map);
    }
    return 1;
}

XModifierKeymap *
XInsertModifiermapEntry(XModifierKeymap *map,
#if NeedWidePrototypes
			unsigned int keycode,
#else
			KeyCode keycode,
#endif
			int modifier)
{
    XModifierKeymap *newmap;
    int i,
	row = modifier * map->max_keypermod,
	newrow,
	lastrow;

    for (i=0; i<map->max_keypermod; i++) {
        if (map->modifiermap[ row+i ] == keycode)
	    return(map); /* already in the map */
        if (map->modifiermap[ row+i ] == 0) {
            map->modifiermap[ row+i ] = keycode;
	    return(map); /* we added it without stretching the map */
	}
    }

    /* stretch the map */
    if ((newmap = XNewModifiermap(map->max_keypermod+1)) == NULL)
	return (XModifierKeymap *) NULL;
    newrow = row = 0;
    lastrow = newmap->max_keypermod * 8;
    while (newrow < lastrow) {
	for (i=0; i<map->max_keypermod; i++)
	    newmap->modifiermap[ newrow+i ] = map->modifiermap[ row+i ];
	newmap->modifiermap[ newrow+i ] = 0;
	row += map->max_keypermod;
	newrow += newmap->max_keypermod;
    }
    (void) XFreeModifiermap(map);
    newrow = newmap->max_keypermod * modifier + newmap->max_keypermod - 1;
    newmap->modifiermap[ newrow ] = keycode;
    return(newmap);
}

XModifierKeymap *
XDeleteModifiermapEntry(XModifierKeymap *map,
#if NeedWidePrototypes
			unsigned int keycode,
#else
			KeyCode keycode,
#endif
			int modifier)
{
    int i,
	row = modifier * map->max_keypermod;

    for (i=0; i<map->max_keypermod; i++) {
        if (map->modifiermap[ row+i ] == keycode)
            map->modifiermap[ row+i ] = 0;
    }
    /* should we shrink the map?? */
    return (map);
}
/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern const char *ProgramName;
extern Display *dpy;
extern int min_keycode, max_keycode;
extern Bool verbose;
extern Bool dontExecute;
extern const char *inputFilename;
extern int lineno;
extern int parse_errors;

extern void initialize_map(void);
extern void process_file(const char *filename);
extern void process_line(const char *buffer);
extern void handle_line(char *line, int len);
extern void print_work_queue(void);
extern int execute_work_queue(void);
extern void print_modifier_map(void);
extern void print_key_table(Bool exprs);
extern void print_pointer_map(void);

extern int UpdateModifierMapping(XModifierKeymap *map);
extern int AddModifier(XModifierKeymap **mapp, KeyCode keycode, int modifier);
extern int RemoveModifier(XModifierKeymap **mapp, KeyCode keycode, 
			  int modifier);
extern int ClearModifier(XModifierKeymap **mapp, int modifier);
extern void PrintModifierMapping(XModifierKeymap *map, FILE *fp);
extern void PrintKeyTable(Bool exprs, FILE *fp);
extern void PrintPointerMap(FILE *fp);
extern int SetPointerMap(unsigned char *map, int n);

extern void _X_NORETURN Exit(int status);

const char *ProgramName;
Display *dpy = NULL;
int min_keycode, max_keycode;
Bool verbose = False;
Bool dontExecute = False;

/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#ifndef _WQ_H
#define _WQ_H

/* 
 * Input is parsed and a work queue is built that is executed later.  This
 * allows us to swap keys as well as ensure that we don't mess up the keyboard
 * by doing a partial rebind.
 */

enum opcode { doKeycode, doAddModifier, doRemoveModifier, doClearModifier,
	      doPointer };

struct op_generic {
    enum opcode type;			/* oneof enum opcode */
    union op *next;			/* next element in list or NULL */
};


/*
 * keycode KEYCODE = KEYSYM
 * keysym OLDKEYSYM = NEWKEYSYM
 *
 * want to eval the OLDKEYSYM before executing the work list so that it isn't
 * effected by any assignments.
 */

struct op_keycode {
    enum opcode type;			/* doKeycode */
    union op *next;			/* next element in list or NULL */
    KeyCode target_keycode;		/* key to which we are assigning */
    int count;				/* number of new keysyms */
    KeySym *keysyms;			/* new values to insert */
};


/*
 * add MODIFIER = KEYSYM ...
 */

struct op_addmodifier {
    enum opcode type;			/* doAddModifier */
    union op *next;			/* next element in list or NULL */
    int modifier;			/* index into modifier list */
    int count;				/* number of keysyms */
    KeySym *keysyms;			/* new values to insert */
};


/*
 * remove MODIFIER = OLDKEYSYM ...
 *
 * want to eval the OLDKEYSYM before executing the work list so that it isn't
 * effected by any assignments.
 */

struct op_removemodifier {
    enum opcode type;			/* doRemoveModifier */
    union op *next;			/* next element in list or NULL */
    int modifier;			/* index into modifier list */
    int count;				/* number of keysyms */
    KeyCode *keycodes;			/* old values to remove */
};


/*
 * clear MODIFIER
 */

struct op_clearmodifier {
    enum opcode type;			/* doClearModifier */
    union op *next;			/* next element in list or NULL */
    int modifier;			/* index into modifier list */
};

/*
 * pointer = NUMBER ...
 *
 * set pointer map to the positive numbers given on the right hand side
 */

#define MAXBUTTONCODES 256		/* there are eight bits of buttons */

struct op_pointer {
    enum opcode type;			/* doPointer */
    union op *next;			/* next element in list or NULL */
    int count;				/* number of new button codes */
    unsigned char button_codes[MAXBUTTONCODES];
};


/*
 * all together now
 */
union op {
    struct op_generic generic;
    struct op_keycode keycode;
    struct op_addmodifier addmodifier;
    struct op_removemodifier removemodifier;
    struct op_clearmodifier clearmodifier;
    struct op_pointer pointer;
};

extern struct wq {
    union op *head;
    union op *tail;
} work_queue;


extern struct modtab {
    const char *name;
    int length;
    int value;
} modifier_table[];

#define AllocStruct(s) (malloc (sizeof (s)))

#define MAXKEYSYMNAMESIZE 80		/* absurdly large */

#endif

/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

/*
 * Copyright (c) 1987, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Author:  Jim Fulton, MIT X Consortium; derived from parts of the
 * original xmodmap, written by David Rosenthal, of Sun Microsystems.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef WIN32
#include <X11/Xwindows.h>
#endif

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <stdio.h>

static void
mapping_busy_key(int timeout)
{
    int i;
    unsigned char keymap[32];
    static unsigned int masktable[8] = {
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

    XQueryKeymap (dpy, (char *) keymap);

    fprintf (stderr,
	     "%s:  please release the following keys within %d seconds:\n",
	     ProgramName, timeout);
    for (i = 0; i < 256; i++) {
	if (keymap[i >> 3] & masktable[i & 7]) {
	    KeySym ks = XKeycodeToKeysym (dpy, (KeyCode) i, 0);
	    char *cp = XKeysymToString (ks);
	    fprintf (stderr, "    %s (keysym 0x%x, keycode %d)\n",
		     cp ? cp : "UNNAMED", (unsigned int)ks, i);
	}
    }
    sleep (timeout);
    return;
}

static void
mapping_busy_pointer(int timeout)
{
    int i;
    Window root, child;			/* dummy variables */
    int rx, ry, wx, wy;			/* dummy variables */
    unsigned int mask;
    static unsigned int masks[5] = {
	Button1Mask, Button2Mask, Button3Mask, Button4Mask, Button5Mask };

    if (!XQueryPointer (dpy, RootWindow(dpy,DefaultScreen(dpy)),
			&root, &child, &rx, &ry, &wx, &wy, &mask))
      mask = 0;

    fprintf (stderr,
	     "%s:  please release the following buttons within %d seconds:\n",
	     ProgramName, timeout);
    for (i = 0; i < 5; i++) {
	if (mask & masks[i]) 
	  fprintf (stderr, "    Button%d\n", i+1);
    }
    sleep (timeout);
    return;
}


/*
 * UpdateModifierMapping - this sends the modifier map to the server
 * and deals with retransmissions due to the keyboard being busy.
 */

int 
UpdateModifierMapping(XModifierKeymap *map)
{
    int retries, timeout;

    for (retries = 5, timeout = 2; retries > 0; retries--, timeout *= 2) {
	int result;

	result = XSetModifierMapping (dpy, map);
	switch (result) {
	  case MappingSuccess:	/* Success */
	    return (0);
	  case MappingBusy:		/* Busy */
	    mapping_busy_key (timeout);
	    continue;
	  case MappingFailed:
	    fprintf (stderr, "%s: bad set modifier mapping.\n",
		     ProgramName);
	    return (-1);
	  default:
	    fprintf (stderr, "%s:  bad return %d from XSetModifierMapping\n",
		     ProgramName, result);
	    return (-1);
	}
    }
    fprintf (stderr,
	     "%s:  unable to set modifier mapping, keyboard problem\n",
	     ProgramName);
    return (-1);
}


/*
 * AddModifier - this adds a keycode to the modifier list
 */

int 
AddModifier(XModifierKeymap **mapp, KeyCode keycode, int modifier)
{
    if (keycode) {
	*mapp = XInsertModifiermapEntry (*mapp, keycode, modifier);
	return (0);
    } else {
	return (-1);
    }
    /*NOTREACHED*/
}


/*
 * DeleteModifier - this removes a keycode from the modifier list
 */

int 
RemoveModifier(XModifierKeymap **mapp, KeyCode keycode, int modifier)
{
    if (keycode) {
	*mapp = XDeleteModifiermapEntry (*mapp, keycode, modifier);
	return (0);
    } else {
	return (-1);
    }
    /*NOTREACHED*/
}


/*
 * ClearModifier - this removes all entries from the modifier list
 */

int 
ClearModifier(XModifierKeymap **mapp, int modifier)
{
    int i;
    XModifierKeymap *map = *mapp;
    KeyCode *kcp;

    kcp = &map->modifiermap[modifier * map->max_keypermod];
    for (i = 0; i < map->max_keypermod; i++) {
	*kcp++ = (KeyCode) 0;
    }
    return (0);
}

static int
GetKeysymsPerKeycode(void)
{
    int min_keycode, max_keycode, keysyms_per_keycode = 0;
    KeySym *m;

    XDisplayKeycodes(dpy, &min_keycode, &max_keycode);
    m = XGetKeyboardMapping(dpy, min_keycode, (max_keycode - min_keycode + 1),
                            &keysyms_per_keycode);
    XFree(m);
    return keysyms_per_keycode;
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

void
PrintKeyTable(Bool exprs, FILE *fp)
{
    int         i;
    int min_keycode, max_keycode, keysyms_per_keycode;
    KeySym *keymap, *origkeymap;

    XDisplayKeycodes (dpy, &min_keycode, &max_keycode);
    origkeymap = XGetKeyboardMapping (dpy, min_keycode,
				      (max_keycode - min_keycode + 1),
				      &keysyms_per_keycode);

    if (!origkeymap) {
	fprintf (stderr, "%s:  unable to get keyboard mapping table.\n",
		 ProgramName);
	return;
    }
    if (!exprs) {
	fprintf (fp, 
		 "There are %d KeySyms per KeyCode; KeyCodes range from %d to %d.\n\n", 
		 keysyms_per_keycode, min_keycode, max_keycode);
	fprintf (fp, "    KeyCode\tKeysym (Keysym)\t...\n");
	fprintf (fp, "    Value  \tValue   (Name) \t...\n\n");
    }
    keymap = origkeymap;
    for (i = min_keycode; i <= max_keycode; i++) {
	int  j, max;

	if (exprs)
	    fprintf(fp, "keycode %3d =", i);
	else
	    fprintf(fp, "    %3d    \t", i);
	max = keysyms_per_keycode - 1;
	while ((max >= 0) && (keymap[max] == NoSymbol))
	    max--;
	for (j = 0; j <= max; j++) {
	    register KeySym ks = keymap[j];
	    const char *s;
	    if (ks != NoSymbol)
		s = XKeysymToString (ks);
	    else
		s = "NoSymbol";
	    if (!exprs)
		fprintf (fp, "0x%04x (%s)\t", 
			 (unsigned int)ks, s ? s : "no name");
	    else if (s)
		fprintf (fp, " %s", s);
	    else
		fprintf (fp, " 0x%04x", (unsigned int)ks);
	}
	keymap += keysyms_per_keycode;
	fprintf (fp, "\n");
    }

    XFree ((char *) origkeymap);
    return;
}

void
PrintPointerMap(FILE *fp)
{
    unsigned char pmap[256];		/* there are 8 bits of buttons */
    int count, i;

    count = XGetPointerMapping (dpy, pmap, 256);

    fprintf (fp, "There are %d pointer buttons defined.\n\n", count);
    fprintf (fp, "    Physical        Button\n");
    fprintf (fp, "     Button          Code\n");
/*               "      ###            ###\n"               */
    for (i = 0; i < count; i++) {
	fprintf (fp, "      %3u            %3u\n", 
		 i+1, (unsigned int) pmap[i]);
    }
    fprintf (fp, "\n");
    return;
}


/*
 * SetPointerMap - set the pointer map
 */

int 
SetPointerMap(unsigned char *map, int n)
{
    unsigned char defmap[MAXBUTTONCODES];
    int j;
    int retries, timeout;

    if (n == 0) {				/* reset to default */
	n = XGetPointerMapping (dpy, defmap, MAXBUTTONCODES);
	for (j = 0; j < n; j++) defmap[j] = (unsigned char) (j + 1);
	map = defmap;
    }

    for (retries = 5, timeout = 2; retries > 0; retries--, timeout *= 2) {
	int result;

	switch (result = XSetPointerMapping (dpy, map, n)) {
	  case MappingSuccess:
	    return 0;
	  case MappingBusy:
	    mapping_busy_pointer (timeout);
	    continue;
	  case MappingFailed:
	    fprintf (stderr, "%s:  bad pointer mapping\n", ProgramName);
	    return -1;
	  default:
	    fprintf (stderr, "%s:  bad return %d from XSetPointerMapping\n",
		     ProgramName, result);
	    return -1;
	}
    }
    fprintf (stderr, "%s:  unable to set pointer mapping\n", ProgramName);
    return -1;
}

/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef HAVE_STRNCASECMP
#include <strings.h>
#endif

static XModifierKeymap *map = NULL;


/*
 * The routines in this file manipulate a queue of intructions.  Instead of
 * executing each line as it is entered, we build up a list of actions to 
 * take and execute them all at the end.  This allows us to find all errors
 * at once, and to preserve the context in which we are looking up keysyms.
 */

struct wq work_queue = {NULL, NULL};


/*
 * common utility routines
 */

/*
 * This is a combination of reallocf() and reallocarray().
 * If the realloc fails, it frees the old pointer so it doesn't leak.
 */
static void *
reallocfarray(void *old, size_t num, size_t size)
{
    static void *new;

    if (size > 0 && num > (SIZE_MAX / size)) /* overflow would happen */
        new = NULL;
    else
        new = realloc(old, num * size);

    if (new == NULL)
        free(old);

    return new;
}

static KeyCode *
KeysymToKeycodes(Display *dpy, KeySym keysym, int *pnum_kcs)
{
    KeyCode *kcs = NULL;
    int i, j;

    *pnum_kcs = 0;
    for (i = min_keycode; i <= max_keycode; i++) {
	for (j = 0; j < 8; j++) {
	    if (XKeycodeToKeysym(dpy, (KeyCode) i, j) == keysym) {
		if (!kcs)
		    kcs = malloc(sizeof(KeyCode));
		else
		    kcs = reallocfarray(kcs, (*pnum_kcs + 1), sizeof(KeyCode));
		if (!kcs) {
		    fprintf(stderr, "attempt to allocate %ld byte keycode set",
			    (long) ((*pnum_kcs + 1) * sizeof (KeyCode)));
		    return NULL;
		}
		kcs[*pnum_kcs] = i;
		*pnum_kcs += 1;
		break;
	    }
	}
    }
    return kcs;
}

static char *
copy_to_scratch(const char *s, int len)
{
    static char *buf = NULL;
    static int buflen = 0;

    if (len < 0)
        len = 0;

    if (len >= buflen) {
	if (buf) free (buf);
	buflen = (len < 40) ? 80 : (len * 2);
	buf = malloc (buflen+1);
	if (!buf) {
	    fprintf (stderr, "attempt to allocate %d byte scratch buffer\n", buflen + 1);
	    return NULL;
	}
    }

    strncpy (buf, s, len);
    buf[len] = '\0';

    return (buf);
}

static void
badheader(void)
{
    fprintf (stderr, "%s:  %s:%d:  bad ", ProgramName, inputFilename, lineno+1);
    parse_errors++;
}

#define badmsg0(what) { badheader(); fprintf (stderr, what); \
			   putc ('\n', stderr); }

#define badmsg(what,arg) { badheader(); fprintf (stderr, what, arg); \
			   putc ('\n', stderr); }

#define badmsgn(what,s,len) badmsg (what, copy_to_scratch (s, len))

void 
initialize_map (void)
{
    map = XGetModifierMapping (dpy);
    return;
}

static void do_keycode ( char *line, int len );
static void do_keysym ( char *line, int len );
static void finish_keycodes ( const char *line, int len, KeyCode *keycodes, 
			      int count );
static void do_add ( char *line, int len );
static void do_remove ( char *line, int len );
static void do_clear ( char *line, int len );
static void do_pointer ( char *line, int len );
static int get_keysym_list ( const char *line, int len, int *np, KeySym **kslistp );

static void print_opcode(union op *op);

static int skip_word ( const char *s, int len );
static int skip_chars ( const char *s, int len );
static int skip_space ( const char *s, int len );

static struct dt {
    const char *command;		/* name of input command */
    int length;				/* length of command */
    void (*proc)(char *, int);		/* handler */
} dispatch_table[] = {
    { "keycode", 7, do_keycode },
    { "keysym", 6, do_keysym },
    { "add", 3, do_add },
    { "remove", 6, do_remove },
    { "clear", 5, do_clear },
    { "pointer", 7, do_pointer },
    { NULL, 0, NULL }};

/*
 * handle_line - this routine parses the input line (which has had all leading
 * and trailing whitespace removed) and builds up the work queue.
 */

void 
handle_line(char *line,		/* string to parse */
	    int len)		/* length of line */
{
    int n;
    struct dt *dtp;

    n = skip_chars (line, len);
    if (n < 0) {
	badmsg ("input line '%s'", line);
	return;
    }

    for (dtp = dispatch_table; dtp->command != NULL; dtp++) {
	if (n == dtp->length &&
	    strncmp (line, dtp->command, dtp->length) == 0) {

	    n += skip_space (line+n, len-n);
	    line += n, len -= n;

	    (*(dtp->proc)) (line, len);
	    return;
	}
    }

    fprintf (stderr, "%s:  unknown command on line %s:%d\n",
	     ProgramName, inputFilename, lineno+1);
    parse_errors++;
}

/*
 * the following routines are useful for parsing
 */ 

static int 
skip_word (const char *s, int len)
{
    register int n;

    n = skip_chars (s, len);
    return (n + skip_space (s+n, len-n));
}

static int 
skip_chars(const char *s, int len)
{
    register int i;

    if (len <= 0 || !s || *s == '\0') return (0);

    for (i = 0; i < len; i++) {
	if (isspace(s[i])) break;
    }
    return (i);
}

static int 
skip_space(const char *s, int len)
{
    register int i;

    if (len <= 0 || !s || *s == '\0') return (0);

    for (i = 0; i < len; i++) {
	if (!s[i] || !isspace(s[i])) break;
    }
    return (i);
}


static int 
skip_until_char(const char *s, int len, char c)
{
    register int i;

    for (i = 0; i < len; i++) {
	if (s[i] == c) break;
    }
    return (i);
}


/*
 * The action routines.
 *
 * This is where the real work gets done.  Each routine is responsible for
 * parsing its input (note that the command keyword has been stripped off)
 * and adding to the work queue.  They are also in charge of outputting
 * error messages and returning non-zero if there is a problem.
 *
 * The following global variables are available:
 *     dpy                the display descriptor
 *     work_queue         linked list of opcodes
 *     inputFilename      name of the file being processed
 *     lineno             line number of current line in input file
 */
static void
add_to_work_queue(union op *p)	/* this can become a macro someday */
{
    if (work_queue.head == NULL) {	/* nothing on the list */
	work_queue.head = work_queue.tail = p;	/* head, tail, no prev */
    } else {
	work_queue.tail->generic.next = p;  /* head okay, prev */
	work_queue.tail = p;		/* tail */
    }
    p->generic.next = NULL;

    if (verbose) {
	print_opcode (p);
    }
    return;
}

static Bool 
parse_number(const char *str, unsigned long *val)
{
    const char *fmt = "%ld";

    if (*str == '0') {
	str++;
	while (isspace(*str))
	    str++;
	fmt = "%lo";
	if (*str == '\0') {
	    *val = 0;
	    return 1;
	}
	if (*str == 'x' || *str == 'X') {
	    str++;
	    fmt = "%lx";
	}
    }
    return (sscanf (str, fmt, val) == 1);
}

static Bool 
parse_keysym(const char *line, int n, char **name, KeySym *keysym)
{
    *name = copy_to_scratch (line, n);
    if (!strcmp(*name, "NoSymbol")) {
	*keysym = NoSymbol;
	return (True);
    }
    *keysym = XStringToKeysym (*name);
    if (*keysym == NoSymbol && '0' <= **name && **name <= '9')
	return parse_number(*name, keysym);
    return (*keysym != NoSymbol);
}

/*
 * do_keycode - parse off lines of the form
 *
 *                 "keycode" number "=" [keysym ...]
 *                           ^
 *
 * where number is in decimal, hex, or octal.  Any number of keysyms may be
 * listed.
 */

static void 
do_keycode(char *line, int len)
{
    int dummy;
    const char *fmt = "%d";
    KeyCode keycode;

    if (len < 3 || !line || *line == '\0') {  /* 5=a minimum */
	badmsg0 ("keycode input line");
	return;
    }

    /*
     * We need not bother to advance line/len past the
     * number (or the string 'any') as finish_keycodes() will
     * first advance past the '='.
     */
    if (!strncmp("any", line, 3)) {
	keycode = 0;
    } else {
	if (*line == '0') line++, len--, fmt = "%o";
	if (*line == 'x' || *line == 'X') line++, len--, fmt = "%x";

	dummy = 0;
	if (sscanf (line, fmt, &dummy) != 1 || dummy == 0) {
	    badmsg0 ("keycode value");
	    return;
	}
	keycode = (KeyCode) dummy;
	if ((int)keycode < min_keycode || (int)keycode > max_keycode) {
	    badmsg0 ("keycode value (out of range)");
	    return;
	}
    }

    finish_keycodes (line, len, &keycode, 1);
}


/*
 * do_keysym - parse off lines of the form
 *
 *                 "keysym" keysym "=" [keysym ...]
 *                          ^
 *
 * The left keysyms has to be checked for validity and evaluated.
 */

static void 
do_keysym(char *line, int len)
{
    int n;
    KeyCode *keycodes;
    KeySym keysym;
    char *tmpname;

    if (len < 3 || !line || *line == '\0') {  /* a=b minimum */
	badmsg0 ("keysym input line");
	return;
    }

    n = skip_chars (line, len);
    if (n < 1) {
	badmsg0 ("target keysym name");
	return;
    }
    if (!parse_keysym(line, n, &tmpname, &keysym)) {
	badmsg ("keysym target key symbol '%s'", tmpname);
	return;
    }

    keycodes = KeysymToKeycodes (dpy, keysym, &n);
    if (n == 0) {
	badmsg ("keysym target keysym '%s', no corresponding keycodes",
		tmpname);
	return;
    }
    if (verbose) {
	int i;
	printf ("! Keysym %s (0x%lx) corresponds to keycode(s)",
		tmpname, (long) keysym);
	for (i = 0; i < n; i++)
	    printf (" 0x%x", keycodes[i]);
	printf("\n");
    }

    finish_keycodes (line, len, keycodes, n);
}

static void 
finish_keycodes(const char *line, int len, KeyCode *keycodes, int count)
{
    int n;
    KeySym *kslist;
    union op *uop;
    struct op_keycode *opk;
   
    n = skip_until_char (line, len, '=');
    line += n, len -= n;
    
    if (len < 1 || *line != '=') {	/* = minimum */
	badmsg0 ("keycode command (missing keysym list),");
	return;
    }
    line++, len--;			/* skip past the = */

    n = skip_space (line, len);
    line += n, len -= n;

    /* allow empty list */
    if (get_keysym_list (line, len, &n, &kslist) < 0)
	return;

    while (--count >= 0) {
	uop = AllocStruct (union op);
	if (!uop) {
	    badmsg ("attempt to allocate a %ld byte keycode opcode",
		    (long) sizeof (struct op_keycode));
	    return;
	}
	opk = &uop->keycode;

	opk->type = doKeycode;
	opk->target_keycode = keycodes[count];
	opk->count = n;
	opk->keysyms = kslist;

	add_to_work_queue (uop);
    }

#ifdef later
    /* make sure we handle any special keys */
    check_special_keys (keycode, n, kslist);
#endif
}


/*
 * parse_modifier - convert a modifier string name to its index
 */

struct modtab modifier_table[] = {	/* keep in order so it can be index */
    { "shift", 5, 0 },
    { "lock", 4, 1 },
    { "control", 7, 2 },
    { "mod1", 4, 3 },
    { "mod2", 4, 4 },
    { "mod3", 4, 5 },
    { "mod4", 4, 6 },
    { "mod5", 4, 7 },
    { "ctrl", 4, 2 },
    { NULL, 0, 0 }};

static int 
parse_modifier(char *line, int n)
{
    register int i;
    struct modtab *mt;

    /* lowercase for comparison against table */
    for (i = 0; i < n; i++) {
	if (isupper (line[i])) line[i] = tolower (line[i]);
    }

    for (mt = modifier_table; mt->name; mt++) {
	if (n == mt->length && strncmp (line, mt->name, n) == 0)
	  return (mt->value);
    }
    return (-1);
}


/*
 * do_add - parse off lines of the form
 *
 *                 add MODIFIER = keysym ...
 *                     ^
 * where the MODIFIER is one of Shift, Lock, Control, Mod[1-5] where case
 * is not important.  There should also be an alias Ctrl for control.
 */

static void 
do_add(char *line, int len)
{
    int n;
    int modifier;
    KeySym *kslist;
    union op *uop;
    struct op_addmodifier *opam;

    if (len < 6 || !line || *line == '\0') {  /* Lock=a minimum */
	badmsg0 ("add modifier input line");
	return;
    }

    n = skip_chars (line, len);
    if (n < 1) {
	badmsg ("add modifier name %s", line);
	return;
    }

    modifier = parse_modifier (line, n);
    if (modifier < 0) {
	badmsgn ("add modifier name '%s', not allowed", line, n);
	return;
    }

    line += n, len -= n;
    n = skip_until_char (line, len, '=');
    if (n < 0) {
	badmsg0 ("add modifier = keysym");
	return;
    }

    n++;				/* skip = */
    n += skip_space (line+n, len-n);
    line += n, len -= n;

    if (get_keysym_list (line, len, &n, &kslist) < 0)
	return;
    if (n == 0) {
	badmsg0 ("add modifier keysym list (empty)");
	return;
    }

    uop = AllocStruct (union op);
    if (!uop) {
	badmsg ("attempt to allocate %ld byte addmodifier opcode",
		(long) sizeof (struct op_addmodifier));
	return;
    }
    opam = &uop->addmodifier;

    opam->type = doAddModifier;
    opam->modifier = modifier;
    opam->count = n;
    opam->keysyms = kslist;

    add_to_work_queue (uop);
}

#ifdef AUTO_ADD_REMOVE
/*
 * make_add - stick a single add onto the queue
 */
static void 
make_add(int modifier, KeySym keysym)
{
    union op *uop;
    struct op_addmodifier *opam;

    uop = AllocStruct (union op);
    if (!uop) {
	badmsg ("attempt to allocate %ld byte addmodifier opcode",
		(long) sizeof (struct op_addmodifier));
	return;
    }
    opam = &uop->addmodifier;

    opam->type = doAddModifier;
    opam->modifier = modifier;
    opam->count = 1;
    opam->keysyms = malloc (sizeof (KeySym));
    if (!opam->keysyms) {
	badmsg ("attempt to allocate %ld byte KeySym", (long) sizeof (KeySym));
	free (opam);
	return;
    }
    opam->keysyms[0] = keysym;

    add_to_work_queue (uop);
    return;
}
#endif /* AUTO_ADD_REMOVE */


/*
 * do_remove - parse off lines of the form
 *
 *                 remove MODIFIER = oldkeysym ...
 *                        ^
 * where the MODIFIER is one of Shift, Lock, Control, Mod[1-5] where case
 * is not important.  There should also be an alias Ctrl for control.
 */

static void 
do_remove(char *line, int len)
{
    int n;
    int nc;
    int i;
    int tot;
    int modifier;
    KeySym *kslist;
    KeyCode *kclist;
    union op *uop;
    struct op_removemodifier *oprm;

    if (len < 6 || !line || *line == '\0') {  /* Lock=a minimum */
	badmsg0 ("remove modifier input line");
	return;
    }

    n = skip_chars (line, len);
    if (n < 1) {
	badmsg ("remove modifier name %s", line);
	return;
    }

    modifier = parse_modifier (line, n);
    if (modifier < 0) {
	badmsgn ("remove modifier name '%s', not allowed", line, n);
	return;
    }

    line += n, len -= n;
    n = skip_until_char (line, len, '=');
    if (n < 0) {
	badmsg0 ("remove modifier = keysym");
	return;
    }

    n++;
    n += skip_space (line+n, len-n);
    line += n, len -= n;

    if (get_keysym_list (line, len, &n, &kslist) < 0)
	return;
    if (n == 0) {
	badmsg0 ("remove modifier keysym list (empty)");
	return;
    }

    /*
     * unlike the add command, we have to now evaluate the keysyms
     */

    kclist = malloc (n * sizeof (KeyCode));
    if (!kclist) {
	badmsg ("attempt to allocate %ld byte keycode list",
		(long) (n * sizeof (KeyCode)));
	free (kslist);
	return;
    }

    tot = n;
    nc = 0;
    for (i = 0; i < n; i++) {
        int num_kcs;
	KeyCode *kcs;
	kcs = KeysymToKeycodes (dpy, kslist[i], &num_kcs);
	if (num_kcs == 0) {
	    char *tmpname = XKeysymToString (kslist[i]);
	    badmsg ("keysym in remove modifier list '%s', no corresponding keycodes",
		    tmpname ? tmpname : "?");
	    continue;
	}
	if (verbose) {
	    int j;
	    char *tmpname = XKeysymToString (kslist[i]);
	    printf ("! Keysym %s (0x%lx) corresponds to keycode(s)", 
		    tmpname ? tmpname : "?", (long) kslist[i]);
	    for (j = 0; j < num_kcs; j++)
		printf(" 0x%x", kcs[j]);
	    printf("\n");
	}
	if (nc + num_kcs > tot) {
	    tot = nc + num_kcs;
	    kclist = reallocfarray(kclist, tot, sizeof(KeyCode));
	    if (!kclist) {
		badmsg ("attempt to allocate %ld byte keycode list",
			(long) (tot * sizeof (KeyCode)));
		free (kslist);
		return;
	    }
	}
	while (--num_kcs >= 0)
	    kclist[nc++] = *kcs++;		/* okay, add it to list */
    }

    free (kslist);		/* all done with it */

    uop = AllocStruct (union op);
    if (!uop) {
	badmsg ("attempt to allocate %ld byte removemodifier opcode",
		(long) sizeof (struct op_removemodifier));
	free(kclist);
	return;
    }
    oprm = &uop->removemodifier;

    oprm->type = doRemoveModifier;
    oprm->modifier = modifier;
    oprm->count = nc;
    oprm->keycodes = kclist;

    add_to_work_queue (uop);
}

#ifdef AUTO_ADD_REMOVE
/*
 * make_remove - stick a single remove onto the queue
 */
static void 
make_remove(int modifier, KeyCode keycode)
{
    union op *uop;
    struct op_removemodifier *oprm;

    uop = AllocStruct (union op);
    if (!uop) {
	badmsg ("attempt to allocate %ld byte removemodifier opcode",
		(long) sizeof (struct op_removemodifier));
	return;
    }
    oprm = &uop->removemodifier;

    oprm->type = doRemoveModifier;
    oprm->modifier = modifier;
    oprm->count = 1;
    oprm->keycodes = malloc (sizeof (KeyCode));
    if (!oprm->keycodes) {
	badmsg ("attempt to allocate %ld byte KeyCode",
		(long) sizeof (KeyCode));
	free (oprm);
	return;
    }
    oprm->keycodes[0] = keycode;

    add_to_work_queue (uop);
    return;
}
#endif /* AUTO_ADD_REMOVE */


/*
 * do_clear - parse off lines of the form
 *
 *                 clear MODIFIER
 *                       ^
 */

static void 
do_clear(char *line, int len)
{
    int n;
    int modifier;
    union op *uop;
    struct op_clearmodifier *opcm;

    if (len < 4 || !line || *line == '\0') {  /* Lock minimum */
	badmsg0 ("clear modifier input line");
	return;
    }

    n = skip_chars (line, len);

    modifier = parse_modifier (line, n);
    if (modifier < 0) {
	badmsgn ("clear modifier name '%s'", line, n);
	return;
    }
    n += skip_space (line+n, len-n);
    if (n != len) {
	badmsgn ("extra argument '%s' to clear modifier", line+n, len-n);
	/* okay to continue */
    }

    uop = AllocStruct (union op);
    if (!uop) {
	badmsg ("attempt to allocate %ld byte clearmodifier opcode",
		(long) sizeof (struct op_clearmodifier));
	return;
    }
    opcm = &uop->clearmodifier;

    opcm->type = doClearModifier;
    opcm->modifier = modifier;

    add_to_work_queue (uop);
}

/*
 * do_pointer = get list of numbers of the form
 *
 *                 buttons = NUMBER ...
 *                         ^
 */

static void 
do_pointer(char *line, int len)
{
    int n;
    int i;
    unsigned long val;
    union op *uop;
    struct op_pointer *opp;
    unsigned char buttons[MAXBUTTONCODES];
    int nbuttons;
    char *strval;
    Bool ok;

    if (len < 2 || !line || *line == '\0') {  /* =1 minimum */
	badmsg0 ("buttons input line");
	return;
    }

    nbuttons = XGetPointerMapping (dpy, buttons, MAXBUTTONCODES);

    n = skip_space (line, len);
    line += n, len -= n;

    if (line[0] != '=') {
	badmsg0 ("buttons pointer code list, missing equal sign");
	return;
    }

    line++, len--;			/* skip = */
    n = skip_space (line, len);
    line += n, len -= n;

    i = 0;
    if (len < 7 || strncasecmp (line, "default", 7) != 0) {
	while (len > 0) {
	    n = skip_space (line, len);
	    line += n, len -= n;
	    if (line[0] == '\0') break;
	    n = skip_word (line, len);
	    if (n < 1) {
		badmsg ("skip of word in buttons line:  %s", line);
		return;
	    }
	    strval = copy_to_scratch(line, n);
	    if (strval == NULL)
		/* copy_to_scratch already printed error message */
		return;
	    ok = parse_number (strval, &val);
	    if (!ok || val >= MAXBUTTONCODES) {
		badmsg ("value %s given for buttons list", strval);
		return;
	    }
	    buttons[i++] = (unsigned char) val;
	    line += n, len -= n;
	}
    }
    
    if (i > 0 && i != nbuttons) {
	if (i < nbuttons) {
	    fprintf (stderr, 
		     "Warning: Only changing the first %d of %d buttons.\n",
		     i, nbuttons);
	}
	else {  /* i > nbuttons */ 
	    fprintf (stderr, 
		     "Warning: Not changing %d extra buttons beyond %d.\n",
		     i - nbuttons, nbuttons);
	}
	i = nbuttons;
    }

    uop = AllocStruct (union op);
    if (!uop) {
	badmsg ("attempt to allocate a %ld byte pointer opcode",
		(long) sizeof (struct op_pointer));
	return;
    }
    opp = &uop->pointer;

    opp->type = doPointer;
    opp->count = i;
    for (i = 0; i < opp->count; i++) {
	opp->button_codes[i] = buttons[i];
    }

    add_to_work_queue (uop);
}


/*
 * get_keysym_list - parses the rest of the line into a keysyms assumes
 * that the = sign has been parsed off but there may be leading whitespace
 *
 *                 keysym ...
 *                 ^
 *
 * this involves getting the word containing the keysym, checking its range,
 * and adding it to the list.
 */

static int 
get_keysym_list(const char *line, int len, int *np, KeySym **kslistp)
{
    int havesofar, maxcanhave;
    KeySym *keysymlist;

    *np = 0;
    *kslistp = NULL;

    if (len == 0) return (0);		/* empty list */

    havesofar = 0;
    maxcanhave = 4;			/* most lists are small */
    keysymlist = malloc (maxcanhave * sizeof (KeySym));
    if (!keysymlist) {
	badmsg ("attempt to allocate %ld byte initial keysymlist",
		(long) (maxcanhave * sizeof (KeySym)));
	return (-1);
    }

    while (len > 0) {
	KeySym keysym;
	int n;
	char *tmpname;
	Bool ok;

	n = skip_space (line, len);
	line += n, len -= n;

	n = skip_chars (line, len);
	if (n < 0) {
	    badmsg0 ("keysym name list");
	    free(keysymlist);
	    return (-1);
	}

	ok = parse_keysym (line, n, &tmpname, &keysym);
	line += n, len -= n;
	if (!ok) {
	    badmsg ("keysym name '%s' in keysym list", tmpname);
	    /* do NOT return here, look for others */
	    continue;
	}

	/*
	 * Do NOT test to see if the keysym translates to a keycode or you
	 * won't be able to assign new ones....
	 */

	/* grow the list bigger if necessary */
	if (havesofar >= maxcanhave) {
	    maxcanhave *= 2;
	    keysymlist = reallocfarray(keysymlist, maxcanhave, sizeof(KeySym));
	    if (!keysymlist) {
		badmsg ("attempt to grow keysym list to %ld bytes",
			(long) (maxcanhave * sizeof (KeySym)));
		return (-1);
	    }
	}

	/* and add it to the list */
	keysymlist[havesofar++] = keysym;
    }

    *kslistp = keysymlist;
    *np = havesofar;
    return (0);
}


#ifdef later
/*
 * check_special_keys - run through list of keysyms and generate "add" or
 * "remove" commands for for any of the key syms that appear in the modifier
 * list.  this involves running down the modifier map which is an array of
 * 8 by map->max_keypermod keycodes.
 */

static void 
check_special_keys(KeyCode keycode, int n, KeySym *kslist)
{
    int i;				/* iterator variable */
    KeyCode *kcp;			/* keycode pointer */

    /*
     * walk the modifiermap array.  since its dimensions are not known at
     * compile time, we have to walk it by hand instead of indexing.  this
     * is why it is initialized outside the loop, but incremented inside the
     * second loop.
     */

    kcp = map->modifiermap;		/* start at beginning and iterate */
    for (i = 0; i < 8; i++) {		/* there are 8 modifier keys */
	int j;

	for (j = 0; j < map->max_keypermod; j++, kcp++) {
	    KeySym keysym;
	    int k;

	    if (!*kcp) continue;	/* only non-zero entries significant */

	    /*
	     * check to see if the target keycode is already a modifier; if so,
	     * then we have to remove it
	     */
	    if (keycode == *kcp) {
		make_remove (i, keycode);
	    }

	    /*
	     * now, check to see if any of the keysyms map to keycodes
	     * that are in the modifier list
	     */
	    for (k = 0; k < n; k++) {
		KeyCodes kc;

		kc = XKeysymToKeycode (dpy, kslist[k]);
		if (kc == *kcp) {	/* yup, found one */
		    /*
		     * have to generate a remove of the CURRENT keycode
		     * and then an add of the new KEYCODE
		     */
		    make_remove (i, kc);  /* modifier, keycode */
		    make_add (i, kslist[k]);  /* modifier, keysym */
		}
	    }
	}
    }
    return;
}
#endif

/*
 * print_work_queue - disassemble the work queue and print it on stdout
 */

void 
print_work_queue(void)
{
    union op *op;

    printf ("! dump of work queue\n");
    for (op = work_queue.head; op; op = op->generic.next) {
	print_opcode (op);
    }
    return;
}

static void 
print_opcode(union op *op)
{
    int i;

    printf ("        ");
    switch (op->generic.type) {
      case doKeycode:
	if (op->keycode.target_keycode)
	    printf ("keycode 0x%lx =", (long) op->keycode.target_keycode);
	else
	    printf ("keycode any =");
	for (i = 0; i < op->keycode.count; i++) {
	    char *name = XKeysymToString (op->keycode.keysyms[i]);

	    printf (" %s", name ? name : "BADKEYSYM");
	}
	printf ("\n");
	break;
      case doAddModifier:
	printf ("add %s =", modifier_table[op->addmodifier.modifier].name);
	for (i = 0; i < op->addmodifier.count; i++) {
	    char *name = XKeysymToString (op->addmodifier.keysyms[i]);
	    printf (" %s", name ? name : "BADKEYSYM");
	}
	printf ("\n");
	break;
      case doRemoveModifier:
	printf ("remove %s = ",
		modifier_table[op->removemodifier.modifier].name);
	for (i = 0; i < op->removemodifier.count; i++) {
	    printf (" 0x%lx", (long) op->removemodifier.keycodes[i]);
	}
	printf ("\n");
	break;
      case doClearModifier:
	printf ("clear %s\n", modifier_table[op->clearmodifier.modifier].name);
	break;
      case doPointer:
	printf ("pointer = ");
	if (op->pointer.count == 0)
	    printf(" default");
	else for (i=0; i < op->pointer.count; i++)
	    printf(" %d", op->pointer.button_codes[i]);
	printf ("\n");
	break;
      default:
	printf ("! unknown opcode %d\n", op->generic.type);
	break;
    }				/* end switch */
    return;
}

/*
 * execute_work_queue - do the real meat and potatoes now that we know what
 * we need to do and that all of the input is correct.
 */
static int exec_keycode ( struct op_keycode *opk );
static int exec_add ( struct op_addmodifier *opam );
static int exec_remove ( struct op_removemodifier *oprm );
static int exec_clear ( struct op_clearmodifier *opcm );
static int exec_pointer ( struct op_pointer *opp );


int 
execute_work_queue (void)
{
    union op *op;
    int errors;
    Bool update_map = False;
    int dosync;

    if (verbose) {
	printf ("!\n");
	printf ("! executing work queue\n");
	printf ("!\n");
    }

    errors = 0;
    dosync = 0;

    for (op = work_queue.head; op; op = op->generic.next) {
	if (verbose) print_opcode (op);

	/* check to see if we have to update the keyboard mapping */
	if (dosync &&
	    (dosync < 0 ||
	     op->generic.type != doKeycode ||
	     !op->keycode.target_keycode)) {
	    XSync (dpy, 0);
	    while (XEventsQueued (dpy, QueuedAlready) > 0) {
		XEvent event;
		XNextEvent (dpy, &event);
		if (event.type == MappingNotify) {
		    /* read all MappingNotify events */
		    while (XCheckTypedEvent (dpy, MappingNotify, &event)) ;
		    XRefreshKeyboardMapping (&event.xmapping);
		} else {
		    fprintf (stderr, "%s:  unknown event %ld\n", 
		    	     ProgramName, (long) event.type);
		}
	    }
	}
	dosync = 0;
	switch (op->generic.type) {
	  case doKeycode:
	    if (exec_keycode (&op->keycode) < 0) errors++;
	    if (op->keycode.target_keycode)
		dosync = 1;
	    else
		dosync = -1;
	    break;
	  case doAddModifier:
	    if (exec_add (&op->addmodifier) < 0) errors++;
	    else update_map = True;
	    break;
	  case doRemoveModifier:
	    if (exec_remove (&op->removemodifier) < 0) errors++;
	    else update_map = True;
	    break;
	  case doClearModifier:
	    if (exec_clear (&op->clearmodifier) < 0) errors++;
	    else update_map = True;
	    break;
	  case doPointer:
	    if (exec_pointer (&op->pointer) < 0) errors++;
	    break;
	  default:
	    fprintf (stderr, "%s:  unknown opcode %d\n", 
		     ProgramName, op->generic.type);
	    break;
	}
    }

    if (update_map) {
	if (UpdateModifierMapping (map) < 0) errors++;
    }

    return (errors > 0 ? -1 : 0);
}

static int 
exec_keycode(struct op_keycode *opk)
{
    if (!opk->target_keycode) {
	int i, j;
	KeyCode free;
	if (!opk->count)
	    return (0);
	free = 0;
	for (i = min_keycode; i <= max_keycode; i++) {
	    for (j = 0; j < opk->count; j++) {
		if (XKeycodeToKeysym(dpy, (KeyCode) i, j) != opk->keysyms[j])
		    break;
	    }
	    if (j >= opk->count)
		return (0);
	    if (free)
		continue;
	    for (j = 0; j < 8; j++) {
		if (XKeycodeToKeysym(dpy, (KeyCode) i, j) != None)
		    break;
	    }
	    if (j >= 8)
		free = i;
	}
	if (!free) {
	    fprintf(stderr, "%s: no available keycode for assignment\n",
		    ProgramName);
	    return (-1);
	}
	XChangeKeyboardMapping (dpy, free, opk->count, opk->keysyms, 1);
    } else if (opk->count == 0) {
	KeySym dummy = NoSymbol;
	XChangeKeyboardMapping (dpy, opk->target_keycode, 1,
				&dummy, 1);
    } else {
	XChangeKeyboardMapping (dpy, opk->target_keycode, opk->count, 
				opk->keysyms, 1);
    }
    return (0);
}

static int 
exec_add(struct op_addmodifier *opam)
{
    int i;
    int status;

    status = 0;
    for (i = 0; i < opam->count; i++) {
	int num_kcs;
	KeyCode *kcs;

	kcs = KeysymToKeycodes (dpy, opam->keysyms[i], &num_kcs);
	if (num_kcs == 0)
	    status = -1;
	while (--num_kcs >= 0) {
	    if (AddModifier (&map, *kcs++, opam->modifier) < 0)
		status = -1;
	}
    }
    return (status);
}

static int 
exec_remove(struct op_removemodifier *oprm)
{
    int i;
    int status;

    status = 0;
    for (i = 0; i < oprm->count; i++) {
	if (RemoveModifier (&map, oprm->keycodes[i], oprm->modifier) < 0)
	  status = -1;
    }
    return (status);
}

static int 
exec_clear(struct op_clearmodifier *opcm)
{
    return (ClearModifier (&map, opcm->modifier));
}


static int 
exec_pointer(struct op_pointer *opp)
{
    return (SetPointerMap (opp->button_codes, opp->count));
}

void 
print_modifier_map(void)
{
    PrintModifierMapping (map, stdout);
    return;
}

void 
print_key_table(Bool exprs)
{
    PrintKeyTable (exprs, stdout);
    return;
}

void 
print_pointer_map(void)
{
    PrintPointerMap (stdout);
    return;
}

/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define NOTINFILEFILENAME "commandline"
const char *inputFilename = NOTINFILEFILENAME;
int lineno = 0;

void process_file (const char *filename)	/* NULL means use stdin */
{
    FILE *fp;
    char buffer[BUFSIZ];

    /* open the file, eventually we'll want to pipe through cpp */

    if (!filename) {
	fp = stdin;
	inputFilename = "stdin"; 
    } else {
	fp = fopen (filename, "r");
	if (!fp) {
	    fprintf (stderr, "%s:  unable to open file '%s' for reading\n",
		     ProgramName, filename);
	    parse_errors++;
	    return;
	}
	inputFilename = filename;
    }


    /* read the input and filter */

    if (verbose) {
	printf ("! %s:\n", inputFilename);
    }

    for (lineno = 0; ; lineno++) {
	buffer[0] = '\0';
	if (fgets (buffer, BUFSIZ, fp) == NULL)
	  break;

	process_line (buffer);
    }

    inputFilename = NOTINFILEFILENAME;
    lineno = 0;
    (void) fclose (fp);
}


void process_line (const char *line)
{
    int len;
    int i;
    char *cp, *buffer;

    /* copy line to buffer since it may point to unwritable data */
    len = strlen(line);
    cp = buffer = strdup(line);
    if (buffer == NULL) {
	fprintf(stderr, "%s: Could not allocate %d bytes\n", ProgramName, len);
	Exit(-1);
    }
    
    for (i = 0; i < len; i++) {		/* look for blank lines */
	register char c = buffer[i];
	if (!(isspace(c) || c == '\n')) break;
    }
    if (i == len) goto done;

    cp = &buffer[i];

    if (*cp == '!') goto done;		/* look for comments */
    len -= (cp - buffer);		/* adjust len by how much we skipped */

					/* pipe through cpp */

					/* strip trailing space */
    for (i = len-1; i >= 0; i--) {
	register char c = cp[i];
	if (!(isspace(c) || c == '\n')) break;
    }
    if (i >= 0) cp[len = (i+1)] = '\0';  /* nul terminate */

    if (verbose) {
	printf ("! %d:  %s\n", lineno+1, cp);
    }

    /* handle input */
    handle_line (cp, len);

  done:
    free(buffer);
}

void
_X_NORETURN
Exit(int status)
{
    if (dpy) {
	XCloseDisplay (dpy);
	dpy = NULL;
    }
    exit (status);
}

static void _X_NORETURN
FatalError(const char *message)
{
    fprintf(stderr, "%s: %s\n", ProgramName, message);
    Exit(-1);
}

#ifndef HAVE_ASPRINTF
/* sprintf variant found in newer libc's which allocates string to print to */
static int _X_ATTRIBUTE_PRINTF(2,3)
asprintf(char ** ret, const char *format, ...)
{
    char buf[256];
    int len;
    va_list ap;

    va_start(ap, format);
    len = vsnprintf(buf, sizeof(buf), format, ap);
    va_end(ap);

    if (len < 0)
	return -1;

    if (len < sizeof(buf))
    {
	*ret = strdup(buf);
    }
    else
    {
	*ret = malloc(len + 1); /* snprintf doesn't count trailing '\0' */
	if (*ret != NULL)
	{
	    va_start(ap, format);
	    len = vsnprintf(*ret, len + 1, format, ap);
	    va_end(ap);
	    if (len < 0) {
		free(*ret);
		*ret = NULL;
	    }
	}
    }

    if (*ret == NULL)
	return -1;

    return len;
}
#endif /* HAVE_ASPRINTF */

static const char help_message[] = 
"\nwhere options include:\n"
"    -display host:dpy            X server to use\n"
"    -verbose, -quiet             turn logging on or off\n"
"    -n                           don't execute changes, just show like make\n"
"    -e expression                execute string\n"
"    -pm                          print modifier map\n"
"    -pk                          print keymap table\n"
"    -pke                         print keymap table as expressions\n"
"    -pp                          print pointer map\n"
"    -help                        print this usage message\n"
"    -grammar                     print out short help on allowable input\n"
"    -version                     print program version\n"
"    -                            read standard input\n"
"\n";


static void
_X_NORETURN _X_COLD
usage(int exitcode)
{
    fprintf (stderr, "usage:  %s [-options ...] [filename]\n", ProgramName);
    fprintf (stderr, "%s\n", help_message);
    Exit (exitcode);
}

static void
_X_NORETURN _X_COLD
missing_arg(const char *arg)
{
    fprintf (stderr, "%s: %s requires an argument\n\n", ProgramName, arg);
    usage(1);
}

static void
_X_NORETURN _X_COLD
unknown_arg(const char *arg)
{
    fprintf (stderr, "%s: unrecognized argument %s\n\n", ProgramName, arg);
    usage(1);
}

static const char grammar_message[] = 
"    pointer = default              reset pointer buttons to default\n"
"    pointer = NUMBER ...           set pointer button codes\n"
"    keycode NUMBER = [KEYSYM ...]  map keycode to given keysyms\n"
"    keysym KEYSYM = [KEYSYM ...]   look up keysym and do a keycode operation\n"
"    clear MODIFIER                 remove all keys for this modifier\n"
"    add MODIFIER = KEYSYM ...      add the keysyms to the modifier\n"
"    remove MODIFIER = KEYSYM ...   remove the keysyms from the modifier\n"
"\n"
"where NUMBER is a decimal, octal, or hex constant; KEYSYM is a valid\n"
"Key Symbol name; and MODIFIER is one of the eight modifier names:  Shift,\n"
"Lock, Control, Mod1, Mod2, Mod3, Mod4, or Mod5.  Lines beginning with\n"
"an exclamation mark (!) are taken as comments.  Case is significant except\n"
"for MODIFIER names.\n"
"\n"
"Keysyms on the left hand side of the = sign are looked up before any changes\n"
"are made; keysyms on the right are looked up after all of those on the left\n"
"have been resolved.  This makes it possible to swap modifier keys.\n"
"\n";


static void 
_X_NORETURN
grammar_usage(void)
{
    fprintf (stderr, "%s accepts the following input expressions:\n\n",
	     ProgramName);
    fprintf (stderr, "%s\n", grammar_message);
    Exit (0);
}

int parse_errors = 0;

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

