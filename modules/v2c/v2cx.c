/*  A Bison parser, made from y.v2cx  */

#define	USE	258
#define	LIBRARY	259
#define	GENERIC	260
#define	TYPE	261
#define	PROCEDURE	262
#define	FUNCTION	263
#define	ASSERT	264
#define	CONSTANT	265
#define	COMPONENT	266
#define	FIL	267
#define	ALIAS	268
#define	ATTRIBUTE_STAT	269
#define	DISCONNECT	270
#define	INOUT	271
#define	ENTITY	272
#define	IS	273
#define	PORT	274
#define	END	275
#define	IN	276
#define	OUT	277
#define	BIT	278
#define	STD_ULOGIC_VECTOR	279
#define	INTEGER	280
#define	RANGE	281
#define	STD_ULOGIC	282
#define	QSIM_STATE	283
#define	ARCHITECTURE	284
#define	OF	285
#define	SIGNAL	286
#define	BEGN	287
#define	NOT	288
#define	AFTER	289
#define	UNIT	290
#define	NAME	291
#define	TO	292
#define	DOWNTO	293
#define	STRING	294
#define	NATURAL	295
#define	AND	296
#define	OR	297
#define	XOR	298
#define	WHEN	299
#define	ELSE	300
#define	WITH	301
#define	SELECT	302
#define	OTHERS	303
#define	BLOCK	304
#define	PROCESS	305
#define	VARIABLE	306
#define	IF	307
#define	THEN	308
#define	ELSIF	309
#define	CASE	310
#define	LOOP	311
#define	WHILE	312
#define	FOR	313
#define	NEXT	314
#define	EXIT	315
#define	WAIT	316
#define	UNTIL	317
#define	ON	318
#define	CLKEXPR	319
#define	LASTVALUE	320
#define	EVENT	321
#define	ORL	322
#define	ANDL	323
#define	BIGEQ	324
#define	LESSEQ	325
#define	NOTEQ	326
#define	EQUAL	327
#define	UNARYMINUS	328
#define	UNARYPLUS	329
#define	NOTL	330

#line 4 "y.v2cx"

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "procs.h"
#include "versionx.h"
#include "match.h"

BOOL process_present;
BOOL seq_flag;
int seq_tot, comb_tot;
BOOL processing_process;
BOOL elsefound; /* 'else' part of 'if' statement */
BOOL clk_in_sensi=FALSE; /* clock found in sensitivity list */
int clkcount=0; /* number of "clock expressions" in one 'if' or 'wait' or blockguard */
BOOL firstline=TRUE; /* First line in a process */
BOOL waitclk=FALSE; /* Clock present in wait statement */

fromto dummyft;

extern char sigprefix[1024];
extern int lineno;

signal **procsig=NULL;
int procsigcount=0;
signal **sensisig=NULL;
int sensisigcount=0;

static BOOL isclock(char *str);
static char *clockstr=NULL;


#line 36 "y.v2cx"
typedef union { /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
       char * txt;  /* String */
       int n;       /* Value  */
       expdata * e; /* For expressions */
       sigdata * s; /* For signals     */
       } YYSTYPE;


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif


#ifndef YYDEBUG
#define YYDEBUG 0
#endif

#include <stdio.h>
#ifdef __STDC__
#include <stdlib.h>
#endif

#ifndef __STDC__
#define const
#endif

#define	YYFINAL		350
#define	YYFLAG		-32768
#define	YYNTBASE	91

#define YYTRANSLATE(x) ((unsigned)(x) <= 330 ? yytranslate[x] : 152)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    80,    89,    85,
    86,    78,    76,    88,    77,     2,    79,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    87,    84,    70,
    67,    71,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    90,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    68,    69,    72,    73,    74,    75,    81,    82,    83
};

#if YYDEBUG != 0
static const short yyrline[] = {     0,
    87,    92,    93,    94,    95,    96,    97,    98,    99,   100,
   101,   102,   103,   104,   105,   106,   109,   118,   119,   121,
   122,   124,   125,   127,   129,   130,   131,   132,   134,   135,
   136,   137,   141,   142,   144,   149,   154,   158,   162,   163,
   165,   166,   169,   170,   172,   173,   174,   175,   176,   179,
   213,   232,   233,   234,   235,   236,   237,   238,   239,   240,
   241,   242,   243,   244,   245,   246,   247,   254,   259,   267,
   268,   269,   270,   271,   272,   273,   281,   282,   283,   284,
   285,   286,   287,   288,   294,   296,   297,   299,   301,   302,
   303,   305,   306,   312,   314,   315,   316,   319,   329,   336,
   337,   339,   340,   350,   352,   358,   413,   426,   437,   438,
   441,   442,   445,   458,   474,   475,   476,   477,   478,   479,
   480,   481,   484,   487,   492,   493,   497,   498,   502,   503,
   504,   505,   506,   507,   508,   509,   512,   520,   530,   531,
   532,   534,   536,   553,   557,   559,   560,   561,   568,   569,
   573,   575,   576,   578,   579,   580,   582,   583,   587,   591,
   595,   597,   606,   611,   619
};

static const char * const yytname[] = {     0,
"error","$illegal.","USE","LIBRARY","GENERIC","TYPE","PROCEDURE","FUNCTION","ASSERT","CONSTANT",
"COMPONENT","FIL","ALIAS","ATTRIBUTE_STAT","DISCONNECT","INOUT","ENTITY","IS","PORT","END",
"IN","OUT","BIT","STD_ULOGIC_VECTOR","INTEGER","RANGE","STD_ULOGIC","QSIM_STATE","ARCHITECTURE","OF",
"SIGNAL","BEGN","NOT","AFTER","UNIT","NAME","TO","DOWNTO","STRING","NATURAL",
"AND","OR","XOR","WHEN","ELSE","WITH","SELECT","OTHERS","BLOCK","PROCESS",
"VARIABLE","IF","THEN","ELSIF","CASE","LOOP","WHILE","FOR","NEXT","EXIT",
"WAIT","UNTIL","ON","CLKEXPR","LASTVALUE","EVENT","'='","ORL","ANDL","'<'",
"'>'","BIGEQ","LESSEQ","NOTEQ","EQUAL","'+'","'-'","'*'","'/'","'&'",
"UNARYMINUS","UNARYPLUS","NOTL","';'","'('","')'","':'","','","'\\''","'|'",
"trad"
};
#endif

static const short yyr1[] = {     0,
    91,    92,    92,    93,    93,    93,    93,    93,    93,    93,
    93,    93,    93,    93,    93,    93,    94,    95,    95,    96,
    96,    97,    97,    98,    99,    99,    99,    99,   100,   100,
   100,   100,   100,   100,   101,   101,   101,   102,   103,   103,
   104,   104,   105,   105,   106,   106,   106,   106,   106,   107,
   107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
   107,   107,   107,   107,   107,   107,   107,   108,   108,   109,
   109,   109,   109,   109,   109,   109,   110,   110,   110,   110,
   110,   110,   110,   110,   111,   112,   112,   113,   114,   114,
   114,   115,   115,   116,   117,   117,   117,   118,   119,   120,
   120,   121,   121,   122,   123,   124,   125,   125,   126,   126,
   127,   127,   128,   128,   129,   129,   129,   129,   129,   129,
   129,   129,   130,   130,   131,   131,   132,   132,   133,   133,
   133,   133,   133,   133,   133,   133,   134,   135,   136,   136,
   136,   137,   138,   138,   139,   140,   140,   140,   141,   141,
   142,   143,   143,   144,   145,   145,   146,   146,   147,   148,
   149,   150,   150,   151,   151
};

static const short yyr2[] = {     0,
     2,     0,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     8,     1,     7,     3,
     5,     1,     3,     2,     1,     1,     1,     1,     1,     1,
     1,     4,     1,     5,     3,     1,     3,    11,     1,     7,
     0,     3,     1,     2,     1,     1,     1,     1,     1,     1,
     4,     1,     3,     1,     3,     2,     2,     3,     3,     3,
     3,     2,     3,     3,     3,     3,     3,     1,     1,     1,
     3,     3,     3,     2,     2,     3,     3,     3,     4,     3,
     4,     4,     1,     6,     4,     1,     4,     1,     3,     5,
     6,     0,     3,     7,     4,     4,     5,    10,     2,     0,
     1,     0,     3,     1,     1,    10,     0,     2,     0,     1,
     0,     3,     1,     3,     0,     7,     2,     2,     2,     2,
     2,     2,     1,     3,     0,     3,     1,     2,     1,     1,
     1,     1,     1,     1,     1,     1,     5,     8,     0,     5,
     2,     1,     1,     1,     7,     0,     6,     5,     1,     3,
     8,     0,     2,     1,     2,     6,     1,     1,     2,     2,
     3,     2,     2,     1,     3
};

static const short yydefact[] = {     2,
     4,     5,     6,     7,     9,    10,    11,     8,    16,    12,
    13,    14,    15,     0,     2,     0,     0,     3,     0,     1,
     0,     0,     2,     0,    18,     0,     0,     0,     0,     2,
     0,     0,     0,    39,     0,    22,     0,     0,    17,     0,
   107,     0,     0,     0,     0,    49,    88,     0,     0,    43,
    45,     0,    86,    46,    47,     0,    48,     0,     2,    28,
    27,    25,    26,    20,     0,    23,    29,     0,    33,    31,
    30,    41,    99,     0,    50,    54,    52,     0,     0,     0,
     0,     0,     0,     0,    44,     0,     0,   102,   111,    19,
     0,    24,     0,     0,     0,     0,    62,     0,    57,    56,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    36,     0,     0,     2,     0,   115,
    21,     0,     0,     0,     2,    67,    66,    53,    63,    64,
    65,    88,     0,    58,    59,    60,    61,    55,     0,    38,
    92,    85,     0,     0,    87,     0,    50,    83,     0,     0,
     0,    70,   104,     0,   113,     0,   115,   115,   115,   115,
   115,   115,     0,     0,    32,     0,    42,    40,     0,    51,
     0,     0,    37,    35,    62,    74,     0,    68,    69,    75,
     0,     0,     0,     0,     0,     0,     0,   103,   107,   112,
     0,   117,   122,   121,   118,   119,   120,   123,     0,   152,
    34,     0,     0,     0,    89,    76,     0,    71,    77,     0,
     0,    80,     0,    78,    72,    73,   105,     0,   114,     0,
     0,    88,     0,     0,     0,     0,     0,   129,     0,   127,
   130,   131,   132,   133,     0,   134,   135,   136,     0,    94,
    93,     0,     0,    81,    82,    79,     0,   124,   125,   153,
   142,   143,   144,     0,   142,     0,   159,   160,     0,     0,
     0,     0,   128,     0,     0,     0,     0,     0,    90,     0,
   100,     0,     0,     0,   152,   146,   162,   164,   163,   161,
   109,   155,     0,   152,     0,     0,    91,    84,   101,     0,
     0,   115,     0,   139,     0,     0,     0,   110,     0,     0,
     0,    96,    95,     0,    98,   126,   116,   137,   152,     0,
     0,     0,   149,     0,     0,   165,   106,     0,     0,    97,
   141,     0,     0,     0,     0,     0,     0,   157,   158,     0,
   109,   152,     0,   152,   150,   152,   145,   156,   154,     0,
   139,   138,   148,   146,   151,   140,   147,     0,     0,     0
};

static const short yydefgoto[] = {   348,
    34,    15,    16,    26,    37,    38,    64,    65,    72,   116,
    20,    35,    96,    49,    50,   255,   180,   252,   152,   228,
    52,    83,   142,   172,    54,   240,    55,    56,   290,   118,
   154,   218,    57,    58,   299,   120,   156,   164,   199,   273,
   229,   230,   231,   232,   311,   253,   254,   233,   296,   314,
   234,   235,   340,   266,   330,   236,   237,   238,   261,   279
};

static const short yypact[] = {   445,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    -9,   445,    12,     8,-32768,    15,-32768,
    65,    71,   445,    76,   100,   102,   111,    61,   113,   396,
   117,    81,   117,-32768,   135,-32768,    89,    16,-32768,    27,
    75,    97,   112,   152,   285,-32768,   105,   222,   178,   108,
-32768,   129,   123,-32768,-32768,   160,-32768,   166,   445,-32768,
-32768,-32768,-32768,   126,   285,-32768,-32768,   137,   185,-32768,
-32768,   143,   168,   222,   -39,-32768,-32768,   222,   222,   222,
   191,   318,   140,   199,-32768,   172,   200,   157,   162,-32768,
   117,-32768,   200,   209,   186,   170,-32768,   194,-32768,-32768,
   127,   175,   222,   222,   222,   229,   222,   222,   222,   222,
   222,   200,   182,   222,    59,   181,   138,   396,   229,   173,
-32768,   190,   240,   222,   396,-32768,-32768,-32768,   207,    30,
   195,-32768,   220,    63,    63,-32768,-32768,-32768,   206,-32768,
    47,-32768,   254,   256,-32768,   138,     6,    66,   138,   278,
   -31,-32768,-32768,   268,-32768,   -34,   173,   173,   173,   173,
   173,   173,   269,   274,-32768,   283,   301,-32768,   257,-32768,
   287,   -18,-32768,-32768,-32768,-32768,    96,-32768,-32768,   258,
   261,   -17,   222,     9,   161,   138,   138,-32768,    75,-32768,
   229,-32768,-32768,-32768,-32768,-32768,-32768,   241,   243,   386,
-32768,   222,   311,   138,-32768,-32768,   262,-32768,   307,   222,
   222,   307,   222,   307,   131,   131,-32768,   332,-32768,   269,
   285,   266,   138,   222,   279,   280,   121,-32768,   342,   376,
-32768,-32768,-32768,-32768,   133,-32768,-32768,-32768,   292,-32768,
-32768,    -2,   326,   307,   307,   307,   324,-32768,   288,   300,
   278,   131,-32768,   321,   301,   358,-32768,-32768,   138,   229,
   298,   338,-32768,   138,   353,   334,   193,   222,-32768,   302,
   356,   346,   309,   222,   386,   370,   131,-32768,   327,-32768,
   380,-32768,   397,   386,   333,   238,-32768,-32768,-32768,   335,
   222,   173,   336,    -7,   212,   401,   229,-32768,   339,   222,
   404,-32768,-32768,   222,-32768,   301,-32768,-32768,   386,   138,
   405,   359,   340,   362,   377,-32768,-32768,   158,   383,-32768,
-32768,   387,   390,   372,   222,   373,   378,-32768,-32768,   222,
   380,   386,   379,   386,-32768,   386,-32768,-32768,-32768,   381,
    -7,-32768,-32768,   370,-32768,-32768,-32768,   461,   464,-32768
};

static const short yypgoto[] = {-32768,
    13,-32768,-32768,   407,   382,   434,-32768,-32768,   -61,   -77,
-32768,   -95,-32768,   -44,-32768,   -47,-32768,  -112,-32768,   -38,
  -104,   -41,   201,-32768,-32768,   164,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   139,-32768,-32768,  -140,   251,-32768,
  -216,-32768,-32768,-32768,   134,  -195,  -257,-32768,   128,   149,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768
};


#define	YYLAST		475


static const short yytable[] = {    53,
    82,   133,    51,    92,   151,    85,   282,    17,    53,   186,
   187,    51,    14,   263,   155,   122,   192,   193,   194,   195,
   196,   197,   153,   186,   187,   204,    97,    18,   256,   168,
    99,   100,   101,   176,   139,    25,   182,   309,   186,   187,
    19,    74,   268,    21,    75,   -88,   310,    76,    77,    98,
    22,   190,   322,   191,   188,   129,   130,   131,   294,   134,
   135,   136,   137,   138,    53,   205,   141,   301,   208,   150,
   103,    25,   105,   215,   216,   210,   167,    53,   293,   211,
   171,   269,    23,    46,    78,    79,   219,   103,   104,   105,
   -88,   242,   321,    80,   177,   143,   144,    81,   175,   313,
    24,   181,    43,    44,   318,   107,   108,   109,   110,   111,
    47,    27,    60,    45,    44,   341,    46,   343,    28,   344,
    48,    29,   107,   108,   109,   110,   111,    61,    30,   313,
   178,   179,    62,    63,   338,   209,   212,   214,   150,   150,
   109,   110,   111,    47,   217,    31,   277,    53,    32,    53,
    51,   307,    36,    48,   239,   278,   150,  -107,    53,   249,
   126,   206,   244,   245,    39,   246,    41,   103,   104,   105,
   146,   186,   187,   147,    42,   251,    76,    77,   157,   158,
    59,   159,   259,   260,   160,   161,   162,    66,    53,   264,
   265,    73,   316,    74,   328,   329,    75,    84,    86,    76,
    77,   148,   107,   108,   109,   110,   111,    87,    88,    91,
    94,   150,   127,    78,    79,    89,   251,  -108,    53,   286,
   141,    93,   149,   163,   112,    74,    81,   213,    75,    95,
   102,    76,    77,    53,   113,   103,    78,    79,   114,   115,
   285,   117,    53,   306,    74,    80,   119,    75,   123,    81,
    76,    77,   124,   125,    74,    53,   239,    75,   126,   312,
    76,    77,   251,   128,   132,   140,   145,    53,    78,    79,
   107,   108,   109,   110,   111,   165,   166,    80,   103,   104,
   105,    81,   107,   108,   109,   110,   111,    78,    79,   169,
    53,   170,    53,   173,    53,   174,    80,    78,    79,   189,
    81,   103,   104,   105,   198,   200,    80,    67,    68,    69,
    81,    70,    71,   107,   108,   109,   110,   111,   103,   104,
   105,   303,   201,   202,   207,   304,   203,   183,   220,   221,
   184,   185,   103,   104,   105,   267,   107,   108,   109,   110,
   111,   103,   104,   105,   183,   241,   127,   184,   185,   105,
   243,   247,   250,   107,   108,   109,   110,   111,   103,   104,
   105,   262,   257,   258,   106,   270,   274,   107,   108,   109,
   110,   111,   271,   275,   272,   276,   107,   108,   109,   110,
   111,   280,   107,   108,   109,   110,   111,   281,   283,   284,
   288,   289,   292,   107,   108,   109,   110,   111,     1,     2,
     3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
    13,   222,   291,   295,   297,   298,   302,   300,   305,   308,
   315,   222,   317,   319,   323,   324,    33,   223,   326,   325,
   224,   327,  -152,  -152,   225,   226,   227,   223,   331,   332,
   224,   333,   334,   336,   225,   226,   227,     1,     2,     3,
     4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
   349,   337,   342,   350,   345,    90,    40,   320,   287,   339,
   248,   347,   121,   335,   346
};

static const short yycheck[] = {    41,
    48,   106,    41,    65,   117,    50,   264,    17,    50,    41,
    42,    50,     0,   230,   119,    93,   157,   158,   159,   160,
   161,   162,   118,    41,    42,    44,    74,    15,   224,   125,
    78,    79,    80,   146,   112,    23,   149,    45,    41,    42,
    29,    33,    45,    36,    36,    85,    54,    39,    40,    89,
    36,    86,   310,    88,    86,   103,   104,   105,   275,   107,
   108,   109,   110,   111,   106,    84,   114,   284,    86,   117,
    41,    59,    43,   186,   187,    67,   124,   119,   274,    71,
    34,    84,    18,     9,    76,    77,   191,    41,    42,    43,
    85,   204,   309,    85,    89,    37,    38,    89,   146,   295,
    30,   149,    87,    88,   300,    76,    77,    78,    79,    80,
    36,    36,     1,    87,    88,   332,     9,   334,    19,   336,
    46,    20,    76,    77,    78,    79,    80,    16,    18,   325,
    65,    66,    21,    22,   330,   183,   184,   185,   186,   187,
    78,    79,    80,    36,   189,    85,   259,   189,    36,   191,
   189,   292,    36,    46,   202,   260,   204,    50,   200,   221,
    65,    66,   210,   211,    84,   213,    32,    41,    42,    43,
    33,    41,    42,    36,    86,   223,    39,    40,     6,     7,
    84,     9,    62,    63,    12,    13,    14,    36,   230,    57,
    58,    87,   297,    33,    37,    38,    36,    20,    70,    39,
    40,    64,    76,    77,    78,    79,    80,    85,    49,    84,
    26,   259,    86,    76,    77,    50,   264,    50,   260,   267,
   268,    85,    85,    51,    85,    33,    89,    67,    36,    87,
    40,    39,    40,   275,    36,    41,    76,    77,    67,    40,
    48,    85,   284,   291,    33,    85,    85,    36,    40,    89,
    39,    40,    67,    84,    33,   297,   304,    36,    65,    48,
    39,    40,   310,    89,    36,    84,    86,   309,    76,    77,
    76,    77,    78,    79,    80,    86,    37,    85,    41,    42,
    43,    89,    76,    77,    78,    79,    80,    76,    77,    70,
   332,    86,   334,    40,   336,    40,    85,    76,    77,    32,
    89,    41,    42,    43,    36,    32,    85,    23,    24,    25,
    89,    27,    28,    76,    77,    78,    79,    80,    41,    42,
    43,    84,    40,    67,    67,    88,    40,    67,    88,    87,
    70,    71,    41,    42,    43,    44,    76,    77,    78,    79,
    80,    41,    42,    43,    67,    35,    86,    70,    71,    43,
    89,    20,    87,    76,    77,    78,    79,    80,    41,    42,
    43,    20,    84,    84,    47,    40,    67,    76,    77,    78,
    79,    80,    49,    53,    87,    18,    76,    77,    78,    79,
    80,    84,    76,    77,    78,    79,    80,    50,    36,    56,
    89,    36,    84,    76,    77,    78,    79,    80,     3,     4,
     5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    36,    67,    44,    88,    36,    84,    21,    84,    84,
    20,    36,    84,    20,    20,    67,    31,    52,    67,    90,
    55,    55,    57,    58,    59,    60,    61,    52,    56,    53,
    55,    52,    71,    71,    59,    60,    61,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     0,    84,    84,     0,    84,    59,    33,   304,   268,   331,
   220,   344,    91,   325,   341
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984 Bob Corbett and Richard Stallman

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

/* ------------------------ */
/* Questo l'ho aggiunto io: */
#ifdef __STDC__
  void yyerror(char *s);
  int yylex(void);
#endif
/* ------------------------ */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYFAIL		goto yyerrlab;
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYIMPURE
#define YYLEX		yylex()
#endif

#ifndef YYPURE
#define YYLEX		yylex(&yylval, &yylloc)
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYIMPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/

int yynerrs;			/*  number of parse errors so far       */
#endif  /* YYIMPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYMAXDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYMAXDEPTH
#define YYMAXDEPTH 200
#endif

/*  YYMAXLIMIT is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#ifndef YYMAXLIMIT
#define YYMAXLIMIT 10000
#endif


#line 86 "bison.simple"
int
yyparse()
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1;		/*  lookahead token as an internal (translated) token number */

  /*  yyss: the state stack			*/
  /*  yyvs: the semantic value stack		*/
  /*  yyls: the location stack			*/

  short   *yyss = (short *)   malloc(YYMAXDEPTH * sizeof(short));
  YYSTYPE *yyvs = (YYSTYPE *) malloc(YYMAXDEPTH * sizeof(YYSTYPE));

#ifdef YYLSP_NEEDED
  YYLTYPE *yyls = (YYLTYPE *) malloc(YYMAXDEPTH * sizeof(YYLTYPE));
  YYLTYPE *yylsp;
#endif

  int yymaxdepth = YYMAXDEPTH;

#ifndef YYPURE
  int yychar;
  YYSTYPE yylval;
  YYLTYPE yylloc;
  int yynerrs;
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;

#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate.  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yymaxdepth - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;

#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
      int yylssz = size * sizeof (*yylsp);
#else
      void *yyls1 = NULL;
      int yylssz = 0;
#endif

      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, yylssz,
		 &yymaxdepth);

      yyss = yyss1; yyvs = yyvs1;

#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif

#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yymaxdepth >= YYMAXLIMIT)
	yyerror("parser stack overflow");
      yymaxdepth *= 2;
      if (yymaxdepth > YYMAXLIMIT)
	yymaxdepth = YYMAXLIMIT;
      yyss = (short *)   realloc (yyss, yymaxdepth * sizeof (*yyssp));
      if (yyss == 0)
	yyerror("parser stack overflow");
      yyvs = (YYSTYPE *) realloc (yyvs, yymaxdepth * sizeof (*yyvsp));
      if (yyvs == 0)
	yyerror("parser stack overflow");

#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) realloc (yyls, yymaxdepth * sizeof (*yylsp));
      if (yyls == 0)
	yyerror("parser stack overflow");
#endif

#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yymaxdepth);
#endif

      if (yyssp >= yyss + yymaxdepth - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Next token is %d (%s)\n", yychar, yytname[yychar1]);
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    if (yychar)
       fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      if (yylen == 1)
	fprintf (stderr, "Reducing 1 value via line %d, ",
		 yyrline[yyn]);
      else
	fprintf (stderr, "Reducing %d values via line %d, ",
		 yylen, yyrline[yyn]);
    }
#endif


  switch (yyn) {

case 4:
#line 94 "y.v2cx"
{ warning("'use' statement ignored"); ;
    break;}
case 5:
#line 95 "y.v2cx"
{ warning("'library' statement ignored"); ;
    break;}
case 6:
#line 96 "y.v2cx"
{ warning("'generic' statement ignored"); ;
    break;}
case 7:
#line 97 "y.v2cx"
{ warning("'type' statement ignored"); ;
    break;}
case 8:
#line 98 "y.v2cx"
{ warning("'constant' statement ignored"); ;
    break;}
case 9:
#line 99 "y.v2cx"
{ warning("'procedure' statement illegal"); ;
    break;}
case 10:
#line 100 "y.v2cx"
{ warning("'function' statement illegal"); ;
    break;}
case 11:
#line 101 "y.v2cx"
{ warning("'assert' statement illegal"); ;
    break;}
case 12:
#line 102 "y.v2cx"
{ warning("'file' statement ignored"); ;
    break;}
case 13:
#line 103 "y.v2cx"
{ warning("'alias' statement ignored"); ;
    break;}
case 14:
#line 104 "y.v2cx"
{ warning("'attribute' statement ignored"); ;
    break;}
case 15:
#line 105 "y.v2cx"
{ warning("'disconnect' statement ignored"); ;
    break;}
case 16:
#line 106 "y.v2cx"
{ warning("'component' statement illegal"); ;
    break;}
case 17:
#line 109 "y.v2cx"
{
            sigprefix[0]=0;
            process_present=FALSE;
            seq_flag=FALSE;
            seq_tot=0; comb_tot=0;
            processing_process=FALSE;
            myfree(&yyvsp[-5].txt);
          ;
    break;}
case 22:
#line 124 "y.v2cx"
{ addtmpsig(yyvsp[0].txt); myfree(&yyvsp[0].txt); ;
    break;}
case 23:
#line 125 "y.v2cx"
{ addtmpsig(yyvsp[0].txt); myfree(&yyvsp[0].txt); ;
    break;}
case 24:
#line 127 "y.v2cx"
{ copytmpslist(yyvsp[-1].n, yyvsp[0].n, TRUE, &dummyft); ;
    break;}
case 25:
#line 129 "y.v2cx"
{ yyval.n=_IN; ;
    break;}
case 26:
#line 130 "y.v2cx"
{ yyval.n=_OUT; ;
    break;}
case 27:
#line 131 "y.v2cx"
{ warning("'inout' direction illegal"); ;
    break;}
case 28:
#line 132 "y.v2cx"
{ warning("unknown direction"); yyerrok; ;
    break;}
case 29:
#line 134 "y.v2cx"
{ yyval.n=1; ;
    break;}
case 30:
#line 135 "y.v2cx"
{ yyval.n=1; ;
    break;}
case 31:
#line 136 "y.v2cx"
{ yyval.n=1; ;
    break;}
case 32:
#line 137 "y.v2cx"
{
                yyval.n=yyvsp[-1].s->rleft-yyvsp[-1].s->rright+1; /* (x to y) ! */
                myfree((char **)&yyvsp[-1].s);
                ;
    break;}
case 35:
#line 144 "y.v2cx"
{
              yyval.s=(sigdata *)mymalloc(sizeof(sigdata));
              yyval.s->rleft=yyvsp[-2].n;
              yyval.s->rright=yyvsp[0].n;
              ;
    break;}
case 36:
#line 149 "y.v2cx"
{
              yyval.s=(sigdata *)mymalloc(sizeof(sigdata));
              yyval.s->rleft=yyvsp[0].n;
              yyval.s->rright=yyvsp[0].n;
              ;
    break;}
case 37:
#line 154 "y.v2cx"
{ warning("'to' direction illegal"); ;
    break;}
case 38:
#line 159 "y.v2cx"
{ myfreen(3, &yyvsp[-9].txt, &yyvsp[-7].txt, &yyvsp[-1].txt); ;
    break;}
case 49:
#line 176 "y.v2cx"
{ warning("'assert' statement illegal"); ;
    break;}
case 50:
#line 179 "y.v2cx"
{
         /* When we find a name, firstly we check if it is a declared variable;
            if this is the case, whe check if the variable has been assigned
            a value, ie if state is FALSE. */
         /* We don't bother of variables used but not declared */
         signal *sp;
         sp=findsig(yyvsp[0].txt);
         if (sp!=NULL) {
            if (processing_process && !sp->var) { /* Signal */
                /* Compile signal list */
                /* Check if signal already there */
                BOOL present=FALSE;
                int i;
                for (i=0; i<procsigcount; i++)
                  if (strcmp(procsig[i]->name, yyvsp[0].txt)==0) {
                      present=TRUE;
                      break;
                      }
                if (!present) {
                   procsig=myrealloc(procsig, (++procsigcount)*sizeof(signal *));
                   procsig[procsigcount-1]=sp;
                   }
                }
            else if (sp->var && sp->state) { /* Variable not assigned */
               printf("Guessing: variable '%s' at line %d seems to be used\n"
                      "          before a value is assigned to\n"
                      "          --> may be sequential, but not sure\n",
                      sp->name, lineno);
                  seq_tot++;
                  /* seq_flag=TRUE; */
               }
            }
         myfree(&yyvsp[0].txt);
         ;
    break;}
case 51:
#line 213 "y.v2cx"
{
         signal *sp;
         sp=findsig(yyvsp[-3].txt);
         if (sp==NULL) warning("Undeclared signal '%s'", yyvsp[-3].txt);
         else if (processing_process) {
            BOOL present=FALSE;
            int i;
            for (i=0; i<procsigcount; i++)
               if (strcmp(procsig[i]->name, yyvsp[-3].txt)==0) {
                  present=TRUE;
                  break;
                  }
            if (!present) {
                procsig=myrealloc(procsig, (++procsigcount)*sizeof(signal *));
                procsig[procsigcount-1]=sp;
                }
            }
         myfree(&yyvsp[-3].txt);
         ;
    break;}
case 52:
#line 232 "y.v2cx"
{;
    break;}
case 53:
#line 233 "y.v2cx"
{;
    break;}
case 67:
#line 247 "y.v2cx"
{
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          ;
    break;}
case 68:
#line 254 "y.v2cx"
{
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          ;
    break;}
case 69:
#line 259 "y.v2cx"
{
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          ;
    break;}
case 75:
#line 272 "y.v2cx"
{ clkcount++; ;
    break;}
case 76:
#line 273 "y.v2cx"
{
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          ;
    break;}
case 83:
#line 287 "y.v2cx"
{ clkcount++; ;
    break;}
case 84:
#line 288 "y.v2cx"
{ clkcount++; ;
    break;}
case 85:
#line 294 "y.v2cx"
{ myfree(&yyvsp[-3].txt); ;
    break;}
case 86:
#line 296 "y.v2cx"
{ yyval.txt=yyvsp[0].txt; ;
    break;}
case 87:
#line 297 "y.v2cx"
{ yyval.txt=yyvsp[-3].txt; ;
    break;}
case 88:
#line 299 "y.v2cx"
{ yyval.txt=yyvsp[0].txt; ;
    break;}
case 93:
#line 306 "y.v2cx"
{
             warning("'delay' has no effect");
             ;
    break;}
case 94:
#line 312 "y.v2cx"
{ myfree(&yyvsp[-3].txt); ;
    break;}
case 98:
#line 320 "y.v2cx"
{
         char *point;
         /* Tolgo il prefisso del blocco attuale */
         sigprefix[strlen(sigprefix)-1]='\0';
         point=strrchr(sigprefix, '_');
         if (point==NULL) point=sigprefix;
         *point='\0';
         ;
    break;}
case 99:
#line 329 "y.v2cx"
{
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, yyvsp[-1].txt);
           strcat(sigprefix, "_");
           myfree(&yyvsp[-1].txt);
           ;
    break;}
case 101:
#line 337 "y.v2cx"
{ myfree(&yyvsp[0].txt); ;
    break;}
case 103:
#line 340 "y.v2cx"
{
               if (clkcount>0) {
                  printf("Diagnostic: Clock check at line %d\n"
                         "            --> sequential architecture\n", lineno);
/*                seq_flag=TRUE; */
                  seq_tot+=10;
                  }
               clkcount=0; /* Initialize */
               ;
    break;}
case 106:
#line 359 "y.v2cx"
{
            char *point;
            int i, j;
            BOOL found, allincluded=TRUE;
            /* Tolgo il prefisso del blocco attuale */
            sigprefix[strlen(sigprefix)-1]='\0';
            point=strrchr(sigprefix, '_');
            if (point==NULL) point=sigprefix;
            *point='\0';
            /* Check if used signals are all included in sensitivity list */

#if 0
puts("Segnali nel processo:");
for (i=0; i<procsigcount; i++)
     printf("%s\n", procsig[i]->name);
puts("Segnali nella sensilist:");
for (j=0; j<sensisigcount; j++)
     printf("%s\n", sensisig[j]->name);
#endif


            for (i=0; i<procsigcount; i++) {
                 found=FALSE;
                 for (j=0; j<sensisigcount; j++) {
                     if (procsig[i]==sensisig[j]) {
                        found=TRUE;
                        break;
                        }
                     }
                 if (found==FALSE) { /* Not all included -> Sequential */
                    printf("Diagnostic: Signal '%s' in process '%s'\n"
                           "            not included in sensitivity list\n"
                           "            --> sequential architecture\n",
                           procsig[i]->name, yyvsp[-9].txt);
/*                  seq_flag=TRUE; */
                    seq_tot+=5;
                    allincluded=FALSE;
                    }
                 }
            /* All included? */
            if (allincluded) {
               printf("Diagnostic: All signals used in process '%s'\n"
                      "            are included in sensitivity list\n"
                      "            --> may be combinatorial\n", yyvsp[-9].txt);
                      comb_tot++;
               }
            if (procsigcount) myfree((void *)&procsig);
            if (sensisigcount) myfree((void *)&sensisig);
            procsigcount=0;
            sensisigcount=0;

            processing_process=FALSE;
          ;
    break;}
case 107:
#line 413 "y.v2cx"
{
           /* Creo e aggiungo il prefisso del blocco attuale */
           static nonameprocs=0;
           char tmp[8];
           sprintf(tmp, "p%d", nonameprocs++);
           strcat(sigprefix, tmp);
           strcat(sigprefix, "_");
           join(&yyval.txt, "%s", tmp);
           clk_in_sensi=FALSE;
           processing_process=TRUE;
           process_present=TRUE;
           firstline=TRUE;
           ;
    break;}
case 108:
#line 426 "y.v2cx"
{
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, yyvsp[-1].txt);
           strcat(sigprefix, "_");
           yyval.txt=yyvsp[-1].txt;
           processing_process=TRUE;
           process_present=TRUE;
           clk_in_sensi=FALSE;
           firstline=TRUE;
           ;
    break;}
case 110:
#line 438 "y.v2cx"
{ myfree(&yyvsp[0].txt); ;
    break;}
case 113:
#line 445 "y.v2cx"
{
              signal *sp;
              sp=findsig(yyvsp[0].txt);
              if (sp==NULL) warning("Undeclared signal '%s'", yyvsp[0].txt);
              else {
                sensisig=myrealloc(sensisig, (++sensisigcount)*sizeof(signal *));
                sensisig[sensisigcount-1]=sp;
                }
              if (isclock(yyvsp[0].txt)) {
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) clk_in_sensi=TRUE;
                }
              myfree(&yyvsp[0].txt);
              ;
    break;}
case 114:
#line 458 "y.v2cx"
{
              signal *sp;
              sp=findsig(yyvsp[0].txt);
              if (sp==NULL) warning("Undeclared signal '%s'", yyvsp[0].txt);
              else {
                sensisig=myrealloc(sensisig, (++sensisigcount)*sizeof(signal *));
                sensisig[sensisigcount-1]=sp;
                }
              if (isclock(yyvsp[0].txt)) {
                warning("Clock signal '%s' in sensilist", yyvsp[0].txt);
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) clk_in_sensi=TRUE;
                }
              myfree(&yyvsp[0].txt);
              ;
    break;}
case 117:
#line 476 "y.v2cx"
{ warning("'type' statement ignored"); ;
    break;}
case 118:
#line 477 "y.v2cx"
{ warning("'file' statement illegal"); ;
    break;}
case 119:
#line 478 "y.v2cx"
{ warning("'alias' statement illegal"); ;
    break;}
case 120:
#line 479 "y.v2cx"
{ warning("'attribute' statement ignored"); ;
    break;}
case 121:
#line 480 "y.v2cx"
{ warning("'assert' statement illegal"); ;
    break;}
case 122:
#line 481 "y.v2cx"
{ warning("'procedure' statement illegal"); ;
    break;}
case 123:
#line 484 "y.v2cx"
{
                addsig(yyvsp[0].txt, TRUE); myfree(&yyvsp[0].txt);
                ;
    break;}
case 124:
#line 487 "y.v2cx"
{
                addsig(yyvsp[-2].txt, TRUE); myfree(&yyvsp[-2].txt);
                ;
    break;}
case 129:
#line 502 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 130:
#line 503 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 131:
#line 504 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 132:
#line 505 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 133:
#line 506 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 134:
#line 507 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 135:
#line 508 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 136:
#line 509 "y.v2cx"
{ firstline=FALSE; ;
    break;}
case 137:
#line 512 "y.v2cx"
{
             findsig(yyvsp[-4].txt)->state=FALSE;
             /* state is FALSE when a value has been assigned to a variable */
             /* (This is a different use of 'state' from 'v2c' sources) */
             myfree(&yyvsp[-4].txt);
             ;
    break;}
case 138:
#line 520 "y.v2cx"
{
           /* If 'else' not found, probably is sequential */
           if (!elsefound) {
            printf("Diagnostic: 'if' without 'else' at line %d\n"
                   "            --> may be sequential\n", lineno);
/*              seq_flag=TRUE; */
             seq_tot++;
             }
           ;
    break;}
case 141:
#line 532 "y.v2cx"
{ elsefound=TRUE; ;
    break;}
case 143:
#line 536 "y.v2cx"
{
            if (clk_in_sensi == TRUE) {
               if (clkcount>1) {
                  printf("Diagnostic: Clock check at line %d\n"
                         "            --> sequential architecture\n", lineno);
/*                seq_flag=TRUE; */
                  seq_tot+=10;
                  }
               else if (clkcount==1) {
                  printf("Guessing: Clock check at line %d\n"
                         "          --> may be sequential\n", lineno);
                  seq_tot++;
                  }
               }
            clkcount=0; /* Initialize */
            elsefound=FALSE; /* Initialize */
        ;
    break;}
case 144:
#line 553 "y.v2cx"
{ elsefound=FALSE; /* Initialize */ ;
    break;}
case 148:
#line 561 "y.v2cx"
{
             printf("Diagnostic: 'other' statement at line %d:\n"
                    "            'case' may be a multiplexer\n"
                    "            --> may be combinatorial\n", lineno);
             comb_tot++;
             ;
    break;}
case 153:
#line 576 "y.v2cx"
{ myfree(&yyvsp[-1].txt); ;
    break;}
case 156:
#line 580 "y.v2cx"
{ myfree(&yyvsp[-4].txt); ;
    break;}
case 157:
#line 582 "y.v2cx"
{;
    break;}
case 158:
#line 583 "y.v2cx"
{;
    break;}
case 162:
#line 597 "y.v2cx"
{
             if (clkcount>0) {
                printf("Diagnostic: Clock check at line %d\n"
                       "            --> sequential architecture\n", lineno);
/*              seq_flag=TRUE; */
                seq_tot+=10;
                }
             clkcount=0; /* Initialize */
             ;
    break;}
case 163:
#line 606 "y.v2cx"
{
             if (waitclk) clk_in_sensi=TRUE;
             waitclk=FALSE;
             ;
    break;}
case 164:
#line 611 "y.v2cx"
{
             if (isclock(yyvsp[0].txt)) {
                signal *sp;
                sp=findsig(yyvsp[0].txt);
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) waitclk=TRUE;
                }
             myfree(&yyvsp[0].txt);
             ;
    break;}
case 165:
#line 619 "y.v2cx"
{
             if (isclock(yyvsp[0].txt)) {
                signal *sp;
                sp=findsig(yyvsp[0].txt);
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) waitclk=TRUE;
                }
             myfree(&yyvsp[0].txt);
             ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 322 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;
      yyerror("parse error");
    }

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 628 "y.v2cx"


extern signal *shead, *stail;
extern signal **tmpslist;
extern int tmpslist_alloc;
extern char **waitcase;
extern int waitcase_alloc;
extern int yyparse(void);

static BOOL isclock(char *str)
{
if (match("*clk*", str) || match("*clock*", str) || match("*Clock*", str) || match("*CLOCK*", str) || match("*Clk*", str) || match("*CLK*", str)) {
   if (clockstr==0) { /* First time we enter */
      clockstr=mymalloc(strlen(str)+1);
      strcpy(clockstr, str);
      }
   else /* No first time */
      if (strcmp(clockstr, str)!=0) /* Different string */
         warning("Another clock signal (%s) found", str);
   return TRUE;
   }
return FALSE;
}



static int usage(void)
{
   fputs("Usage: v2cx [-s<n>] <filename> [-x <list>]\n"
         "  -s<n>    Size of 'integer'; default = "_INTEGERSIZES" bits\n"
         "  -x       Exclude variables from state\n"
         "           <list> is a space-separated list of"
#ifdef UNIX
         " escaped"
#endif
         " regular expressions\n"
         "Eg: v2cx counter.vhd -x sum "
#ifdef UNIX
         "'*waitindex' 't[eoa]st'\n"
#else
         "*waitindex t[eoa]st\n"
#endif
         , stderr);
   return(1);
}



int main(int argc, char *argv[])
{
int i;
char **argp;

fprintf(stderr, "v2c eXpert interface - (c) by C.Ghezzi - "
                VERSION " " DATE "\n");
if (argc<2 || strcmp(argv[1], "-x")==0) {
   return usage();
   }

if (!freopen(argv[1], "r", stdin)) {
   fprintf(stderr, "Error: Can't open input file '%s'\n", argv[1]);
   return(1);
   }

shead=(signal *)mymalloc(sizeof(signal));
stail=shead;
tmpslist=(signal **)mymalloc(tmpslist_alloc*sizeof(signal *));
waitcase=(char **)mymalloc(waitcase_alloc*sizeof(char *));

yyparse();

if (!process_present) {
   printf("Diagnostic: no processes detected\n");
   printf("            --> combinatorial architecture\n");
/*    seq_flag=FALSE; */
   comb_tot+=100;
   }

fclose(stdin);

if (seq_tot==0 && comb_tot==0) { seq_tot=1; comb_tot=1; }
if (seq_tot>=comb_tot) seq_flag=TRUE; else seq_flag=FALSE;
printf("\nFinal Report: sequential weight = %d , combinatorial weight = %d\n",
       seq_tot, comb_tot);
if (seq_flag)
    printf("              --> Architecture is sequential at %d%%\n",
           seq_tot*100/(seq_tot+comb_tot));
else
    printf("              --> Architecture is combinatorial at %d%%\n",
           comb_tot*100/(seq_tot+comb_tot));

argp=mymalloc((argc+2)*sizeof(char **)); /* Add one parameter (the last is '0') */
for (i=0; i<argc; i++) {
  argp[i]=mymalloc(strlen(argv[i])+1);
  strcpy(argp[i], argv[i]); /* Replicate arguments */
  }

strcpy(argp[0], "v2c"); /* Replace 'v2cx' */

if (!seq_flag) { /* Add '-c' flag */
   argp[argc]=mymalloc(3);
   strcpy(argp[argc], "-c");
   argc++;
}
else /* Add '-k<name>' if clock found */
  if (clockstr!=NULL) {
     argp[argc]=mymalloc(strlen(clockstr)+2+1);
     strcpy(argp[argc], "-k");
     strcat(argp[argc], clockstr);
     argc++;
     }

argp[argc]=0;

for (i=0; i<argc; i++) printf("%s ", argp[i]);
puts("");

/* execvp("v2c", argp); */

return(0);
}

/* End of v2cx.y */
