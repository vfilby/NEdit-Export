#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 3 "parse.y"
#include <stdio.h>
#include <ctype.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#ifdef VMS
#include "../util/VMSparam.h"
#else
#ifndef __MVS__
#include <sys/param.h>
#endif
#endif /*VMS*/
#include "textBuf.h"
#include "nedit.h"
#include "rbTree.h"
#include "interpret.h"
#include "parse.h"

/* Macros to add error processing to AddOp and AddSym calls */
#define ADD_OP(op) if (!AddOp(op, &ErrMsg)) return 1
#define ADD_SYM(sym) if (!AddSym(sym, &ErrMsg)) return 1
#define ADD_IMMED(val) if (!AddImmediate(val, &ErrMsg)) return 1
#define ADD_BR_OFF(to) if (!AddBranchOffset(to, &ErrMsg)) return 1
#define SET_BR_OFF(from, to) *((int *)(from)) = ((Inst *)(to)) - ((Inst *)(from))

/* Max. length for a string constant (... there shouldn't be a maximum) */
#define MAX_STRING_CONST_LEN 5000

static const char CVSID[] = "$Id: parse.y,v 1.15 2001/07/11 21:35:50 amai Exp $";
static int yyerror(char *s);
static int yylex(void);
int yyparse(void);
static int follow(char expect, int yes, int no);
static int follow2(char expect1, int yes1, char expect2, int yes2, int no);
static int follow_non_whitespace(char expect, int yes, int no);
static Symbol *matchesActionRoutine(char **inPtr);

static char *ErrMsg;
static char *InPtr;

#line 44 "parse.y"
typedef union {
    Symbol *sym;
    Inst *inst;
    int nArgs;
} YYSTYPE;
#line 63 "y.tab.c"
#define YYERRCODE 256
#define NUMBER 257
#define STRING 258
#define SYMBOL 259
#define IF 260
#define WHILE 261
#define ELSE 262
#define FOR 263
#define BREAK 264
#define CONTINUE 265
#define RETURN 266
#define IF_NO_ELSE 267
#define ADDEQ 268
#define SUBEQ 269
#define MULEQ 270
#define DIVEQ 271
#define MODEQ 272
#define ANDEQ 273
#define OREQ 274
#define CONCAT 275
#define OR 276
#define AND 277
#define GT 278
#define GE 279
#define LT 280
#define LE 281
#define EQ 282
#define NE 283
#define IN 284
#define UNARY_MINUS 285
#define NOT 286
#define DELETE 287
#define INCR 288
#define DECR 289
#define POW 290
const short yylhs[] = {                                        -1,
    0,    0,    0,    0,   12,   12,   12,   11,   11,   13,
   13,   13,   13,   13,   15,   13,   13,   13,   13,   13,
   14,   14,   14,   14,   14,   14,   14,   14,   14,   14,
   17,   14,   18,   14,   19,   14,   20,   14,   21,   14,
   22,   14,   23,   14,   14,   14,   14,   14,   14,    9,
    3,    3,    3,    1,    1,    1,   16,   16,   24,   24,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   24,   24,   24,   24,   24,   24,   24,   24,   24,   24,
   24,   24,   24,   24,   24,   24,   24,    5,    4,    6,
    2,    2,    7,    8,   10,   10,
};
const short yylen[] = {                                         2,
    2,    5,    4,    1,    5,    4,    1,    1,    2,    3,
    6,    9,    6,   10,    0,    9,    3,    3,    4,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    5,    6,
    0,    7,    0,    7,    0,    7,    0,    7,    0,    7,
    0,    7,    0,    7,    4,    2,    2,    2,    2,    1,
    0,    1,    3,    0,    1,    3,    1,    2,    1,    1,
    1,    4,    3,    4,    3,    3,    3,    3,    3,    3,
    2,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    2,    2,    2,    2,    2,    3,    1,    1,    1,
    0,    1,    1,    1,    0,    2,
};
const short yydefred[] = {                                      0,
    4,    0,    0,    0,    0,   88,   89,    0,    0,    0,
    0,    0,    0,   95,   96,    0,    0,    0,    0,    8,
    0,    0,   47,   49,    0,    0,    0,   95,   95,   59,
   60,    0,    0,    0,    0,    0,    0,   95,    0,    0,
    0,   46,   48,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    9,   95,    0,    0,    0,    0,    0,
    0,    0,    0,   84,   86,    0,    0,    0,   83,   85,
    0,    0,   95,    0,   94,   93,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    3,    0,    0,    0,   52,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   45,   95,    0,   63,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    0,    0,    0,   95,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   62,   64,   29,    0,    0,   53,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   95,    0,    7,   15,    0,
   13,    0,    0,    0,    0,    0,    0,    0,    0,   90,
   95,   95,    0,   95,    0,    0,    0,   95,    0,   95,
   12,   16,    0,    0,   14,
};
const short yydgoto[] = {                                       2,
   57,   60,   99,   16,   17,  181,   93,   94,   18,    3,
   19,  167,  168,   21,  182,   58,  142,  143,  144,  145,
  146,  147,  148,   40,
};
const short yysindex[] = {                                   -253,
    0,    0,  718,  -33,  -28,    0,    0,   12,   19,  176,
 -228, -226, -223,    0,    0,    5,    7,  412, 1138,    0,
   39,  380,    0,    0,  380,  380,  380,    0,    0,    0,
    0,    3,  380,  380, -206, -205,  380,    0,  504,  -32,
  -36,    0,    0,  222, -120,  380,  380,  380,  380,  380,
  380,  380,  380,    0,    0,  380,  -30,  380,   33,   20,
  -32,   68,   68,    0,    0,  380,  -91,  -91,    0,    0,
  301,   68,    0,  -32,    0,    0,  380,  380,  380,  380,
  380,  380,  380,  380,  380,  380,  380,  380,  380,  380,
  380,  380,  380,  380,  380,    0, 1119,   11,   -9,    0,
   21,  380,  380,  380,  380,  380,  380,  380,   68,   22,
  380,    0,    0,   41,    0,   68, 1271, 1285,   -5,   -5,
   -5,   -5,   -5,   -5,   -5,   -3,   -3,  -91,  -91,  -91,
  -91,  -24, 1253, 1216,  -20,    0, -172,  380,  -65,    0,
  380, -175, -165, -173, -166, -160, -157, -155,  380,  879,
    0,    0,    0,   76,   62,    0,  879,  380,  380,  380,
  380,  380,  380,  380,  380,    0, -132,    0,    0,  -65,
    0,  380,  380,  380,  380,  380,  380,  380,  923,    0,
    0,    0,   55,    0, 1130,  879,  879,    0,   68,    0,
    0,    0,  879,   68,    0,
};
const short yyrindex[] = {                                    954,
    0,    0,    0,  446,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  140,    0,
    0,    0,    0,    0,  -17,   65,  102,    0,    0,    0,
    0,  117,    0,    0,    0,    0,    0,    0,    0,   91,
    0,    0,    0,    0,    8,  102,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   16,    0,  -25,    0,    0,
  -18,    1,    9,    0,    0,   65,  160,  368,    0,    0,
    0,   17,    0, 1181,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -17,    0,    0,  -17,    0,    0,  446,    0,    0,
    0,   69,   74,   79,  104,  112,  131,  136,   48,  575,
    0,    0,    0,    0,    0,   56, 1035,  993,  665,  741,
  781,  826,  872,  917,  950,  574,  620,  413,  453,  489,
  529,    0, 1078,  464,    0,    0,    0,   77,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -23,    0,
    0,    0,    0,    0,    0,    0,    0,  329,    0,    0,
    0,    0,    0,    0,    0,    0,  103,    0,    0,   67,
    0,  497,  506,  542,  551,  552,  565,  618,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   64,    0,
    0,    0,    0,   95,    0,
};
const short yygindex[] = {                                      0,
   -1,  -38,  -26,    0,    0,    0,    0,    0,    0,   52,
  -42,   -8,   27,  -41,    0, 1321,    0,    0,    0,    0,
    0,    0,    0, 1543,
};
#define YYTABLESIZE 1721
const short yytable[] = {                                      92,
   17,   97,    1,  100,   90,   78,   26,  101,   18,   88,
   86,   27,   87,  111,   89,   55,   20,   56,   55,  111,
   56,   28,   92,  111,   59,   21,   54,   22,   29,   20,
   41,   90,   42,   90,  139,   43,   88,   86,   88,   87,
   92,   89,   66,   89,   45,   54,   46,   10,   55,  138,
   26,   51,   69,   70,   95,   19,   21,   25,   92,   21,
  113,  140,  110,    6,  114,   44,   51,   55,  152,   56,
   20,   22,  153,  112,   21,   54,  111,   15,   22,   62,
   63,  151,  141,   23,  111,   92,  154,   92,   24,   72,
  132,   77,  159,  135,    5,  188,  161,  156,  139,  155,
   57,   25,   11,  160,  162,   54,  109,   51,   54,   22,
   51,  163,   22,   25,   23,  164,  169,   23,  165,   24,
  170,   26,   24,   54,  116,   17,   61,   22,  100,  180,
   57,   57,   23,   18,   57,   91,  185,   24,   98,    1,
   27,   20,   91,  183,   25,   28,    0,   25,  171,   57,
    0,    0,   26,   61,   61,   26,    0,   61,   61,   61,
   61,   61,   25,   61,  150,    0,   11,   12,   13,   71,
   26,   27,   10,    0,   27,   61,   28,  191,  192,   28,
   19,    0,    0,   57,  195,   38,    0,    0,    6,   27,
    0,  157,    0,    4,   28,    0,   71,   71,   91,   71,
   71,   71,   71,   71,   71,   20,   71,   61,    0,   61,
    0,   54,    0,    0,    0,   37,    0,  179,   71,    5,
   33,   11,   12,   13,    0,    0,    0,   11,    0,    0,
    0,   15,  186,  187,    0,  189,    0,    0,    0,  193,
   61,  194,    0,   75,   76,   79,   80,   81,   82,   83,
   84,   85,   71,    0,   23,   24,    0,   91,    0,   17,
   17,   17,   17,   17,   17,   17,   17,   18,   18,   18,
   18,   18,   18,   18,   18,   20,   20,   20,   20,   20,
   20,   20,   20,   71,   91,    0,   91,   17,   17,   17,
   64,   65,    0,    0,  137,   18,   18,   18,   23,   24,
    0,    0,    0,   20,   20,   20,   10,   10,   10,   10,
   10,   10,   10,   10,   19,   19,   19,   19,   19,   19,
   19,   19,    6,    6,    6,    6,    6,    6,    6,    6,
    0,    0,    0,    0,   10,   10,   10,    0,   30,    0,
   37,  115,   19,   19,   19,   33,   96,   57,   57,   57,
    6,    6,    6,    5,    5,    5,    5,    5,    5,    5,
    5,   11,   11,   11,    0,   11,   11,   11,   11,   30,
    0,    0,   30,   61,   61,   61,   57,   82,   57,   57,
    0,    5,    5,    5,    0,    0,    0,   30,    0,   11,
   11,   11,   61,   61,   61,   61,   61,   61,   61,   61,
   61,    0,   61,    0,   82,   82,   61,   82,   82,   82,
   82,   82,   82,    0,   82,    0,   71,   71,   71,   37,
    0,    0,   67,    0,   33,    0,   82,    0,    0,    0,
    0,    0,   30,   31,   32,   71,   71,   71,   71,   71,
   71,   71,   71,   71,    0,   71,    0,   71,   71,   67,
   67,    0,   67,   67,   67,   67,   67,   67,    0,   67,
   82,   34,   68,   35,   36,    0,    0,    0,    0,    0,
    0,   67,    0,   81,    0,    0,    0,    0,    0,    0,
    4,    5,    6,    0,    7,    8,    9,   10,    0,   68,
   68,   82,   68,   68,   68,   68,   68,   68,   69,   68,
    0,    0,    0,   81,   81,   67,   32,   81,   11,   12,
   13,   68,    0,   73,    0,   34,    0,    0,    0,    0,
    0,    0,   81,    0,    0,   69,   69,    0,   69,   69,
   69,   69,   69,   69,    0,   69,   67,   32,   70,    0,
   32,    0,    0,   37,    0,   68,   34,   69,   33,   34,
    0,   36,    0,    0,    0,   32,   81,   30,   31,   32,
   38,   40,    0,    0,   34,   70,   70,    0,   70,   70,
   70,   70,   70,   70,   42,   70,   68,    0,    0,    0,
    0,   69,   36,   65,    0,   36,   34,   70,   35,   36,
    0,   38,   40,    0,   38,   40,    0,    0,    0,    0,
   36,    0,    0,    0,    0,   42,    0,    0,   42,   38,
   40,   65,   69,   65,   65,    0,   65,   65,   65,    0,
    0,   70,    0,   42,   82,   82,   82,   44,    0,   66,
    0,    0,   65,    0,    0,    0,   30,   31,   32,    0,
    0,    0,    0,   82,   82,   82,   82,   82,   82,   82,
   82,   82,   70,   82,    0,   82,   82,   66,   44,   66,
   66,   44,   66,   66,   66,   34,   65,   35,   36,   67,
   67,   67,    0,    0,   72,    0,   44,    0,   66,   47,
   48,   49,   50,   51,   52,   53,    0,    0,   67,   67,
   67,   67,   67,   67,   67,   67,   67,   65,   67,    0,
   67,   67,   72,    0,   72,   72,    0,    0,   72,   68,
   68,   68,   66,   50,   50,   50,   50,   50,   50,   50,
   81,   81,   81,   72,    0,    0,    0,   15,   68,   68,
   68,   68,   68,   68,   68,   68,   68,    0,   68,   81,
   68,   68,    0,   66,    0,   69,   69,   69,    0,   81,
   73,   81,   81,    0,    0,    0,    0,   72,    0,    0,
   30,   31,   32,    0,   69,   69,   69,   69,   69,   69,
   69,   69,   69,    0,   69,    0,   69,   69,   73,    0,
   73,   73,    0,    0,   73,   70,   70,   70,   72,   34,
   74,   35,   36,    0,    0,    0,    0,    0,    0,   73,
    0,    0,    0,    0,   70,   70,   70,   70,   70,   70,
   70,   70,   70,    0,   70,    0,   70,   70,   74,    0,
   74,   74,    0,    0,   74,    0,    0,    0,    0,    0,
   65,   65,   65,   73,    0,   75,    0,    0,    0,   74,
   14,    0,   31,   33,   35,   37,   39,   41,   43,   65,
   65,   65,   65,   65,   65,   65,   65,   65,    0,   65,
    0,   65,   65,   75,   73,   75,   75,    0,    0,   75,
    0,    0,    0,   74,    0,    0,   66,   66,   66,    0,
    0,   76,    0,    0,   75,    0,    0,    0,   15,    0,
    0,    0,    0,    0,    0,   66,   66,   66,   66,   66,
   66,   66,   66,   66,   74,   66,    0,   66,   66,   76,
    0,   76,   76,    0,    0,   76,    0,    0,   75,    0,
    0,   72,   72,   72,    0,    0,   77,    0,    0,    0,
   76,    0,   15,    0,    0,    0,    0,    0,    0,    0,
   72,   72,   72,   72,   72,   72,   72,   72,   72,   75,
   72,    0,   72,   72,   77,    0,   77,   77,    0,   87,
   77,    0,    0,   95,   76,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   77,    4,    5,    6,    0,
    7,    8,    9,   10,    0,    0,    0,   87,    0,   87,
   87,    0,    0,   87,    0,   76,    0,   73,   73,   73,
    0,  166,   78,    0,   11,   12,   13,    0,   87,   77,
    0,    0,    0,    0,    0,    0,   73,   73,   73,   73,
   73,   73,   73,   73,   73,    0,   73,    0,   73,   73,
   78,    0,   78,   78,    0,    0,   78,   74,   74,   74,
   77,    0,   87,    0,   79,    0,    0,  184,    0,    0,
    0,   78,    0,    0,    0,    0,   74,   74,   74,   74,
   74,   74,   74,   74,   74,    0,   74,    0,   74,   74,
    0,    0,    0,   87,   79,   79,   95,    0,   79,    0,
    0,    0,   75,   75,   75,   78,    0,   80,    0,    0,
    0,    0,    0,   79,    0,    0,    0,    0,    0,    0,
    0,   75,   75,   75,   75,   75,   75,   75,   75,   75,
    0,   75,    0,   75,   75,    0,   78,   80,   80,    0,
    0,   80,    0,    0,    0,    0,    0,   79,   76,   76,
   76,    0,    0,    0,    0,    0,   80,    4,    5,    6,
    0,    7,    8,    9,   10,    0,    0,   76,   76,   76,
   76,   76,   76,   76,   76,   76,    0,   76,   79,   76,
   76,    0,    0,    0,    0,   11,   12,   13,    0,    0,
   80,    0,    0,   77,   77,   77,    0,    0,    0,    0,
    0,    4,    5,    6,    0,    7,    8,    9,   10,    0,
   58,    0,   77,   77,   77,   77,   77,   77,   77,   77,
   77,    0,   77,    0,   77,   77,   87,   87,   87,   11,
   12,   13,   95,   95,   95,    0,   95,   95,   95,   95,
   58,   58,    0,    0,   58,   87,   87,   87,   87,   87,
   87,   87,   87,   87,    0,   87,    0,   87,   87,   58,
   95,   95,   95,  136,    0,    0,    0,    0,    0,   78,
   78,   78,   90,   78,  190,    0,    0,   88,   86,    0,
   87,    0,   89,    0,    0,    0,    0,    0,   78,   78,
    0,    0,    0,   58,    0,    0,    0,    0,   78,    0,
   78,   78,    0,    0,    0,    0,    0,    0,    0,   90,
   78,   79,   79,   79,   88,   86,    0,   87,    0,   89,
    0,    0,    0,    0,    0,    0,   92,   90,   78,    0,
   79,   79,   88,   86,    0,   87,    0,   89,    0,    0,
   79,   90,   79,   79,    0,    0,   88,   86,    0,   87,
   39,   89,    0,    0,   80,   80,   80,    0,    0,   77,
    0,    0,   56,   92,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   80,   80,    0,    0,   71,    0,    0,
    0,   92,    0,   80,    0,   80,   80,  102,  103,  104,
  105,  106,  107,  108,    0,   92,   77,    4,    5,    6,
    0,    7,    8,    9,   10,    0,    0,    0,    4,    5,
    6,    0,    7,    8,    9,   10,    4,    5,    6,    0,
    7,    8,    9,   10,    0,   11,   12,   13,    0,    0,
    0,    0,    0,    0,    0,    0,   11,   12,   13,    0,
    0,    0,    0,    0,   11,   12,   13,    0,    0,    0,
    0,  149,    0,    0,    0,    0,    0,   58,   58,   58,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  158,    0,    0,    0,    0,   58,    0,   58,   58,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  172,
  173,  174,  175,  176,  177,  178,    0,    0,    0,    0,
    0,    0,   76,   79,   80,   81,   82,   83,   84,   85,
    0,    0,    0,    0,    0,   91,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   79,   80,   81,   82,   83,   84,   85,    0,    0,    0,
    0,    0,   91,    0,    0,    0,    0,    0,   79,   80,
   81,   82,   83,   84,   85,    0,    0,    0,    0,    0,
   91,    0,   79,   80,   81,   82,   83,   84,   85,   61,
    0,    0,    0,    0,   91,   67,   68,    0,    0,    0,
    0,   74,    0,    0,    0,    0,    0,    0,   61,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   74,    0,
   74,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   74,    0,    0,    0,    0,    0,  117,
  118,  119,  120,  121,  122,  123,  124,  125,  126,  127,
  128,  129,  130,  131,    0,  133,  134,    0,    0,    0,
    0,    0,    0,    0,   74,   74,   74,   74,   74,   74,
   74,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   61,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   74,    0,    0,    0,    0,    0,    0,    0,    0,
   74,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   74,   74,   74,   74,   74,   74,
   74,
};
const short yycheck[] = {                                      91,
    0,   44,  256,   45,   37,   38,   40,   46,    0,   42,
   43,   40,   45,   44,   47,   41,    0,   41,   44,   44,
   44,   10,   41,   44,   26,   10,   44,   61,   10,    3,
  259,   37,  259,   37,   44,  259,   42,   43,   42,   45,
   59,   47,   40,   47,   40,   19,   40,    0,   10,   59,
   40,   44,  259,  259,   91,    0,   41,   91,   91,   44,
   41,   41,   93,    0,   66,   14,   59,   93,   93,   93,
   44,   61,   93,   41,   59,   93,   44,   10,   10,   28,
   29,   41,   61,   10,   44,   91,  259,   91,   10,   38,
   92,  124,  268,   95,    0,   41,  270,  139,   44,  138,
   10,   91,    0,  269,  271,   41,   55,   41,   44,   41,
   44,  272,   44,   10,   41,  273,   41,   44,  274,   41,
   59,   10,   44,   97,   73,  125,   10,   59,  170,  262,
   40,   41,   59,  125,   44,   59,  179,   59,  259,    0,
   10,  125,   41,  170,   41,   10,   -1,   44,  157,   59,
   -1,   -1,   41,   37,   38,   44,   -1,   41,   42,   43,
   44,   45,   59,   47,  113,   -1,  287,  288,  289,   10,
   59,   41,  125,   -1,   44,   59,   41,  186,  187,   44,
  125,   -1,   -1,   93,  193,   10,   -1,   -1,  125,   59,
   -1,  140,   -1,  259,   59,   -1,   37,   38,  290,   40,
   41,   42,   43,   44,   45,  179,   47,   91,   -1,   93,
   -1,  185,   -1,   -1,   -1,   40,   -1,  166,   59,  125,
   45,  287,  288,  289,   -1,   -1,   -1,  125,   -1,   -1,
   -1,   10,  181,  182,   -1,  184,   -1,   -1,   -1,  188,
  124,  190,   -1,  276,  277,  278,  279,  280,  281,  282,
  283,  284,   93,   -1,  288,  289,   -1,  290,   -1,  259,
  260,  261,  262,  263,  264,  265,  266,  259,  260,  261,
  262,  263,  264,  265,  266,  259,  260,  261,  262,  263,
  264,  265,  266,  124,  290,   -1,  290,  287,  288,  289,
  288,  289,   -1,   -1,  284,  287,  288,  289,  288,  289,
   -1,   -1,   -1,  287,  288,  289,  259,  260,  261,  262,
  263,  264,  265,  266,  259,  260,  261,  262,  263,  264,
  265,  266,  259,  260,  261,  262,  263,  264,  265,  266,
   -1,   -1,   -1,   -1,  287,  288,  289,   -1,   10,   -1,
   40,   41,  287,  288,  289,   45,  125,  257,  258,  259,
  287,  288,  289,  259,  260,  261,  262,  263,  264,  265,
  266,  259,  260,  261,   -1,  263,  264,  265,  266,   41,
   -1,   -1,   44,  257,  258,  259,  286,   10,  288,  289,
   -1,  287,  288,  289,   -1,   -1,   -1,   59,   -1,  287,
  288,  289,  276,  277,  278,  279,  280,  281,  282,  283,
  284,   -1,  286,   -1,   37,   38,  290,   40,   41,   42,
   43,   44,   45,   -1,   47,   -1,  257,  258,  259,   40,
   -1,   -1,   10,   -1,   45,   -1,   59,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  276,  277,  278,  279,  280,
  281,  282,  283,  284,   -1,  286,   -1,  288,  289,   37,
   38,   -1,   40,   41,   42,   43,   44,   45,   -1,   47,
   93,  286,   10,  288,  289,   -1,   -1,   -1,   -1,   -1,
   -1,   59,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,
  259,  260,  261,   -1,  263,  264,  265,  266,   -1,   37,
   38,  124,   40,   41,   42,   43,   44,   45,   10,   47,
   -1,   -1,   -1,   40,   41,   93,   10,   44,  287,  288,
  289,   59,   -1,   10,   -1,   10,   -1,   -1,   -1,   -1,
   -1,   -1,   59,   -1,   -1,   37,   38,   -1,   40,   41,
   42,   43,   44,   45,   -1,   47,  124,   41,   10,   -1,
   44,   -1,   -1,   40,   -1,   93,   41,   59,   45,   44,
   -1,   10,   -1,   -1,   -1,   59,   93,  257,  258,  259,
   10,   10,   -1,   -1,   59,   37,   38,   -1,   40,   41,
   42,   43,   44,   45,   10,   47,  124,   -1,   -1,   -1,
   -1,   93,   41,   10,   -1,   44,  286,   59,  288,  289,
   -1,   41,   41,   -1,   44,   44,   -1,   -1,   -1,   -1,
   59,   -1,   -1,   -1,   -1,   41,   -1,   -1,   44,   59,
   59,   38,  124,   40,   41,   -1,   43,   44,   45,   -1,
   -1,   93,   -1,   59,  257,  258,  259,   10,   -1,   10,
   -1,   -1,   59,   -1,   -1,   -1,  257,  258,  259,   -1,
   -1,   -1,   -1,  276,  277,  278,  279,  280,  281,  282,
  283,  284,  124,  286,   -1,  288,  289,   38,   41,   40,
   41,   44,   43,   44,   45,  286,   93,  288,  289,  257,
  258,  259,   -1,   -1,   10,   -1,   59,   -1,   59,  268,
  269,  270,  271,  272,  273,  274,   -1,   -1,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  124,  286,   -1,
  288,  289,   38,   -1,   40,   41,   -1,   -1,   44,  257,
  258,  259,   93,  268,  269,  270,  271,  272,  273,  274,
  257,  258,  259,   59,   -1,   -1,   -1,   10,  276,  277,
  278,  279,  280,  281,  282,  283,  284,   -1,  286,  276,
  288,  289,   -1,  124,   -1,  257,  258,  259,   -1,  286,
   10,  288,  289,   -1,   -1,   -1,   -1,   93,   -1,   -1,
  257,  258,  259,   -1,  276,  277,  278,  279,  280,  281,
  282,  283,  284,   -1,  286,   -1,  288,  289,   38,   -1,
   40,   41,   -1,   -1,   44,  257,  258,  259,  124,  286,
   10,  288,  289,   -1,   -1,   -1,   -1,   -1,   -1,   59,
   -1,   -1,   -1,   -1,  276,  277,  278,  279,  280,  281,
  282,  283,  284,   -1,  286,   -1,  288,  289,   38,   -1,
   40,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,   93,   -1,   10,   -1,   -1,   -1,   59,
  123,   -1,  268,  269,  270,  271,  272,  273,  274,  276,
  277,  278,  279,  280,  281,  282,  283,  284,   -1,  286,
   -1,  288,  289,   38,  124,   40,   41,   -1,   -1,   44,
   -1,   -1,   -1,   93,   -1,   -1,  257,  258,  259,   -1,
   -1,   10,   -1,   -1,   59,   -1,   -1,   -1,   10,   -1,
   -1,   -1,   -1,   -1,   -1,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  124,  286,   -1,  288,  289,   38,
   -1,   40,   41,   -1,   -1,   44,   -1,   -1,   93,   -1,
   -1,  257,  258,  259,   -1,   -1,   10,   -1,   -1,   -1,
   59,   -1,   10,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  124,
  286,   -1,  288,  289,   38,   -1,   40,   41,   -1,   10,
   44,   -1,   -1,   10,   93,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   59,  259,  260,  261,   -1,
  263,  264,  265,  266,   -1,   -1,   -1,   38,   -1,   40,
   41,   -1,   -1,   44,   -1,  124,   -1,  257,  258,  259,
   -1,  123,   10,   -1,  287,  288,  289,   -1,   59,   93,
   -1,   -1,   -1,   -1,   -1,   -1,  276,  277,  278,  279,
  280,  281,  282,  283,  284,   -1,  286,   -1,  288,  289,
   38,   -1,   40,   41,   -1,   -1,   44,  257,  258,  259,
  124,   -1,   93,   -1,   10,   -1,   -1,  125,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,  276,  277,  278,  279,
  280,  281,  282,  283,  284,   -1,  286,   -1,  288,  289,
   -1,   -1,   -1,  124,   40,   41,  123,   -1,   44,   -1,
   -1,   -1,  257,  258,  259,   93,   -1,   10,   -1,   -1,
   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  276,  277,  278,  279,  280,  281,  282,  283,  284,
   -1,  286,   -1,  288,  289,   -1,  124,   40,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,   -1,   93,  257,  258,
  259,   -1,   -1,   -1,   -1,   -1,   59,  259,  260,  261,
   -1,  263,  264,  265,  266,   -1,   -1,  276,  277,  278,
  279,  280,  281,  282,  283,  284,   -1,  286,  124,  288,
  289,   -1,   -1,   -1,   -1,  287,  288,  289,   -1,   -1,
   93,   -1,   -1,  257,  258,  259,   -1,   -1,   -1,   -1,
   -1,  259,  260,  261,   -1,  263,  264,  265,  266,   -1,
   10,   -1,  276,  277,  278,  279,  280,  281,  282,  283,
  284,   -1,  286,   -1,  288,  289,  257,  258,  259,  287,
  288,  289,  259,  260,  261,   -1,  263,  264,  265,  266,
   40,   41,   -1,   -1,   44,  276,  277,  278,  279,  280,
  281,  282,  283,  284,   -1,  286,   -1,  288,  289,   59,
  287,  288,  289,  125,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,   37,   38,  125,   -1,   -1,   42,   43,   -1,
   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,  276,  277,
   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,  286,   -1,
  288,  289,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,
   38,  257,  258,  259,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,   -1,   -1,   -1,   -1,   91,   37,   38,   -1,
  276,  277,   42,   43,   -1,   45,   -1,   47,   -1,   -1,
  286,   37,  288,  289,   -1,   -1,   42,   43,   -1,   45,
   10,   47,   -1,   -1,  257,  258,  259,   -1,   -1,  124,
   -1,   -1,   22,   91,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  276,  277,   -1,   -1,   37,   -1,   -1,
   -1,   91,   -1,  286,   -1,  288,  289,   47,   48,   49,
   50,   51,   52,   53,   -1,   91,  124,  259,  260,  261,
   -1,  263,  264,  265,  266,   -1,   -1,   -1,  259,  260,
  261,   -1,  263,  264,  265,  266,  259,  260,  261,   -1,
  263,  264,  265,  266,   -1,  287,  288,  289,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  287,  288,  289,   -1,
   -1,   -1,   -1,   -1,  287,  288,  289,   -1,   -1,   -1,
   -1,  111,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  141,   -1,   -1,   -1,   -1,  286,   -1,  288,  289,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  159,
  160,  161,  162,  163,  164,  165,   -1,   -1,   -1,   -1,
   -1,   -1,  277,  278,  279,  280,  281,  282,  283,  284,
   -1,   -1,   -1,   -1,   -1,  290,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  278,  279,  280,  281,  282,  283,  284,   -1,   -1,   -1,
   -1,   -1,  290,   -1,   -1,   -1,   -1,   -1,  278,  279,
  280,  281,  282,  283,  284,   -1,   -1,   -1,   -1,   -1,
  290,   -1,  278,  279,  280,  281,  282,  283,  284,   27,
   -1,   -1,   -1,   -1,  290,   33,   34,   -1,   -1,   -1,
   -1,   39,   -1,   -1,   -1,   -1,   -1,   -1,   46,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   56,   -1,
   58,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   71,   -1,   -1,   -1,   -1,   -1,   77,
   78,   79,   80,   81,   82,   83,   84,   85,   86,   87,
   88,   89,   90,   91,   -1,   93,   94,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  102,  103,  104,  105,  106,  107,
  108,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  138,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  149,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  158,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  172,  173,  174,  175,  176,  177,
  178,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,0,"';'",0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'{'","'|'","'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"NUMBER","STRING","SYMBOL","IF","WHILE",
"ELSE","FOR","BREAK","CONTINUE","RETURN","IF_NO_ELSE","ADDEQ","SUBEQ","MULEQ",
"DIVEQ","MODEQ","ANDEQ","OREQ","CONCAT","OR","AND","GT","GE","LT","LE","EQ",
"NE","IN","UNARY_MINUS","NOT","DELETE","INCR","DECR","POW",
};
const char * const yyrule[] = {
"$accept : program",
"program : blank stmts",
"program : blank '{' blank stmts '}'",
"program : blank '{' blank '}'",
"program : error",
"block : '{' blank stmts '}' blank",
"block : '{' blank '}' blank",
"block : stmt",
"stmts : stmt",
"stmts : stmts stmt",
"stmt : simpstmt '\\n' blank",
"stmt : IF '(' cond ')' blank block",
"stmt : IF '(' cond ')' blank block else blank block",
"stmt : while '(' cond ')' blank block",
"stmt : for '(' comastmts ';' cond ';' comastmts ')' blank block",
"$$1 :",
"stmt : for '(' SYMBOL IN SYMBOL ')' $$1 blank block",
"stmt : BREAK '\\n' blank",
"stmt : CONTINUE '\\n' blank",
"stmt : RETURN expr '\\n' blank",
"stmt : RETURN '\\n' blank",
"simpstmt : SYMBOL '=' expr",
"simpstmt : evalsym ADDEQ expr",
"simpstmt : evalsym SUBEQ expr",
"simpstmt : evalsym MULEQ expr",
"simpstmt : evalsym DIVEQ expr",
"simpstmt : evalsym MODEQ expr",
"simpstmt : evalsym ANDEQ expr",
"simpstmt : evalsym OREQ expr",
"simpstmt : DELETE SYMBOL '[' arglist ']'",
"simpstmt : SYMBOL '[' arglist ']' '=' expr",
"$$2 :",
"simpstmt : SYMBOL '[' arglist ']' $$2 ADDEQ expr",
"$$3 :",
"simpstmt : SYMBOL '[' arglist ']' $$3 SUBEQ expr",
"$$4 :",
"simpstmt : SYMBOL '[' arglist ']' $$4 MULEQ expr",
"$$5 :",
"simpstmt : SYMBOL '[' arglist ']' $$5 DIVEQ expr",
"$$6 :",
"simpstmt : SYMBOL '[' arglist ']' $$6 MODEQ expr",
"$$7 :",
"simpstmt : SYMBOL '[' arglist ']' $$7 ANDEQ expr",
"$$8 :",
"simpstmt : SYMBOL '[' arglist ']' $$8 OREQ expr",
"simpstmt : SYMBOL '(' arglist ')'",
"simpstmt : INCR SYMBOL",
"simpstmt : SYMBOL INCR",
"simpstmt : DECR SYMBOL",
"simpstmt : SYMBOL DECR",
"evalsym : SYMBOL",
"comastmts :",
"comastmts : simpstmt",
"comastmts : comastmts ',' simpstmt",
"arglist :",
"arglist : expr",
"arglist : arglist ',' expr",
"expr : numexpr",
"expr : expr numexpr",
"numexpr : NUMBER",
"numexpr : STRING",
"numexpr : SYMBOL",
"numexpr : SYMBOL '(' arglist ')'",
"numexpr : '(' expr ')'",
"numexpr : numexpr '[' arglist ']'",
"numexpr : numexpr '+' numexpr",
"numexpr : numexpr '-' numexpr",
"numexpr : numexpr '*' numexpr",
"numexpr : numexpr '/' numexpr",
"numexpr : numexpr '%' numexpr",
"numexpr : numexpr POW numexpr",
"numexpr : '-' numexpr",
"numexpr : numexpr GT numexpr",
"numexpr : numexpr GE numexpr",
"numexpr : numexpr LT numexpr",
"numexpr : numexpr LE numexpr",
"numexpr : numexpr EQ numexpr",
"numexpr : numexpr NE numexpr",
"numexpr : numexpr '&' numexpr",
"numexpr : numexpr '|' numexpr",
"numexpr : numexpr and numexpr",
"numexpr : numexpr or numexpr",
"numexpr : NOT numexpr",
"numexpr : INCR SYMBOL",
"numexpr : SYMBOL INCR",
"numexpr : DECR SYMBOL",
"numexpr : SYMBOL DECR",
"numexpr : numexpr IN numexpr",
"while : WHILE",
"for : FOR",
"else : ELSE",
"cond :",
"cond : numexpr",
"and : AND",
"or : OR",
"blank :",
"blank : blank '\\n'",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 252 "parse.y"
 /* User Subroutines Section */

/*
** Parse a null terminated string and create a program from it (this is the
** parser entry point).  The program created by this routine can be
** executed using ExecuteProgram.  Returns program on success, or NULL
** on failure.  If the command failed, the error message is returned
** as a pointer to a static string in msg, and the length of the string up
** to where parsing failed in stoppedAt.
*/
Program *ParseMacro(char *expr, char **msg, char **stoppedAt)
{
    Program *prog;
    
    BeginCreatingProgram();
    
    /* call yyparse to parse the string and check for success.  If the parse
       failed, return the error message and string index (the grammar aborts
       parsing at the first error) */
    InPtr = expr;
    if (yyparse()) {
    	*msg = ErrMsg;
    	*stoppedAt = InPtr;
    	FreeProgram(FinishCreatingProgram());
    	return NULL;
    }
    
    /* get the newly created program */
    prog = FinishCreatingProgram();
    
    /* parse succeeded */
    *msg = "";
    *stoppedAt = InPtr;
    return prog;
}

static int yylex(void)
{
    int i, len;
    Symbol *s;
    static int stringConstIndex = 0;
    static DataValue value = {0, {0}};
    static char escape[] = "\\\"ntbrfav";
    static char replace[] = "\\\"\n\t\b\r\f\a\v";
    
    /* skip whitespace and backslash-newline combinations which are
       also considered whitespace */
    for (;;) {
    	if (*InPtr == '\\' && *(InPtr + 1) == '\n')
    	    InPtr += 2;
    	else if (*InPtr == ' ' || *InPtr == '\t')
    	    InPtr++;
    	else
    	    break;
    }
    
    /* skip comments */
    if (*InPtr == '#')
    	while (*InPtr != '\n' && *InPtr != '\0') InPtr++;
    
    /* return end of input at the end of the string */
    if (*InPtr == '\0') {
	return 0;
    }
    
    /* process number tokens */
    if (isdigit(*InPtr))  { /* number */
        char name[28];
        sscanf(InPtr, "%d%n", &value.val.n, &len);
        sprintf(name, "const %d", value.val.n);
        InPtr += len;
        value.tag = INT_TAG;
        if ((yylval.sym=LookupSymbol(name)) == NULL)
            yylval.sym = InstallSymbol(name, CONST_SYM, value);
        return NUMBER;
    }
    
    /* process symbol tokens.  "define" is a special case not handled
       by this parser, considered end of input.  Another special case
       is action routine names which are allowed to contain '-' despite
       the ambiguity, handled in matchesActionRoutine. */
    if (isalpha(*InPtr) || *InPtr == '$') {
        if ((s=matchesActionRoutine(&InPtr)) == NULL) {
            char symName[MAX_SYM_LEN+1], *p = symName;
            *p++ = *InPtr++;
            while (isalnum(*InPtr) || *InPtr=='_') {
		if (p >= symName + MAX_SYM_LEN)
		    InPtr++;
		else
		    *p++ = *InPtr++;
	    }
	    *p = '\0';
	    if (!strcmp(symName, "while")) return WHILE;
	    if (!strcmp(symName, "if")) return IF;
	    if (!strcmp(symName, "else")) return ELSE;
	    if (!strcmp(symName, "for")) return FOR;
	    if (!strcmp(symName, "break")) return BREAK;
	    if (!strcmp(symName, "continue")) return CONTINUE;
	    if (!strcmp(symName, "return")) return RETURN;
        if (!strcmp(symName, "in")) return IN;
        if (!strcmp(symName, "delete") && follow_non_whitespace('(', SYMBOL, DELETE) == DELETE) return DELETE;
	    if (!strcmp(symName, "define")) {
	    	InPtr -= 6;
	    	return 0;
	    }
	    if ((s=LookupSymbol(symName)) == NULL) {
        	s = InstallSymbol(symName, symName[0]=='$' ? (isdigit(symName[1]) ?
            		ARG_SYM : GLOBAL_SYM) : LOCAL_SYM, value);
            	s->value.tag = NO_TAG;
            }
	}
	yylval.sym = s;
        return SYMBOL;
    }
    
    /* process quoted strings w/ embedded escape sequences */
    if (*InPtr == '\"') {
        char string[MAX_STRING_CONST_LEN], *p = string;
        char stringName[25];
        InPtr++;
        while (*InPtr != '\0' && *InPtr != '\"' && *InPtr != '\n') {
	    if (p >= string + MAX_STRING_CONST_LEN) {
	    	InPtr++;
	    	continue;
	    }
	    if (*InPtr == '\\') {
		InPtr++;
		if (*InPtr == '\n') {
		    InPtr++;
		    continue;
		}
		for (i=0; escape[i]!='\0'; i++) {
		    if (escape[i] == '\0') {
		    	*p++= *InPtr++;
		    	break;
		    } else if (escape[i] == *InPtr) {
		    	*p++ = replace[i];
		    	InPtr++;
		    	break;
		    }
		}
	    } else
		*p++= *InPtr++;
	}
	*p = '\0';
	InPtr++;
	if ((yylval.sym = LookupStringConstSymbol(string)) == NULL) {
		value.val.str = AllocString(p-string+1);
		strcpy(value.val.str, string);
		value.tag = STRING_TAG;
		sprintf(stringName, "string #%d", stringConstIndex++);
		yylval.sym = InstallSymbol(stringName, CONST_SYM, value);
	}
	return STRING;
    }
    
    /* process remaining two character tokens or return single char as token */
    switch(*InPtr++) {
    case '>':	return follow('=', GE, GT);
    case '<':	return follow('=', LE, LT);
    case '=':	return follow('=', EQ, '=');
    case '!':	return follow('=', NE, NOT);
    case '+':	return follow2('+', INCR, '=', ADDEQ, '+');
    case '-':	return follow2('-', DECR, '=', SUBEQ, '-');
    case '|':	return follow2('|', OR, '=', OREQ, '|');
    case '&':	return follow2('&', AND, '=', ANDEQ, '&');
    case '*':	return follow2('*', POW, '=', MULEQ, '*');
    case '/':   return follow('=', DIVEQ, '/');
    case '%':	return follow('=', MODEQ, '%');
    case '^':	return POW;
    default:	return *(InPtr-1);
    }
}

/*
** look ahead for >=, etc.
*/
static int follow(char expect, int yes, int no)
{
    if (*InPtr++ == expect)
	return yes;
    InPtr--;
    return no;
}
static int follow2(char expect1, int yes1, char expect2, int yes2, int no)
{
    char next = *InPtr++;
    if (next == expect1)
	return yes1;
    if (next == expect2)
    	return yes2;
    InPtr--;
    return no;
}

static int follow_non_whitespace(char expect, int yes, int no)
{
    char *localInPtr = InPtr;
    
    while (1) {
        if (*localInPtr == ' ' || *localInPtr == '\t') {
            ++localInPtr;
        }
        else if (*localInPtr == '\\' && *(localInPtr + 1) == '\n') {
            localInPtr += 2;
        }
        else if (*localInPtr == expect) {
            return(yes);
        }
        else {
            return(no);
        }
    }
}

/*
** Look (way) ahead for hyphenated routine names which begin at inPtr.  A
** hyphenated name is allowed if it is pre-defined in the global symbol
** table.  If a matching name exists, returns the symbol, and update "inPtr".
**
** I know this is horrible language design, but existing nedit action routine
** names contain hyphens.  Handling them here in the lexical analysis process
** is much easier than trying to deal with it in the parser itself.  (sorry)
*/
static Symbol *matchesActionRoutine(char **inPtr)
{
    char *c, *symPtr;
    int hasDash = False;
    char symbolName[MAX_SYM_LEN+1];
    Symbol *s;
    
    symPtr = symbolName;
    for (c = *inPtr; isalnum(*c) || *c=='_' || (*c=='-'&&isalnum(*(c+1))); c++){
    	if (*c == '-')
    	    hasDash = True;
    	*symPtr++ = *c;
    }
    if (!hasDash)
    	return NULL;
    *symPtr = '\0';
    s = LookupSymbol(symbolName);
    if (s != NULL)
    	*inPtr = c;
    return s;
}

/*
** Called by yacc to report errors (just stores for returning when
** parsing is aborted.  The error token action is to immediate abort
** parsing, so this message is immediately reported to the caller
** of ParseExpr)
*/
static int yyerror(char *s)
{
    ErrMsg = s;
    return 0;
}
#line 954 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 77 "parse.y"
{ ADD_OP(OP_RETURN_NO_VAL); return 0; }
break;
case 2:
#line 78 "parse.y"
{ ADD_OP(OP_RETURN_NO_VAL); return 0; }
break;
case 3:
#line 79 "parse.y"
{ ADD_OP(OP_RETURN_NO_VAL); return 0; }
break;
case 4:
#line 80 "parse.y"
{ return 1; }
break;
case 11:
#line 91 "parse.y"
{ SET_BR_OFF(yyvsp[-3].inst, GetPC()); }
break;
case 12:
#line 93 "parse.y"
{ SET_BR_OFF(yyvsp[-6].inst, (yyvsp[-2].inst+1)); SET_BR_OFF(yyvsp[-2].inst, GetPC()); }
break;
case 13:
#line 94 "parse.y"
{ ADD_OP(OP_BRANCH); ADD_BR_OFF(yyvsp[-5].inst);
                SET_BR_OFF(yyvsp[-3].inst, GetPC()); FillLoopAddrs(GetPC(), yyvsp[-5].inst); }
break;
case 14:
#line 97 "parse.y"
{ FillLoopAddrs(GetPC()+2+(yyvsp[-3].inst-(yyvsp[-5].inst+1)), GetPC());
    	          SwapCode(yyvsp[-5].inst+1, yyvsp[-3].inst, GetPC());
    	          ADD_OP(OP_BRANCH); ADD_BR_OFF(yyvsp[-7].inst); SET_BR_OFF(yyvsp[-5].inst, GetPC()); }
break;
case 15:
#line 101 "parse.y"
{ Symbol *iterSym = InstallIteratorSymbol();
                  ADD_OP(OP_BEGIN_ARRAY_ITER); ADD_SYM(yyvsp[-1].sym); ADD_SYM(iterSym);
                  ADD_OP(OP_ARRAY_ITER); ADD_SYM(yyvsp[-3].sym); ADD_SYM(iterSym);
                  ADD_BR_OFF(0); }
break;
case 16:
#line 106 "parse.y"
{ FillLoopAddrs(GetPC()+2, GetPC());
                  ADD_OP(OP_BRANCH); ADD_BR_OFF(yyvsp[-8].inst+3);
                  SET_BR_OFF(yyvsp[-8].inst+6, GetPC());}
break;
case 17:
#line 110 "parse.y"
{ ADD_OP(OP_BRANCH); ADD_BR_OFF(0); AddBreakAddr(GetPC()-1); }
break;
case 18:
#line 112 "parse.y"
{ ADD_OP(OP_BRANCH); ADD_BR_OFF(0); AddContinueAddr(GetPC()-1); }
break;
case 19:
#line 113 "parse.y"
{ ADD_OP(OP_RETURN); }
break;
case 20:
#line 114 "parse.y"
{ ADD_OP(OP_RETURN_NO_VAL); }
break;
case 21:
#line 116 "parse.y"
{ ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-2].sym); }
break;
case 22:
#line 117 "parse.y"
{ ADD_OP(OP_ADD); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-2].sym); }
break;
case 23:
#line 118 "parse.y"
{ ADD_OP(OP_SUB); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-2].sym); }
break;
case 24:
#line 119 "parse.y"
{ ADD_OP(OP_MUL); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-2].sym); }
break;
case 25:
#line 120 "parse.y"
{ ADD_OP(OP_DIV); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-2].sym); }
break;
case 26:
#line 121 "parse.y"
{ ADD_OP(OP_MOD); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-2].sym); }
break;
case 27:
#line 122 "parse.y"
{ ADD_OP(OP_BIT_AND); ADD_OP(OP_ASSIGN);
    	    	ADD_SYM(yyvsp[-2].sym); }
break;
case 28:
#line 124 "parse.y"
{ ADD_OP(OP_BIT_OR); ADD_OP(OP_ASSIGN);
    	    	ADD_SYM(yyvsp[-2].sym); }
break;
case 29:
#line 127 "parse.y"
{ ADD_OP(OP_ARRAY_DELETE); ADD_SYM(yyvsp[-3].sym); ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 30:
#line 129 "parse.y"
{ ADD_OP(OP_ARRAY_ASSIGN); ADD_SYM(yyvsp[-5].sym); ADD_IMMED((void *)yyvsp[-3].nArgs); }
break;
case 31:
#line 130 "parse.y"
{ ADD_OP(OP_PUSH_SYM);
                ADD_SYM(yyvsp[-3].sym); ADD_OP(OP_ARRAY_REF); ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 32:
#line 133 "parse.y"
{ ADD_OP(OP_ADD); ADD_OP(OP_ARRAY_ASSIGN); ADD_SYM(yyvsp[-6].sym);
                  ADD_IMMED((void *)yyvsp[-4].nArgs);}
break;
case 33:
#line 135 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-3].sym);
                  ADD_OP(OP_ARRAY_REF); ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 34:
#line 138 "parse.y"
{ ADD_OP(OP_SUB); ADD_OP(OP_ARRAY_ASSIGN); ADD_SYM(yyvsp[-6].sym);
                  ADD_IMMED((void *)yyvsp[-4].nArgs); }
break;
case 35:
#line 141 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-3].sym); ADD_OP(OP_ARRAY_REF);
                  ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 36:
#line 144 "parse.y"
{ ADD_OP(OP_MUL); ADD_OP(OP_ARRAY_ASSIGN); ADD_SYM(yyvsp[-6].sym);
                  ADD_IMMED((void *)yyvsp[-4].nArgs); }
break;
case 37:
#line 147 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-3].sym); ADD_OP(OP_ARRAY_REF);
                  ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 38:
#line 150 "parse.y"
{ ADD_OP(OP_DIV); ADD_OP(OP_ARRAY_ASSIGN); ADD_SYM(yyvsp[-6].sym);
                  ADD_IMMED((void *)yyvsp[-4].nArgs); }
break;
case 39:
#line 153 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-3].sym); ADD_OP(OP_ARRAY_REF);
                  ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 40:
#line 156 "parse.y"
{ ADD_OP(OP_MOD); ADD_OP(OP_ARRAY_ASSIGN); ADD_SYM(yyvsp[-6].sym);
                  ADD_IMMED((void *)yyvsp[-4].nArgs); }
break;
case 41:
#line 159 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-3].sym); ADD_OP(OP_ARRAY_REF);
                  ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 42:
#line 162 "parse.y"
{ ADD_OP(OP_BIT_AND); ADD_OP(OP_ARRAY_ASSIGN);
                ADD_SYM(yyvsp[-6].sym); ADD_IMMED((void *)yyvsp[-4].nArgs); }
break;
case 43:
#line 165 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-3].sym); ADD_OP(OP_ARRAY_REF);
                  ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 44:
#line 168 "parse.y"
{ ADD_OP(OP_BIT_OR); ADD_OP(OP_ARRAY_ASSIGN);
                  ADD_SYM(yyvsp[-6].sym); ADD_IMMED((void *)yyvsp[-4].nArgs); }
break;
case 45:
#line 170 "parse.y"
{ ADD_OP(OP_SUBR_CALL);
                ADD_SYM(PromoteToGlobal(yyvsp[-3].sym)); ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 46:
#line 172 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); ADD_OP(OP_INCR);
                ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[0].sym); }
break;
case 47:
#line 174 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-1].sym); ADD_OP(OP_INCR);
                ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-1].sym); }
break;
case 48:
#line 176 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); ADD_OP(OP_DECR);
                ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[0].sym); }
break;
case 49:
#line 178 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-1].sym); ADD_OP(OP_DECR);
                ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-1].sym); }
break;
case 50:
#line 181 "parse.y"
{ yyval.sym = yyvsp[0].sym; ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); }
break;
case 51:
#line 183 "parse.y"
{ yyval.inst = GetPC(); }
break;
case 52:
#line 184 "parse.y"
{ yyval.inst = GetPC(); }
break;
case 53:
#line 185 "parse.y"
{ yyval.inst = GetPC(); }
break;
case 54:
#line 187 "parse.y"
{ yyval.nArgs = 0;}
break;
case 55:
#line 188 "parse.y"
{ yyval.nArgs = 1; }
break;
case 56:
#line 189 "parse.y"
{ yyval.nArgs = yyvsp[-2].nArgs + 1; }
break;
case 58:
#line 192 "parse.y"
{ ADD_OP(OP_CONCAT); }
break;
case 59:
#line 194 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); }
break;
case 60:
#line 195 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); }
break;
case 61:
#line 196 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); }
break;
case 62:
#line 197 "parse.y"
{ ADD_OP(OP_SUBR_CALL);
	    	ADD_SYM(PromoteToGlobal(yyvsp[-3].sym)); ADD_IMMED((void *)yyvsp[-1].nArgs);
		ADD_OP(OP_FETCH_RET_VAL);}
break;
case 64:
#line 202 "parse.y"
{ ADD_OP(OP_ARRAY_REF); ADD_IMMED((void *)yyvsp[-1].nArgs); }
break;
case 65:
#line 203 "parse.y"
{ ADD_OP(OP_ADD); }
break;
case 66:
#line 204 "parse.y"
{ ADD_OP(OP_SUB); }
break;
case 67:
#line 205 "parse.y"
{ ADD_OP(OP_MUL); }
break;
case 68:
#line 206 "parse.y"
{ ADD_OP(OP_DIV); }
break;
case 69:
#line 207 "parse.y"
{ ADD_OP(OP_MOD); }
break;
case 70:
#line 208 "parse.y"
{ ADD_OP(OP_POWER); }
break;
case 71:
#line 209 "parse.y"
{ ADD_OP(OP_NEGATE); }
break;
case 72:
#line 210 "parse.y"
{ ADD_OP(OP_GT); }
break;
case 73:
#line 211 "parse.y"
{ ADD_OP(OP_GE); }
break;
case 74:
#line 212 "parse.y"
{ ADD_OP(OP_LT); }
break;
case 75:
#line 213 "parse.y"
{ ADD_OP(OP_LE); }
break;
case 76:
#line 214 "parse.y"
{ ADD_OP(OP_EQ); }
break;
case 77:
#line 215 "parse.y"
{ ADD_OP(OP_NE); }
break;
case 78:
#line 216 "parse.y"
{ ADD_OP(OP_BIT_AND); }
break;
case 79:
#line 217 "parse.y"
{ ADD_OP(OP_BIT_OR); }
break;
case 80:
#line 219 "parse.y"
{ ADD_OP(OP_AND); SET_BR_OFF(yyvsp[-1].inst, GetPC()); }
break;
case 81:
#line 221 "parse.y"
{ ADD_OP(OP_OR); SET_BR_OFF(yyvsp[-1].inst, GetPC()); }
break;
case 82:
#line 222 "parse.y"
{ ADD_OP(OP_NOT); }
break;
case 83:
#line 223 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); ADD_OP(OP_INCR);
    	    	ADD_OP(OP_DUP); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[0].sym); }
break;
case 84:
#line 225 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-1].sym); ADD_OP(OP_DUP);
	    	ADD_OP(OP_INCR); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-1].sym); }
break;
case 85:
#line 227 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[0].sym); ADD_OP(OP_DECR);
	    	ADD_OP(OP_DUP); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[0].sym); }
break;
case 86:
#line 229 "parse.y"
{ ADD_OP(OP_PUSH_SYM); ADD_SYM(yyvsp[-1].sym); ADD_OP(OP_DUP);
	    	ADD_OP(OP_DECR); ADD_OP(OP_ASSIGN); ADD_SYM(yyvsp[-1].sym); }
break;
case 87:
#line 231 "parse.y"
{ ADD_OP(OP_IN_ARRAY); }
break;
case 88:
#line 233 "parse.y"
{ yyval.inst = GetPC(); StartLoopAddrList(); }
break;
case 89:
#line 235 "parse.y"
{ StartLoopAddrList(); yyval.inst = GetPC(); }
break;
case 90:
#line 237 "parse.y"
{ ADD_OP(OP_BRANCH); yyval.inst = GetPC(); ADD_BR_OFF(0); }
break;
case 91:
#line 239 "parse.y"
{ ADD_OP(OP_BRANCH_NEVER); yyval.inst = GetPC(); ADD_BR_OFF(0); }
break;
case 92:
#line 240 "parse.y"
{ ADD_OP(OP_BRANCH_FALSE); yyval.inst = GetPC(); ADD_BR_OFF(0); }
break;
case 93:
#line 242 "parse.y"
{ ADD_OP(OP_DUP); ADD_OP(OP_BRANCH_FALSE); yyval.inst = GetPC();
    	    	ADD_BR_OFF(0); }
break;
case 94:
#line 245 "parse.y"
{ ADD_OP(OP_DUP); ADD_OP(OP_BRANCH_TRUE); yyval.inst = GetPC();
    	    	ADD_BR_OFF(0); }
break;
#line 1530 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
