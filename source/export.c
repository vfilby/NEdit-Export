/*******************************************************************************
*									       
* export.c -- Nirvana Editor menus					       
*									       
* Copyright (C) 2001 Vincent Filby
*									       
* This is free software; you can redistribute it and/or modify it under the    
* terms of the GNU General Public License as published by the Free Software    
* Foundation; either version 2 of the License, or (at your option) any later   
* version.							               
* 									       
* This software is distributed in the hope that it will be useful, but WITHOUT 
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License 
* for more details.							       
* 									       
* You should have received a copy of the GNU General Public License along with 
* software; if not, write to the Free Software Foundation, Inc., 59 Temple     
* Place, Suite 330, Boston, MA  02111-1307 USA		                       
*									       
* Nirvana Text Editor	    						       
* May 3rd, 2001								       
*									       
* Written by Vincent Filby							       
*									       
*/
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#ifdef VMS
#include "../util/VMSparam.h"
#else
#include <sys/param.h>
#endif /*VMS*/
#include <X11/X.h>
#include <X11/Xatom.h>
#include <Xm/Xm.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/ToggleB.h>
#include <Xm/FileSB.h>
#include "../util/getfiles.h"
#include "../util/fontsel.h" /*... get rid of this */
#include "../util/DialogF.h"
#include "../util/misc.h"
#include "../util/fileUtils.h"
#include "textBuf.h"
#include "text.h"
#include "nedit.h"
#include "file.h"
#include "menu.h"
#include "window.h"
#include "search.h"
#include "selection.h"
#include "undo.h"
#include "shift.h"
#include "help.h"
#include "preferences.h"
#include "tags.h"
#include "userCmds.h"
#include "shell.h"
#include "macro.h"
#include "highlight.h"
#include "highlightData.h"
#include "rbTree.h"
#include "interpret.h"
#include "smartIndent.h"
#include "export.h"
#include "regularExp.h"
#include "textDisp.h"
#include "textSel.h"
#include "textP.h"


/* These defines and structsare taken from
 * highlightData.c.  They have been put here
 * because they were not in the public header */
#define FILL_MASK 0x100
#define SECONDARY_MASK 0x200
#define PRIMARY_MASK 0x400
#define HIGHLIGHT_MASK 0x800
#define STYLE_LOOKUP_MASK 0xff

typedef struct _highlightDataRec {
    regexp *startRE;
    regexp *endRE;
    regexp *errorRE;
    regexp *subPatternRE;
    char style;
    int colorOnly;
    signed char startSubexprs[NSUBEXP+1];
    signed char endSubexprs[NSUBEXP+1];
    int flags;
    int nSubPatterns;
    struct _highlightDataRec **subPatterns;
} highlightDataRec;

/* Context requirements for incremental reparsing of a pattern set */
typedef struct {
    int nLines;
    int nChars;
} reparseContext;

/* Data structure attached to window to hold all syntax highlighting
   information (for both drawing and incremental reparsing) */
typedef struct {
    highlightDataRec *pass1Patterns;
    highlightDataRec *pass2Patterns;
    char *majorStyles;
    reparseContext contextRequirements;
    styleTableEntry *styleTable;
    int nStyles;
    textBuffer *styleBuffer;
} windowHighlightData;
/* End of definitions form highlightData.c */

/* Max length of an html tag */
#define MAX_TAG_LENGTH 30


static void exportToHTML( Widget w, XEvent *event, String *args, Cardinal *nArgs);
static char *errorString(void);
void export(Widget w, XEvent *event, String *args, Cardinal *nArgs);
int PromptForHTMLFile(WindowInfo *window, char *prompt, char *fullname );
static void exportToHTML( Widget w, XEvent *event, String *args, Cardinal *nArgs);
static char *errorString(void);
static int styleOfPos(textDisp *textD, int lineStartPos,
    	int lineLen, int lineIndex, int dispIndex);
static int inSelection(selection *sel, int pos, int lineStartPos, int dispIndex);
static int max(int i1, int i2);
static int min(int i1, int i2);


/********************
 *  void exportAP
 *
 * DESCRIPTION
 *
 * RETURNS
 * 	static
 *
 */
void export(Widget w, XEvent *event, String *args, Cardinal *nArgs) {
		
	exportToHTML(w, event, args, nArgs);		
} /* export */


/********************
 *  exportToHTML
 *
 * DESCRIPTION
 *  Exports code to HTML with the syntax highlighting.
 *
 * RETURNS
 * 	int
 *
 */
static void exportToHTML( Widget w, XEvent *event, String *args, Cardinal *nArgs) {
	int i, j, response;
	int fileLen;
	int screenNum = XScreenNumberOfScreen( XtScreen(w));
	char **colorTagData;
	char **colorTagCloseData;
	char lastStyle = -1;
	char currentStyle;
	char *fileString = NULL;
	char *styleString = NULL;
	char name[MAXPATHLEN] = "";
	FILE *fp = NULL;

	XColor color;
	WindowInfo *window = WidgetToWindow(w);
	Display *display = XtDisplay( w );		
	Colormap colormap = DefaultColormap( display, screenNum );
	windowHighlightData *highlightData;
	textDisp *textD = ((TextWidget)window->textArea)->text.textD;
	int tabDist = BufGetTabDistance( window->buffer );

	/*Is syntaxhighlighting turned on?*/
	if( !window->highlightSyntax ) {
		DialogF( DF_WARN, window->shell, 1,
			"Turn on syntax highlighting before exporting.",
			"Dismiss" );
		return;		
	}                   

	response = PromptForHTMLFile( window, "Export to HTML:", name );



	if( response !=	GFN_OK )
		return;
	/* open the file */
#ifdef VMS
	if( (fp = fopen(name, "w", "rfm = stmlf")) == NULL  ) {
#else
	if( (fp = fopen( name, "w") ) == NULL ) {
#endif /* VMS */
		DialogF( DF_WARN, window->shell, 1,
			"Unable to open file %s:\n%s",
			"Dissmiss", name, errorString() );
		return;
	}                    

	/* Begin long wait */
	BeginWait( window->shell );
	XmUpdateDisplay( window->shell );

	highlightData = (windowHighlightData*)window->highlightData;		
	fileLen = window->buffer->length;
	fileString = BufGetAll( window->buffer );

	colorTagData = (char**)XtMalloc( sizeof( char* ) * highlightData->nStyles );
	colorTagCloseData = (char**)XtMalloc( sizeof( char* ) * highlightData->nStyles );

	/* For each style extract the font attributes and
	 * color.  Then convert them to html tags 
	 */		
	for( i = 0; i < highlightData->nStyles; i++ ) {
		colorTagData[i] = XtMalloc( sizeof( char ) * MAX_TAG_LENGTH );
		colorTagCloseData[i] = XtMalloc( sizeof( char ) * MAX_TAG_LENGTH );

		color.pixel = highlightData->styleTable[i].color;
		XQueryColor(  display, colormap, &color );

		if( highlightData->styleTable[i].font == window->italicFontStruct ) {
			sprintf( colorTagData[i], "<font color=\"#%02hX%02hX%02hX\"><i>", color.red/257, color.green/257, color.blue/257 );
			sprintf( colorTagCloseData[i], "</i></font>" );
		} else if (highlightData->styleTable[i].font == window->boldFontStruct) {
			sprintf( colorTagData[i], "<font color=\"#%02hX%02hX%02hX\"><b>", color.red/257, color.green/257, color.blue/257 );
			sprintf( colorTagCloseData[i], "</b></font>" );
		} else if (highlightData->styleTable[i].font == window->boldItalicFontStruct) {
			sprintf( colorTagData[i], "<font color=\"#%02hX%02hX%02hX\"><i><b>", color.red/257, color.green/257, color.blue/257 );
			sprintf( colorTagCloseData[i], "</b></i></font>" );
		} else {
			sprintf( colorTagData[i], "<font color=\"#%02hX%02hX%02hX\">", color.red/257, color.green/257, color.blue/257 );
			sprintf( colorTagCloseData[i], "</font>" );
		}
	}


	/* Change this to be an option? output bare HTML or
	 * a complete html page.  Note the closing html
	 * body, and pre tags below */
	fprintf( fp, "<html><body bgcolor=\"#ffffff\"><pre>" );
	for( i = 0; i < fileLen; i++ ) {
		int currentLine;
		int currentChar;
		currentStyle = BufGetCharacter( highlightData->styleBuffer, i );

		/* If the style is unfinished, use the unfinished call back
		 * to fill in the unfinished style */
		if( currentStyle == textD->unfinishedStyle ) {
			(textD->unfinishedHighlightCB)( textD, i, textD->highlightCBArg );
			currentStyle = BufGetCharacter( highlightData->styleBuffer, i );
		}
		if( currentStyle != lastStyle ) {
			if( lastStyle != -1 ) {
				fprintf( fp, "%s", colorTagCloseData[lastStyle - 'A'] );
			}
			fprintf( fp, "%s", colorTagData[currentStyle - 'A'] );
			lastStyle = currentStyle;
		}

		/* Convert characters to HTML escape sequences */
		if( fileString[i] == '<' ) {
			fprintf( fp, "&lt;" );
		} else if( fileString[i] == '>' ) {
			fprintf( fp, "&gt;" );
		} else if( fileString[i] == '\t' ) {
			int j;
			for( j = 0; j < tabDist; j++ )
				fprintf( fp, " " );
		} else {
			putc( fileString[i], fp );
		}
	}
	fprintf( fp, "</pre></body></html>" );
	putc( '\n', fp );
	fflush( fp );
	fclose( fp );
	XtFree( styleString );
	XtFree( fileString );

	EndWait( window->shell );
} /* exportToHTML */


/*
** Wrapper for strerror so all the calls don't have to be ifdef'd for VMS.
*/
static char *errorString(void)
{
#ifdef VMS
    return strerror(errno, vaxc$errno);
#else
    return strerror(errno);
#endif
}


/*
** Wrapper for GetNewFilename which uses the current window's path
** (if set) as the default directory, and asks about embedding newlines
** to make wrapping permanent.
*/
int PromptForHTMLFile(WindowInfo *window, char *prompt, char *fullname )
{
    int n, retVal;
    Arg args[20];
    XmString s1, s2;
    Widget fileSB;
    char *savedDefaultDir;
		char filename[MAXPATHLEN] = "";
    
    if( window->filenameSet ) {
			
			strcat(	filename, window->filename );
			strcat( filename, ".html" );
		}	 
    /* Temporarily set default directory to window->path, prompt for file,
       then, if the call was unsuccessful, restore the original default
       directory */
    savedDefaultDir = GetFileDialogDefaultDirectory();
    if (*window->path != '\0')
    	SetFileDialogDefaultDirectory(window->path);
    
    /* Present a file selection dialog with an added field for requesting
       long line wrapping to become permanent via inserted newlines */
    n = 0;
    XtSetArg(args[n], XmNselectionLabelString, 
    	    s1=XmStringCreateSimple(prompt)); n++;     
    XtSetArg(args[n], XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL); n++;
    XtSetArg(args[n], XmNdialogTitle, s2=XmStringCreateSimple(" ")); n++;
    XtSetArg(args[n], XmNresizePolicy, XmRESIZE_GROW); n++;
    fileSB = XmCreateFileSelectionDialog(window->shell,"FileSelect",args,n);
    XmStringFree(s1);
    XmStringFree(s2);

    XtVaSetValues(XmFileSelectionBoxGetChild(fileSB,
    	    XmDIALOG_FILTER_LABEL), XmNmnemonic, 'l', XmNuserData,
    	    XmFileSelectionBoxGetChild(fileSB, XmDIALOG_FILTER_TEXT), 0);
    XtVaSetValues(XmFileSelectionBoxGetChild(fileSB,
    	    XmDIALOG_DIR_LIST_LABEL), XmNmnemonic, 'D', XmNuserData,
    	    XmFileSelectionBoxGetChild(fileSB, XmDIALOG_DIR_LIST), 0);
    XtVaSetValues(XmFileSelectionBoxGetChild(fileSB,
    	    XmDIALOG_LIST_LABEL), XmNmnemonic, 'F', XmNuserData,
    	    XmFileSelectionBoxGetChild(fileSB, XmDIALOG_LIST), 0);
    XtVaSetValues(XmFileSelectionBoxGetChild(fileSB,
    	    XmDIALOG_SELECTION_LABEL), XmNmnemonic,
    	    prompt[strspn(prompt, "lFD")], XmNuserData,
    	    XmFileSelectionBoxGetChild(fileSB, XmDIALOG_TEXT), 0);
    AddDialogMnemonicHandler(fileSB, FALSE);
    RemapDeleteKey(XmFileSelectionBoxGetChild(fileSB, XmDIALOG_FILTER_TEXT));
    RemapDeleteKey(XmFileSelectionBoxGetChild(fileSB, XmDIALOG_TEXT));
    retVal = HandleCustomNewFileSB(fileSB, fullname,
    	    window->filenameSet ? filename : NULL);

    if (retVal != GFN_OK)
    	SetFileDialogDefaultDirectory(savedDefaultDir);
    if (savedDefaultDir != NULL)
    	XtFree(savedDefaultDir);
    return retVal;
}
