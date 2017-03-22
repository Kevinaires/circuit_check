/*  A Bison parser, made from y.v2c  */

#define	REM	258
#define	ENTITY	259
#define	IS	260
#define	PORT	261
#define	IN	262
#define	OUT	263
#define	INOUT	264
#define	END	265
#define	BIT	266
#define	STD_ULOGIC_VECTOR	267
#define	INTEGER	268
#define	RANGE	269
#define	ARCHITECTURE	270
#define	OF	271
#define	SIGNAL	272
#define	BEGN	273
#define	NOT	274
#define	AFTER	275
#define	UNIT	276
#define	TO	277
#define	DOWNTO	278
#define	NAME	279
#define	STRING	280
#define	NATURAL	281
#define	AND	282
#define	OR	283
#define	XOR	284
#define	WHEN	285
#define	ELSE	286
#define	WITH	287
#define	SELECT	288
#define	OTHERS	289
#define	BLOCK	290
#define	PROCESS	291
#define	VARIABLE	292
#define	IF	293
#define	THEN	294
#define	ELSIF	295
#define	CASE	296
#define	LOOP	297
#define	WHILE	298
#define	FOR	299
#define	NEXT	300
#define	EXIT	301
#define	WAIT	302
#define	UNTIL	303
#define	ON	304
#define	LASTVALUE	305
#define	EVENT	306
#define	ORL	307
#define	ANDL	308
#define	BIGEQ	309
#define	LESSEQ	310
#define	NOTEQ	311
#define	EQUAL	312
#define	UNARYMINUS	313
#define	UNARYPLUS	314
#define	NOTL	315

#line 4 "y.v2c"

#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "procs.h"
#include "version.h"
#include "match.h"


extern char *ignores;        /* Signal to ignore in 'exprc' and 'sensilist' */
extern integersize;          /* Bits in an 'integer' */
extern char **exclude;       /* List of variables (patterns) to exclude */
extern BOOL cq;              /* TRUE for combinatorial architectures */
static BOOL process_present; /* FALSE if no processes in source file */
extern char *sourcefile;     /* Name of source file */
extern char *outfile;

/* Signals in blocks are preceded by the genealogy tree
   Eg: qbus in block reg of block alu is alu.reg.qbus */
extern char sigprefix[1024]; /* Prefix for signals and variables */

char *e_name=0; /* Entity name */

extern char indent[256];  /* Indentation string */
BOOL vlib_f;          /* True if vector library to be included */
char tmpbuf[1024];    /* Temporary storage area */
char lastsigasg[256]; /* Last signal assignment */
int lasttype=0;       /* Last signal type encountered */
fromto lastfromto;    /* Range of values for last signal encountered */
BOOL needchg=FALSE;   /* FALSE: chg[] will not be defined */
BOOL needlst=FALSE;   /* FALSE: lst[] will not be defined */
BOOL ignorethis=FALSE; /* TRUE: Ignore current 'conf' */
char *lastvarinitstr=0; /* Variable initialization string value */
char *varinitlist[48]; /* List of variables to be initialized */
int varinitnum=0; /* Number of ... */

char *proclabel=NULL; /* Label for the process */
static int waitnum;   /* Number of wait statement under processing */

#define BIGGER(X, Y) (X>Y?X:Y)


#line 47 "y.v2c"
typedef union {
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

#define	YYFINAL		345
#define	YYFLAG		-32768
#define	YYNTBASE	76

#define YYTRANSLATE(x) ((unsigned)(x) <= 315 ? yytranslate[x] : 141)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    65,    74,    70,
    71,    63,    61,    73,    62,     2,    64,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    72,    69,    55,
    52,    56,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,    75,     2,     2,     2,     2,     2,     2,
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
    46,    47,    48,    49,    50,    51,    53,    54,    57,    58,
    59,    60,    66,    67,    68
};

#if YYDEBUG != 0
static const short yyrline[] = {     0,
    98,   145,   146,   150,   151,   158,   170,   171,   173,   174,
   179,   188,   199,   203,   204,   209,   210,   216,   224,   231,
   236,   248,   316,   319,   322,   323,   340,   343,   344,   351,
   355,   360,   361,   362,   363,   366,   388,   402,   407,   413,
   420,   427,   432,   437,   442,   447,   452,   457,   461,   466,
   471,   476,   481,   508,   512,   513,   516,   519,   522,   525,
   549,   553,   557,   561,   565,   569,   578,   596,   606,   616,
   629,   634,   639,   648,   649,   655,   678,   684,   690,   700,
   716,   723,   724,   726,   734,   746,   754,   760,   810,   819,
   826,   827,   830,   843,   874,   880,   888,   889,   909,   932,
   955,   979,   980,   987,   991,   998,   999,  1000,  1001,  1002,
  1003,  1004,  1005,  1008,  1021,  1033,  1034,  1045,  1055,  1061,
  1066,  1070,  1080,  1081,  1092,  1100,  1104,  1111,  1117,  1118,
  1120,  1121,  1129,  1147,  1148,  1152,  1156,  1160,  1180,  1185,
  1192,  1194
};

static const char * const yytname[] = {     0,
"error","$illegal.","REM","ENTITY","IS","PORT","IN","OUT","INOUT","END",
"BIT","STD_ULOGIC_VECTOR","INTEGER","RANGE","ARCHITECTURE","OF","SIGNAL","BEGN","NOT","AFTER",
"UNIT","TO","DOWNTO","NAME","STRING","NATURAL","AND","OR","XOR","WHEN",
"ELSE","WITH","SELECT","OTHERS","BLOCK","PROCESS","VARIABLE","IF","THEN","ELSIF",
"CASE","LOOP","WHILE","FOR","NEXT","EXIT","WAIT","UNTIL","ON","LASTVALUE",
"EVENT","'='","ORL","ANDL","'<'","'>'","BIGEQ","LESSEQ","NOTEQ","EQUAL",
"'+'","'-'","'*'","'/'","'&'","UNARYMINUS","UNARYPLUS","NOTL","';'","'('",
"')'","':'","','","'\\''","'|'","trad"
};
#endif

static const short yyr1[] = {     0,
    76,    77,    77,    78,    78,    79,    80,    80,    81,    81,
    82,    82,    83,    84,    84,    85,    85,    85,    85,    86,
    86,    87,    88,    89,    90,    90,    91,    92,    92,    93,
    93,    94,    94,    94,    94,    95,    95,    95,    95,    95,
    95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
    95,    95,    95,    96,    97,    97,    97,    97,    97,    97,
    98,    98,    98,    98,    98,    98,    99,   100,   100,   101,
   102,   102,   102,   103,   103,   104,   105,   105,   105,   106,
   107,   108,   108,   109,   109,   110,   111,   112,   113,   113,
   114,   114,   115,   115,   116,   116,   117,   117,   118,   119,
   119,   120,   120,   121,   121,   122,   122,   122,   122,   122,
   122,   122,   122,   123,   124,   125,   125,   125,   126,   127,
   127,   128,   129,   129,   129,   130,   130,   131,   132,   132,
   133,   134,   134,   135,   135,   136,   137,   138,   139,   139,
   140,   140
};

static const short yyr2[] = {     0,
     5,     0,     1,     1,     2,     7,     5,     6,     3,     5,
     1,     3,     2,     1,     1,     1,     4,     1,     5,     3,
     1,    13,     0,     0,     1,     9,     0,     0,     3,     3,
     3,     1,     1,     1,     1,     1,     4,     1,     3,     1,
     3,     2,     2,     3,     3,     3,     3,     2,     3,     3,
     3,     3,     3,     0,     1,     3,     3,     3,     2,     3,
     3,     3,     4,     3,     4,     4,     4,     1,     4,     1,
     3,     6,     7,     0,     3,     7,     4,     4,     5,    12,
     2,     0,     1,     0,     4,     1,     1,    13,     0,     2,
     0,     1,     0,     3,     1,     3,     1,     8,     0,     1,
     3,     0,     3,     3,     3,     1,     1,     1,     1,     1,
     1,     1,     1,     5,    11,     0,     8,     4,     1,     1,
     1,     9,     0,     8,     7,     1,     3,    10,     0,     2,
     1,     3,     6,     1,     1,     2,     2,     3,     3,     2,
     1,     3
};

static const short yydefact[] = {     2,
     4,     0,     3,     5,     0,     2,     0,     0,     0,     0,
     2,     0,     0,     0,     1,     0,     0,     0,    11,     0,
     0,     0,     0,     0,     0,     0,     6,     2,     7,    14,
    15,     9,     0,    12,    25,     0,     8,     0,    16,     0,
    18,    13,     0,    23,    10,     0,     0,     0,     2,    21,
     0,     0,     0,    89,     0,     0,    17,     0,    28,    70,
     0,     2,    32,     0,    68,    33,    34,     0,    35,     0,
     0,    20,    19,     0,     0,    81,     0,    36,    40,    38,
     0,     0,     0,     0,     0,     0,    30,    31,     0,     0,
    84,    93,     0,     0,    27,    48,     0,    43,    42,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    54,    23,     0,    23,    24,    29,     2,
    53,    52,    39,    49,    50,    51,    70,     0,    44,    45,
    46,    47,    41,     0,    74,    67,    69,     0,     2,    95,
     0,     2,    22,    26,     0,    37,     0,     0,     0,    36,
     0,     0,     0,    55,    86,     0,    94,     0,    97,    99,
     0,     0,    54,    71,    48,    59,     0,     0,     0,     0,
     0,     0,     0,     0,    85,     2,    96,     0,     0,     0,
    76,    75,     0,    60,    56,    61,     0,     0,    64,     0,
    62,    57,    58,    87,    24,   100,     0,     2,     0,     0,
    65,    66,    63,     0,     0,     0,   129,    24,     0,     0,
     0,    72,     0,   101,   102,    70,    54,     0,     0,     0,
     0,   106,     2,   107,   108,   109,   110,     0,   111,   112,
   113,     0,    78,    77,     0,    73,    82,     0,     0,   130,
     0,   119,     0,   136,   137,    54,     0,     0,   104,   105,
    54,     0,     0,     0,    79,    83,     0,     0,     2,     0,
   119,   120,   121,     0,    23,     0,   141,   140,   138,     0,
     0,    23,    91,    80,   103,    98,     0,    23,   123,   139,
     0,   132,     0,     2,    92,     0,   114,     2,     0,    24,
   142,     0,    24,    88,    24,     0,   126,     0,     0,   134,
   135,     0,     0,   116,     0,     0,     0,     0,   133,     0,
    23,    54,     0,    23,   127,    23,     0,    91,     2,     0,
     0,     2,     2,   122,   131,     0,    24,     0,     0,    24,
    24,   128,   118,    23,   115,   125,   123,     2,   124,    24,
   116,   117,     0,     0,     0
};

static const short yydefgoto[] = {   343,
   207,     3,     6,    13,    20,    21,    32,    33,    42,    51,
    11,    49,   143,    36,   120,    75,    55,    62,   242,   138,
   262,   154,    63,    64,    86,   136,   148,    66,   181,    67,
    68,   257,   115,   156,   195,    69,    70,   286,   117,   141,
   160,   179,   197,   239,   208,   223,   224,   225,   313,   263,
   264,   226,   290,   298,   227,   228,   326,   253,   302,   229,
   230,   231,   248,   268
};

static const short yypact[] = {    25,
    25,    31,-32768,-32768,    16,    25,    52,    45,    64,    51,
    25,     8,    82,    78,-32768,    77,    84,    91,-32768,    57,
    24,    72,   140,    80,    97,   129,-32768,    25,    64,-32768,
-32768,    89,    74,-32768,   150,   144,-32768,    77,-32768,   103,
   161,-32768,    77,-32768,-32768,   155,   156,    47,    25,   153,
   112,   162,    74,    35,   176,   167,-32768,   168,   115,   116,
   237,    25,-32768,   146,   125,-32768,-32768,   164,-32768,   172,
   178,-32768,-32768,   158,   143,   184,   237,   -36,-32768,-32768,
   237,   237,   237,   195,   352,   159,    48,-32768,   171,   155,
   163,   165,   157,   237,-32768,-32768,   175,-32768,-32768,   296,
   169,   237,   237,   237,   207,   237,   237,   237,   237,   237,
   155,   237,   170,-32768,-32768,   207,-32768,-32768,   359,    25,
-32768,-32768,-32768,   251,   337,   190,-32768,   203,    67,    67,
-32768,-32768,-32768,   179,   274,-32768,-32768,   247,    25,-32768,
    18,    25,-32768,-32768,   212,-32768,   241,   -11,   247,    -1,
   247,   313,   -19,-32768,-32768,   250,-32768,   207,   232,-32768,
   237,   249,-32768,-32768,-32768,-32768,    73,   291,     3,   237,
   166,   213,   247,   247,-32768,    25,-32768,   252,   259,   343,
-32768,-32768,   247,-32768,-32768,   266,   237,   237,   266,   237,
   266,   107,   107,-32768,-32768,   215,   219,    25,   145,    75,
   266,   266,   266,   279,   252,    74,   101,-32768,   227,   217,
   237,-32768,   257,-32768,   228,   233,-32768,   237,   235,   253,
    88,-32768,    25,-32768,-32768,-32768,-32768,   108,-32768,-32768,
-32768,   300,-32768,-32768,   237,-32768,   282,   280,   264,   292,
   247,   359,   321,-32768,-32768,-32768,   207,   265,   387,-32768,
-32768,   324,   303,   314,-32768,-32768,   294,   237,    25,   237,
   313,   107,-32768,   310,-32768,   247,-32768,   278,-32768,   247,
   375,-32768,   360,-32768,   359,-32768,   320,-32768,   353,   107,
   207,-32768,   237,    25,-32768,   322,-32768,    25,   223,-32768,
-32768,   138,-32768,-32768,-32768,   338,   317,   341,   384,-32768,
-32768,   237,   385,    -8,   340,   237,   347,   356,-32768,   367,
-32768,-32768,   400,-32768,-32768,-32768,   349,   360,    25,   247,
   374,    25,    25,-32768,-32768,   350,-32768,   388,   357,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   353,    25,-32768,-32768,
    -8,-32768,   429,   435,-32768
};

static const short yypgoto[] = {-32768,
     1,   436,-32768,   407,   401,   395,-32768,-32768,   -49,   -84,
-32768,  -100,  -127,   -95,-32768,-32768,   -60,-32768,   -61,  -153,
  -112,-32768,  -193,   -92,   -51,   229,-32768,-32768,   206,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   124,-32768,-32768,
   185,-32768,   238,-32768,  -205,-32768,-32768,-32768,   104,  -207,
  -265,-32768,   109,   141,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768
};


#define	YYLAST		447


static const short yytable[] = {    85,
     2,    88,    65,    59,   282,   113,     8,   173,   174,   183,
   243,    15,   128,   222,   139,    96,   142,   250,   163,    98,
    99,   100,   311,   140,   144,   153,   134,     1,    35,   173,
   174,   312,   119,   -70,     5,    65,   166,    97,   169,     7,
   124,   125,   126,   155,   129,   130,   131,   132,   133,    54,
   135,   175,   277,    65,   328,   222,     9,   164,    60,    10,
   192,   193,    87,   241,    65,   177,    61,   204,   -70,    12,
   200,    60,   167,   185,    14,   292,   152,    16,   293,    61,
   232,   297,   295,   -89,    39,    40,    41,   165,   157,   168,
   158,    17,   266,    18,   309,    25,    26,   270,   297,   180,
    19,   173,   174,    30,    31,   211,    65,    22,   186,   189,
   191,   152,   152,   327,    23,   194,   330,   331,    53,    26,
    35,   152,   121,   184,   216,   201,   202,    24,   203,   108,
   109,   110,   340,   173,   174,   246,   247,   210,   217,    35,
    27,   218,   159,   212,    28,   219,   220,   221,    29,   135,
   251,   252,    34,   280,   267,    65,   215,    38,   320,   300,
   301,    44,   299,    77,   279,   303,    43,   304,    78,    79,
    80,   284,    46,   180,    47,    56,    54,   288,   209,   261,
    50,    52,    57,    58,    77,    71,    74,    76,   291,    78,
    79,    80,    72,    73,    90,    65,   275,    65,    91,   333,
    89,    93,   336,   337,   152,    81,    82,    92,   261,    94,
   319,    95,   341,   322,    83,   323,   102,   187,    84,   -90,
   101,   188,   112,   249,   121,   118,    81,    82,   111,    65,
   127,    77,   114,   338,   116,    83,    78,    79,    80,    84,
   137,    77,   123,   102,   103,   104,    78,    79,    80,   146,
   106,   107,   108,   109,   110,    77,   296,   145,   261,   159,
    78,    79,    80,   161,   190,   149,   162,   176,   178,   182,
   150,    79,    80,    81,    82,   196,   198,   106,   107,   108,
   109,   110,    83,    81,    82,   234,    84,   205,   213,   235,
   206,   237,    83,   147,   104,   233,    84,    81,    82,   238,
   102,   103,   104,   244,   240,   256,    83,    81,    82,   254,
    84,   106,   107,   108,   109,   110,   151,   102,   103,   104,
    84,   245,   102,   103,   104,   265,   106,   107,   108,   109,
   110,   258,   259,   269,   106,   107,   108,   109,   110,   102,
   103,   104,   170,   260,   272,   171,   172,   271,   278,   273,
   281,   106,   107,   108,   109,   110,   106,   107,   108,   109,
   110,   122,   274,   102,   170,   104,   122,   171,   172,   102,
   103,   104,   199,   106,   107,   108,   109,   110,   102,   103,
   104,   283,   289,   285,   105,   102,   103,   104,   287,   305,
   294,   306,   307,   308,   310,   314,   317,   106,   107,   108,
   109,   110,   316,   106,   107,   108,   109,   110,   318,   321,
   216,   329,   106,   107,   108,   109,   110,   324,   332,   106,
   107,   108,   109,   110,   217,   335,   334,   218,   344,  -129,
  -129,   219,   220,   221,   345,    37,     4,    48,    45,   236,
   255,   325,   214,   276,   342,   339,   315
};

static const short yycheck[] = {    61,
     0,    62,    54,    53,   270,    90,     6,    27,    28,   163,
   218,    11,   105,   207,   115,    77,   117,   223,    30,    81,
    82,    83,    31,   116,   120,   138,   111,     3,    28,    27,
    28,    40,    94,    70,     4,    87,   149,    74,   151,    24,
   102,   103,   104,   139,   106,   107,   108,   109,   110,    49,
   112,    71,   260,   105,   320,   249,     5,    69,    24,    15,
   173,   174,    62,   217,   116,   158,    32,   195,    70,     6,
   183,    24,    74,    71,    24,   283,   138,    70,   284,    32,
   208,   289,   288,    36,    11,    12,    13,   149,    71,   151,
    73,    10,   246,    16,   302,    72,    73,   251,   306,   161,
    24,    27,    28,     7,     8,    31,   158,    24,   170,   171,
   172,   173,   174,   319,    24,   176,   322,   323,    72,    73,
   120,   183,    50,    51,    24,   187,   188,    71,   190,    63,
    64,    65,   338,    27,    28,    48,    49,   199,    38,   139,
    69,    41,   142,    69,     5,    45,    46,    47,    69,   211,
    43,    44,    24,   266,   247,   207,   206,    69,   312,    22,
    23,    18,   290,    19,   265,   293,    17,   295,    24,    25,
    26,   272,    70,   235,    14,    23,   176,   278,    34,   241,
    26,    26,    71,    22,    19,    10,    72,    72,   281,    24,
    25,    26,    26,    26,    70,   247,   258,   249,    35,   327,
    55,    24,   330,   331,   266,    61,    62,    36,   270,    52,
   311,    69,   340,   314,    70,   316,    27,    52,    74,    36,
    26,    56,    52,   223,    50,    69,    61,    62,    70,   281,
    24,    19,    70,   334,    70,    70,    24,    25,    26,    74,
    71,    19,    74,    27,    28,    29,    24,    25,    26,    71,
    61,    62,    63,    64,    65,    19,    34,    55,   320,   259,
    24,    25,    26,    52,    52,    19,    26,    18,    37,    21,
    24,    25,    26,    61,    62,    24,    18,    61,    62,    63,
    64,    65,    70,    61,    62,    69,    74,    73,    10,    73,
    72,    35,    70,    20,    29,    69,    74,    61,    62,    72,
    27,    28,    29,    69,    72,    24,    70,    61,    62,    10,
    74,    61,    62,    63,    64,    65,    70,    27,    28,    29,
    74,    69,    27,    28,    29,     5,    61,    62,    63,    64,
    65,    52,    69,    69,    61,    62,    63,    64,    65,    27,
    28,    29,    52,    52,    42,    55,    56,    24,    39,    36,
    73,    61,    62,    63,    64,    65,    61,    62,    63,    64,
    65,    71,    69,    27,    52,    29,    71,    55,    56,    27,
    28,    29,    30,    61,    62,    63,    64,    65,    27,    28,
    29,     7,    30,    24,    33,    27,    28,    29,    69,    52,
    69,    75,    52,    10,    10,    56,    41,    61,    62,    63,
    64,    65,    56,    61,    62,    63,    64,    65,    42,    10,
    24,    38,    61,    62,    63,    64,    65,    69,    69,    61,
    62,    63,    64,    65,    38,    69,    39,    41,     0,    43,
    44,    45,    46,    47,     0,    29,     1,    43,    38,   211,
   235,   318,   205,   259,   341,   337,   306
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

case 1:
#line 99 "y.v2c"
{
          char *sep;
          char *newoutfile;
          sep=strrchr(sourcefile, DIRSEP);
          if (sep) sep++; else sep=sourcefile;
          printf("/* Original file: %s\n", sep);
          printf(" * Translated by v2c "VERSION);
          if (cq==TRUE)
             printf("\n * -c option: combinatorial translation forced");
          if (exclude) {
             int i=0;
             printf("\n * Exclude variables: ");
             while (exclude[i]) printf(" %s", exclude[i++]);
             }
          if (*ignores)
             printf("\n * Ignored clock signal: %s", ignores);
          printf("\n * Integer size: %d bits", integersize);
          puts(" */");
          if (vlib_f) puts("#include \"vlib.h\"");
          puts("");
          join(&yyval.txt, "%s%s%s%s", yyvsp[-4].txt, yyvsp[-2].txt, yyvsp[-1].txt, yyvsp[0].txt); puts(yyval.txt);
          myfreen(5, &yyval.txt, &yyvsp[-4].txt, &yyvsp[-2].txt, &yyvsp[-1].txt, &yyvsp[0].txt);
          fclose(stdout);

          /* Use the entity name as file name */
          sep=strrchr(sourcefile, DIRSEP);
          if(sep) {
                *(sep)=0;
                newoutfile=mymalloc(strlen(sourcefile)+1+strlen(e_name)+1+1+1);
                sprintf(newoutfile, "%s%c%s%cc", sourcefile, DIRSEP, e_name, EXTC);
                *(sep)=DIRSEP;
          }
          else {
                newoutfile=mymalloc(strlen(e_name)+1+1+1);
                sprintf(newoutfile, "%s%cc", e_name, EXTC);
          }
          remove(newoutfile);
          if (rename(outfile, newoutfile))
             warning("Can't rename file '%s' to '%s'\n", outfile, newoutfile);
          fprintf(stderr, "%s --> %s, %sont\n", sourcefile, newoutfile, newoutfile);
          build_cont(newoutfile);
          myfree(&newoutfile);
          ;
    break;}
case 2:
#line 145 "y.v2c"
{ join(&yyval.txt, ""); ;
    break;}
case 3:
#line 146 "y.v2c"
{
              join(&yyval.txt, "%s/*%s */\n", indent, yyvsp[0].txt);
              myfree(&yyvsp[0].txt); ;
    break;}
case 5:
#line 151 "y.v2c"
{
               join(&yyval.txt, "%s\n%s *%s", yyvsp[-1].txt, indent, yyvsp[0].txt);
               myfreen(2, &yyvsp[-1].txt, &yyvsp[0].txt);
               ;
    break;}
case 6:
#line 158 "y.v2c"
{
              join(&e_name, "%s", StringToLower(yyvsp[-5].txt));
              myfree(&yyvsp[-5].txt);
              /* Inizialization of variables
                 used in the architecture translation */
              sigprefix[0]=0;
              indent[0]=0;
              process_present=FALSE;
              vlib_f=FALSE;
              if (!cq) needchg=TRUE; /* Sequential */
              ;
    break;}
case 7:
#line 170 "y.v2c"
{ ;
    break;}
case 8:
#line 171 "y.v2c"
{ ;
    break;}
case 9:
#line 173 "y.v2c"
{ myfree(&yyvsp[-2].txt); ;
    break;}
case 10:
#line 174 "y.v2c"
{ myfree(&yyvsp[-4].txt); ;
    break;}
case 11:
#line 179 "y.v2c"
{
                if (match(yyvsp[0].txt, ignores)) /* Clock */
                   join(&yyval.txt, "");
                else {
                   addtmpsig(yyvsp[0].txt);
                   join(&yyval.txt, "new[%s]=%%s", yyvsp[0].txt); /* returns "old[name]=%s" */
                   }
                myfree(&yyvsp[0].txt);
                ;
    break;}
case 12:
#line 188 "y.v2c"
{
                if (match(yyvsp[0].txt, ignores)) /* Clock */
                   join(&yyval.txt, "");
                else {
                   addtmpsig(yyvsp[0].txt);
                   join(&yyval.txt, "%s, new[%s]=%%s", yyvsp[-2].txt, yyvsp[0].txt); /* old[nm]=%s, old[nm]=%s */
                   }
                myfree(&yyvsp[0].txt);
                ;
    break;}
case 13:
#line 199 "y.v2c"
{
                copytmpslist(yyvsp[-1].n, yyvsp[0].n, TRUE, &lastfromto); /* TRUE = signal in state */
                ;
    break;}
case 14:
#line 203 "y.v2c"
{ yyval.n=_IN; ;
    break;}
case 15:
#line 204 "y.v2c"
{ yyval.n=_OUT; ;
    break;}
case 16:
#line 209 "y.v2c"
{ yyval.n=1; lasttype=yyval.n; lastfromto.from=0; lastfromto.to=1; ;
    break;}
case 17:
#line 210 "y.v2c"
{
                yyval.n=yyvsp[-1].s->rleft-yyvsp[-1].s->rright+1; /* (x to y) !! */
                lasttype=yyval.n;
                lastfromto.from=0; lastfromto.to=(1<<yyval.n)-1; /* (x to y) !!*/
                myfree((char **)&yyvsp[-1].s);
                ;
    break;}
case 18:
#line 216 "y.v2c"
{
                int min, max;
                yyval.n=integersize;
                lasttype=yyval.n;
                min=-(1<<yyval.n-1); max=(1<<yyval.n-1)-1;
                lastfromto.from=min;
                lastfromto.to=max;
                ;
    break;}
case 19:
#line 224 "y.v2c"
{
                yyval.n=bits(yyvsp[0].n-yyvsp[-2].n);
                lasttype=yyval.n;
                lastfromto.from=yyvsp[-2].n;
                lastfromto.to=yyvsp[0].n;
                ;
    break;}
case 20:
#line 231 "y.v2c"
{
              yyval.s=(sigdata *)mymalloc(sizeof(sigdata));
              yyval.s->rleft=yyvsp[-2].n;
              yyval.s->rright=yyvsp[0].n;
              ;
    break;}
case 21:
#line 236 "y.v2c"
{
              yyval.s=(sigdata *)mymalloc(sizeof(sigdata));
              yyval.s->rleft=yyvsp[0].n;
              yyval.s->rright=yyvsp[0].n; /* Same means 'bit' to addchgsig() */
              ;
    break;}
case 22:
#line 249 "y.v2c"
{
          char *t1, *t2, *t3, *t4, *o1, *o2, *o6, *o7, *o8, *o9, *oA;
          /* Consistency check */
          if (strcmp(e_name, StringToLower(yyvsp[-9].txt))!=0) warning("Entity %s not found", yyvsp[-9].txt);
          join(&o6, "int chg[_MAX_];\n");
          join(&o7, "int lst[_MAX_];\n");
          join(&o2, "    chg[_i_]=old[_i_] ^ new[_i_];\n");
          join(&o8, "       old[_i_]=new[_i_];\n");
          join(&o9, "       lst[_i_]=old[_i_];\n");
          join(&oA, "   ");
          if (needlst) {
             strcpy(o2, "    chg[_i_]=lst[_i_] ^ new[_i_];\n"); /* Beware! */
             strcpy(o8, "       lst[_i_]=new[_i_];\n"); /* Beware! */
             }
          else { o7[0]=0; o9[0]=0; }
          /* If sequential translation ... */
          if (cq==FALSE) {
             join(&o1, "for (_i_=0; _i_<_MAX_; _i_++)\n"
                       "    {\n"
                       "%s" /* o8: old[_i_]=new[_i_] |||| lst[_i_]=new[_i_] */
                       "    }\n", o8);
             }
          else {
             o1=(char *)mymalloc(1); o1[0]=0;
             if (!needchg) { o2[0]=0; o6[0]=0; oA[0]=0; }
             }

          join(&yyval.txt, "void %s(int in_data[], int out_data[])\n" /**/
                    "{\n"
                    "int _i_=0;\n"
                    "int _cont_;\n"
                    "%s\n" /* enum of signals - inherited from a_body */
                    "%s" /* o7: "int lst[_MAX_];\n" */
                    "int old[_MAX_];\n"
                    "int new[_MAX_];\n"
                    "%s" /* o6: "int chg[_MAX_];\n" */
                    "%s\n" /* Inizialization of new[], status part */
                    "%s" /* o1: for (_i_=0; _i_<_MAX_; _i_++)... */
                    "%s\n" /* Inizialization of new[], input part */
                    "%s" /* Comments in a_decl, signal initialisation */
                    "for (_i_=0; _i_<_MAX_; _i_++)\n"
                    "    {\n"
                    "%s" /* o2: chg[_i_]=[old|lst][_i_] ^ new[_i_];\n */
                    "    old[_i_]=new[_i_];\n"
                    "    }\n\n"
                    "do {\n"
                    "   _cont_=0;\n"
                    "   /* Start of Translation */\n\n"
                    "%s" /* Architecture body */
                    "\n   /* End of Translation */\n"
                    "   for (_i_=0; _i_<_MAX_; _i_++)\n"
                    "       {\n"
                    "       if (new[_i_]!=old[_i_]) _cont_=1;\n"
                    "%s" /* o9: lst[_i_]=old[_i_];\n */
                    "%s%s" /* oA: "   "; o2: chg[_i_]=[old|lst][_i_] ^ new[_i_];\n */
                    "       old[_i_]=new[_i_];\n"
                    "       }\n"
                    "   } while (_cont_);\n\n"
                    "%s" /* Compiling of out_data[] */
                    "}\n",
                    StringToLower(yyvsp[-9].txt), t1=make_enum(), o7, o6, t2=make_newinit(),
                    o1, t3=make_newinput(), yyvsp[-7].txt, o2, yyvsp[-4].txt, o9, oA, o2, t4=make_outdataend());
                    myfreen(16, &yyvsp[-11].txt, &yyvsp[-9].txt, &yyvsp[-7].txt, &yyvsp[-4].txt, &yyvsp[-2].txt, &t1,
                    &t2, &t3, &t4, &o1, &o2, &o6, &o7, &o8, &o9, &oA);
          ;
    break;}
case 23:
#line 316 "y.v2c"
{ strcat(indent, INDENTS); ;
    break;}
case 24:
#line 319 "y.v2c"
{ indent[strlen(indent)-INDENTL]=0; ;
    break;}
case 26:
#line 324 "y.v2c"
{
              /* signamelist contains "old[x]=%s, ... old[y]=%s" */
              /* '_docopy' inherits from 'type' through 'lasttype' */
              char *init;
              init=mymalloc(1); init[0]=0;
              if (yyvsp[-3].txt!=NULL) {
                 char *tmp;
                 tmp=strreplace(yyvsp[-6].txt, "%s", yyvsp[-3].txt); /* Replace %s with $6 */
                 init=myrealloc(init, strlen(tmp)+strlen(";\n")+strlen(indent)+1);
                 sprintf(init, "%s%s;\n", indent, tmp);
                 myfreen(2, &tmp, &yyvsp[-3].txt);
                 }
              join(&yyval.txt, "%s%s%s", yyvsp[-8].txt, init, yyvsp[0].txt);
              myfreen(4, &yyvsp[-8].txt, &init, &yyvsp[-6].txt, &yyvsp[0].txt);
              ;
    break;}
case 27:
#line 340 "y.v2c"
{ copytmpslist(_NONE, lasttype, TRUE, &lastfromto); ;
    break;}
case 28:
#line 343 "y.v2c"
{ yyval.txt=NULL; ;
    break;}
case 29:
#line 344 "y.v2c"
{
             join(&yyval.txt, "%s", yyvsp[0].e->txt);
             myfreen(2, &yyvsp[0].e->txt, &yyvsp[0].e);
             ;
    break;}
case 30:
#line 351 "y.v2c"
{
           join(&yyval.txt, "%s%s%s", yyvsp[-2].txt, yyvsp[-1].txt, yyvsp[0].txt);
           myfreen(3, &yyvsp[-2].txt, &yyvsp[-1].txt, &yyvsp[0].txt);
           ;
    break;}
case 31:
#line 355 "y.v2c"
{
           join(&yyval.txt, "%s%s%s", yyvsp[-2].txt, yyvsp[-1].txt, yyvsp[0].txt);
           myfreen(3, &yyvsp[-2].txt, &yyvsp[-1].txt, &yyvsp[0].txt);
           ;
    break;}
case 36:
#line 366 "y.v2c"
{
         signal *sp;
         sp=findsig(yyvsp[0].txt);
         if (sp==NULL && !excludevar(yyvsp[0].txt)) warning("Name '%s' not declared", yyvsp[0].txt);
         /* Maybe something illegal passes this test, but who cares? */
         /* Loop variables will be signalled */
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         if (sp && !sp->var) { /* signal */
            addchgsig(sp->name, -1, -1);
            yyval.e->size=sp->size;
            join(&yyval.e->txt, "old[%s]", sp->name);
            }
         else if (sp) { /* variable */
            join(&yyval.e->txt, "%s", sp->name);
            }
         else join(&yyval.e->txt, "%s", yyvsp[0].txt); /* Excluded variab. or loop var. or mistake */
         if (match(yyvsp[0].txt, ignores)) {
            ignorethis=TRUE; /* Ignored signal */
            warning("Signal %s ignored", yyvsp[0].txt);
            }
         myfree(&yyvsp[0].txt);
         ;
    break;}
case 37:
#line 388 "y.v2c"
{
         vlib_f=TRUE;
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         addchgsig(yyvsp[-3].txt, yyvsp[-1].s->rleft, yyvsp[-1].s->rright);
         yyval.e->size=yyvsp[-1].s->rleft-yyvsp[-1].s->rright+1; /* occhio a (x to y) !! */
         if (yyvsp[-1].s->rleft != yyvsp[-1].s->rright) { /* signal(x downto y) */
            join(&yyval.e->txt, "vpart(old[%s], %d, %d)",
                           yyvsp[-3].txt, yyvsp[-1].s->rleft, yyvsp[-1].s->rright);
            }
         else { /* signal(x) */
            join(&yyval.e->txt, "vbit(old[%s], %d)", yyvsp[-3].txt, yyvsp[-1].s->rleft);
            }
         myfreen(2, &yyvsp[-3].txt, &yyvsp[-1].s);
         ;
    break;}
case 38:
#line 402 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         yyval.e->size=integersize;
         join(&yyval.e->txt, "%d", yyvsp[0].n);
         ;
    break;}
case 39:
#line 407 "y.v2c"
{ /* !! Controllare che sia una cifra sola !! */
         if (yyvsp[-1].n>9) warning("Value '%d' should be one character", yyvsp[-1].n);
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         yyval.e->size=1;
         join(&yyval.e->txt, "%d", yyvsp[-1].n);
         ;
    break;}
case 40:
#line 413 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         yyval.e->size=strlen(yyvsp[0].txt);
         /* Binary strings are replaced with their value */
         join(&yyval.e->txt, "%d", vval(yyvsp[0].txt)); myfree(&yyvsp[0].txt);
         vlib_f=TRUE;
         ;
    break;}
case 41:
#line 420 "y.v2c"
{ /* Vector chaining */
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         yyval.e->size=yyvsp[-2].e->size+yyvsp[0].e->size;
         join(&yyval.e->txt, "vcat(%s, %s, %d)", yyvsp[-2].e->txt, yyvsp[0].e->txt, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e);
         vlib_f=TRUE;
         ;
    break;}
case 42:
#line 427 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "-%s", yyvsp[0].e->txt);
         yyval.e->size=yyvsp[0].e->size;
         myfreen(2, &yyvsp[0].e->txt, &yyvsp[0].e); ;
    break;}
case 43:
#line 432 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "+%s", yyvsp[0].e->txt);
         yyval.e->size=yyvsp[0].e->size;
         myfreen(2, &yyvsp[0].e->txt, &yyvsp[0].e); ;
    break;}
case 44:
#line 437 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s+%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 45:
#line 442 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s-%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 46:
#line 447 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s*%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 47:
#line 452 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s/%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 48:
#line 457 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         yyval.e->size=yyvsp[0].e->size;
         join(&yyval.e->txt, "~%s", yyvsp[0].e->txt); myfreen(2, &yyvsp[0].e->txt, &yyvsp[0].e); ;
    break;}
case 49:
#line 461 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s & %s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 50:
#line 466 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s | %s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 51:
#line 471 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "%s ^ %s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         yyval.e->size=BIGGER(yyvsp[-2].e->size, yyvsp[0].e->size);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 52:
#line 476 "y.v2c"
{
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         join(&yyval.e->txt, "(%s)", yyvsp[-1].e->txt);
         yyval.e->size=yyvsp[-1].e->size;
         myfreen(2, &yyvsp[-1].e->txt, &yyvsp[-1].e); ;
    break;}
case 53:
#line 481 "y.v2c"
{
         signal *sp;
         sp=findsig(yyvsp[-2].txt);
         if (sp==NULL && !excludevar(yyvsp[-2].txt)) warning("Name '%s' not declared", yyvsp[-2].txt);
         yyval.e=(expdata *)mymalloc(sizeof(expdata));
         if (sp && !sp->var) { /* signal */
            addchgsig(sp->name, -1, -1);
            yyval.e->size=sp->size;
            join(&yyval.e->txt, "lst[%s]", sp->name);
            needlst=TRUE;
            }
         else if (sp) { /* variable */
            warning("Illegal attribute on variable %s", yyvsp[-2].txt);
            join(&yyval.e->txt, "%s", sp->name);
            }
         else if (!match(yyvsp[-2].txt, ignores)) { /* Excluded variable or mistake */
           warning("Can't get last value of %s", yyvsp[-2].txt);
           join(&yyval.e->txt, "%s", yyvsp[-2].txt);
          }
         else { /* Ignored signal */
           join(&yyval.e->txt, "1 /* %s ignored */", ignores);
         }
         myfree(&yyvsp[-2].txt);
         ;
    break;}
case 54:
#line 508 "y.v2c"
{ ignorethis=FALSE; ;
    break;}
case 55:
#line 512 "y.v2c"
{ ignorethis=FALSE; ;
    break;}
case 56:
#line 513 "y.v2c"
{
         join(&yyval.txt, "(%s)", yyvsp[-1].txt);
         myfree(&yyvsp[-1].txt); ;
    break;}
case 57:
#line 516 "y.v2c"
{
         join(&yyval.txt, "%s && %s", yyvsp[-2].txt, yyvsp[0].txt);
         myfreen(2, &yyvsp[-2].txt, &yyvsp[0].txt); ;
    break;}
case 58:
#line 519 "y.v2c"
{
         join(&yyval.txt, "%s || %s", yyvsp[-2].txt, yyvsp[0].txt);
         myfreen(2, &yyvsp[-2].txt, &yyvsp[0].txt); ;
    break;}
case 59:
#line 522 "y.v2c"
{
         join(&yyval.txt, "!%s", yyvsp[0].txt);
         myfree(&yyvsp[0].txt); ;
    break;}
case 60:
#line 525 "y.v2c"
{
         signal *sp;
         sp=findsig(yyvsp[-2].txt);
         if (sp==NULL && !excludevar(yyvsp[-2].txt)) warning("Name '%s' not declared", yyvsp[-2].txt);
         if (sp && !sp->var) { /* signal */
            join(&yyval.txt, "old[%s]!=lst[%s]", sp->name, sp->name);
            needlst=TRUE;
            }
         else if (sp) { /* variable */
            warning("'EVENT' illegal on variable %s", yyvsp[-2].txt);
            join(&yyval.txt, "%s", sp->name);
            }
         else if (!match(yyvsp[-2].txt, ignores)) { /* Excluded variable or mistake */
           warning("Can't get last value of %s", yyvsp[-2].txt);
           join(&yyval.txt, "%s", yyvsp[-2].txt);
          }
         else { /* Ignored signal */
           join(&yyval.txt, "1 /* %s ignored */", ignores);
         }
         myfree(&yyvsp[-2].txt);
         ;
    break;}
case 61:
#line 549 "y.v2c"
{
         if (ignorethis) join(&yyval.txt, "1 /* %s ignored */", ignores);
         else join(&yyval.txt, "%s==%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 62:
#line 553 "y.v2c"
{
         if (ignorethis) join(&yyval.txt, "1 /* %s ignored */", ignores);
         else join(&yyval.txt, "%s>%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 63:
#line 557 "y.v2c"
{
         if (ignorethis) join(&yyval.txt, "1 /* %s ignored */", ignores);
         else join(&yyval.txt, "%s>=%s", yyvsp[-3].e->txt, yyvsp[0].e->txt);
         myfreen(4, &yyvsp[-3].e->txt, &yyvsp[0].e->txt, &yyvsp[-3].e, &yyvsp[0].e); ;
    break;}
case 64:
#line 561 "y.v2c"
{
         if (ignorethis) join(&yyval.txt, "1 /* %s ignored */", ignores);
         else join(&yyval.txt, "%s<%s", yyvsp[-2].e->txt, yyvsp[0].e->txt);
         myfreen(4, &yyvsp[-2].e->txt, &yyvsp[0].e->txt, &yyvsp[-2].e, &yyvsp[0].e); ;
    break;}
case 65:
#line 565 "y.v2c"
{
         if (ignorethis) join(&yyval.txt, "1 /* %s ignored */", ignores);
         else join(&yyval.txt, "%s<=%s", yyvsp[-3].e->txt, yyvsp[0].e->txt);
         myfreen(4, &yyvsp[-3].e->txt, &yyvsp[0].e->txt, &yyvsp[-3].e, &yyvsp[0].e); ;
    break;}
case 66:
#line 569 "y.v2c"
{
         if (ignorethis) join(&yyval.txt, "1 /* %s ignored */", ignores);
         else join(&yyval.txt, "%s!=%s", yyvsp[-3].e->txt, yyvsp[0].e->txt);
         myfreen(4, &yyvsp[-3].e->txt, &yyvsp[0].e->txt, &yyvsp[-3].e, &yyvsp[0].e); ;
    break;}
case 67:
#line 578 "y.v2c"
{
           char *t1;
           t1=make_chglist();
           /* Se l'assegnamento e' sensibile ad altri segnali, *
            * si inserisce la condizione (se non sequenziale). */
           if (*t1!=0 && cq==FALSE)
              join(&yyval.txt, "%sif (%s) {\n"
                        "%s   %s"
                        "%s   }\n",
                        indent, t1,
                        indent, yyvsp[0].txt,
                        indent);
           else
              join(&yyval.txt, "%s%s",
                        indent, yyvsp[0].txt);
           myfreen(4, &yyvsp[-3].s->name, &yyvsp[-3].s, &yyvsp[0].txt, &t1);
           ;
    break;}
case 68:
#line 596 "y.v2c"
{
             /* 'lastsigasg' e' usato da 'sigvalue'; puo' contenere: *
              * new[signal]=expr                                     *
              * vins(&new[signal], x, y, expr)                       *
              * vins(&new[signal], x, x, expr)                       */
             sprintf(lastsigasg, "new[%s]=%%s", yyvsp[0].txt);
             yyval.s=(sigdata *)mymalloc(sizeof(sigdata));
             yyval.s->rleft=-1;
             yyval.s->rright=-1;
             join(&yyval.s->name, "%s", yyvsp[0].txt); myfree(&yyvsp[0].txt); ;
    break;}
case 69:
#line 606 "y.v2c"
{ /* segnale(x downto y) */
                                       /* segnale(x)          */
             vlib_f=TRUE;
             sprintf(lastsigasg, "vins(&new[%s], %d, %d, %%s)",
                                 yyvsp[-3].txt, yyvsp[-1].s->rleft, yyvsp[-1].s->rright);
             yyval.s=(sigdata *)mymalloc(sizeof(sigdata));
             yyval.s->rleft=yyvsp[-1].s->rleft;
             yyval.s->rright=yyvsp[-1].s->rright;
             join(&yyval.s->name, "%s", yyvsp[-3].txt); myfreen(2, &yyvsp[-3].txt, &yyvsp[-1].s); ;
    break;}
case 70:
#line 616 "y.v2c"
{
             signal *sp;
             sp=findsig(yyvsp[0].txt);
             /* Controllo di consistenza */
             if (sp==NULL || sp->var) {
                if (!match(yyvsp[0].txt, ignores))
                   warning("%s is not a signal", yyvsp[0].txt);
                join(&yyval.txt, "%s", yyvsp[0].txt);
                }
             else join(&yyval.txt, "%s", sp->name);
             myfree(&yyvsp[0].txt);
             ;
    break;}
case 71:
#line 629 "y.v2c"
{
             sprintf(tmpbuf, lastsigasg, yyvsp[-2].e->txt);
             join(&yyval.txt, "%s;\n", tmpbuf);
             myfreen(2, &yyvsp[-2].e->txt, &yyvsp[-2].e);
             ;
    break;}
case 72:
#line 634 "y.v2c"
{
             sprintf(tmpbuf, lastsigasg, yyvsp[-5].e->txt);
             join(&yyval.txt, "if (%s) %s;\n", yyvsp[-1].txt, tmpbuf);
             myfreen(3, &yyvsp[-5].e->txt, &yyvsp[-5].e, &yyvsp[-1].txt);
             ;
    break;}
case 73:
#line 639 "y.v2c"
{
             sprintf(tmpbuf, lastsigasg, yyvsp[-6].e->txt);
             join(&yyval.txt, "if (%s) %s;\n"
                       "%s   else %s",
                       yyvsp[-2].txt, tmpbuf,
                       indent, yyvsp[0].txt);
             myfreen(4, &yyvsp[-6].e->txt, &yyvsp[-6].e, &yyvsp[-2].txt, &yyvsp[0].txt);
             ;
    break;}
case 74:
#line 648 "y.v2c"
{ ;
    break;}
case 75:
#line 649 "y.v2c"
{
             warning("Delay not yet implemented");
             ;
    break;}
case 76:
#line 655 "y.v2c"
{
         char *t1=make_chglist();
         if (cq==FALSE)
            join(&yyval.txt, "%sif (%s) {\n"
                      "%s%sswitch (%s) {\n"
                      "%s"
                      "%s%s%s}\n"
                      "%s%s}\n",
                      indent, t1,
                      indent, INDENTS, yyvsp[-5].e->txt,
                      yyvsp[0].txt,
                      indent, INDENTS, INDENTS,
                      indent, INDENTS);
          else
            join(&yyval.txt, "%sswitch (%s) {\n"
                      "%s"
                      "%s%s}\n",
                      indent, yyvsp[-5].e->txt,
                      yyvsp[0].txt,
                      indent, INDENTS);
          myfreen(6, &yyvsp[-5].e->txt, &yyvsp[-5].e, &yyvsp[-3].s->name, &yyvsp[-3].s, &yyvsp[0].txt, &t1);
          ;
    break;}
case 77:
#line 678 "y.v2c"
{
               sprintf(tmpbuf, lastsigasg, yyvsp[-3].e->txt);
               join(&yyval.txt, "%s      case %s : %s; break;\n"
                         , indent, yyvsp[-1].e->txt, tmpbuf);
               myfreen(4, &yyvsp[-3].e->txt, &yyvsp[-1].e->txt, &yyvsp[-3].e, &yyvsp[-1].e);
               ;
    break;}
case 78:
#line 684 "y.v2c"
{
               sprintf(tmpbuf, lastsigasg, yyvsp[-3].e->txt);
               join(&yyval.txt, "%s      default : %s;\n"
                         , indent, tmpbuf);
               myfreen(2, &yyvsp[-3].e->txt, &yyvsp[-3].e);
               ;
    break;}
case 79:
#line 690 "y.v2c"
{
               sprintf(tmpbuf, lastsigasg, yyvsp[-4].e->txt);
               join(&yyval.txt, "%s      case %s : %s; break;\n"
                         "%s"
                         , indent, yyvsp[-2].e->txt, tmpbuf
                         , yyvsp[0].txt);
               myfreen(5, &yyvsp[-4].e->txt, &yyvsp[-2].e->txt, &yyvsp[-4].e, &yyvsp[-2].e, &yyvsp[0].txt);
               ;
    break;}
case 80:
#line 701 "y.v2c"
{
         char *point;
         join(&yyval.txt, yyvsp[-9].txt, /* ...%s...%s...%s...%s... */
                   yyvsp[-11].txt, /* bname1 */
                   yyvsp[-7].txt, /* b_decl */
                   yyvsp[-5].txt, /* b_body */
                   yyvsp[-11].txt); /* bname1 */
         myfreen(4, &yyvsp[-11].txt, &yyvsp[-9].txt, &yyvsp[-7].txt, &yyvsp[-5].txt);
         /* Tolgo il prefisso del blocco attuale */
         sigprefix[strlen(sigprefix)-1]='\0';
         point=strrchr(sigprefix, '_');
         if (point==NULL) point=sigprefix;
         *point='\0';
         ;
    break;}
case 81:
#line 716 "y.v2c"
{
           yyval.txt=yyvsp[-1].txt;
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, yyvsp[-1].txt);
           strcat(sigprefix, "_");
           ;
    break;}
case 83:
#line 724 "y.v2c"
{ myfree(&yyvsp[0].txt); ;
    break;}
case 84:
#line 726 "y.v2c"
{
               join(&yyval.txt, "%s/* Block %%s: */\n"  /* bname1 */
                         "%%s"                   /* b_decl */
                         "%%s"                   /* b_body */
                         "%s/* End of %%s */\n", /* b_name1 */
                        indent, indent);
               make_chglist(); /* Pulisce: non ci interessa */
               ;
    break;}
case 85:
#line 734 "y.v2c"
{
               join(&yyval.txt, "%s/* Block %%s: */\n"  /* bname1 */
                         "%sif (%s) {\n"
                         "%%s"                   /* b_decl */
                         "%%s"                   /* b_body */
                         "%s}\n"
                         "%s/* End of %%s */\n", /* b_name1 */
                        indent, indent, yyvsp[-1].txt, indent, indent);
               myfree(&yyvsp[-1].txt);
               make_chglist(); /* Pulisce: non ci interessa */
               ;
    break;}
case 86:
#line 746 "y.v2c"
{
            /* Replace 'new[]' with 'old[]' */
            char *tmp;
            tmp=strreplace(yyvsp[0].txt, "new[", "old[");
            join(&yyval.txt, "%s", tmp);
            myfree(&tmp);
            ;
    break;}
case 88:
#line 761 "y.v2c"
{
            char *w1, *point;
            process_present=TRUE;
            w1=(char *)mymalloc(1); w1[0]=0;
            /* Gestione delle 'wait' */
            if (waitnum) {
               char *t1, *wnameinit;
               char tmpindent[256];
               wnameinit=mymalloc(1); wnameinit[0]=0;
               if (excludevar(WAITINDEXNAME)) {
                   warning("Variable %s excluded from state", WAITINDEXNAME);
                   wnameinit=myrealloc(wnameinit, strlen(indent)+
                                       strlen("static int "WAITINDEXNAME"=0;\n")+1);
                   sprintf(wnameinit, "%sstatic int "WAITINDEXNAME"=0;\n", indent);
                   }
               else addsig(WAITINDEXNAME, TRUE); /* Waitindex nello stato */
               /* Addsig prepone automaticamente il sigprefix */
               strcat(indent, INDENTS);
               sprintf(tmpindent, "%s%s", indent, INDENTS);
               sprintf(tmpbuf, "%s" /* static int waitindex=0; */
                               "%sswitch("WAITINDEXNAME") {\n"
                               "%s" /* case */
                               "%s}\n",
                               wnameinit,
                               indent,
                               t1=make_waitcase(tmpindent, waitnum),
                               tmpindent);
               myfree(&wnameinit);
               myfree(&t1);
               w1=(char *)myrealloc(w1, strlen(tmpbuf)+1);
               strcpy(w1, tmpbuf);
               indent[strlen(indent)-INDENTL]=0;
               sprintf(tmpbuf, "%s%s:\n", indent, proclabel);
               proclabel=myrealloc(proclabel, strlen(tmpbuf)+1);
               strcpy(proclabel, tmpbuf);
               }
            /* psensi ($3) contiene "{%s%s%s%s}%s" */
            sprintf(tmpbuf, "%s%s%s", yyvsp[-12].txt, yyvsp[-10].txt, yyvsp[-1].txt);
            join(&yyval.txt, tmpbuf, yyvsp[-8].txt, w1, yyvsp[-7].txt, yyvsp[-5].txt, proclabel);
            myfreen(7, &w1, &yyvsp[-12].txt, &yyvsp[-10].txt, &yyvsp[-8].txt, &yyvsp[-7].txt, &yyvsp[-5].txt, &yyvsp[-1].txt);
            /* Tolgo il prefisso del blocco attuale */
            sigprefix[strlen(sigprefix)-1]='\0';
            point=strrchr(sigprefix, '_');
            if (point==NULL) point=sigprefix;
            *point='\0';
            if (proclabel) myfree(&proclabel);
            ;
    break;}
case 89:
#line 810 "y.v2c"
{
           /* Creo e aggiungo il prefisso del blocco attuale */
           static nonameprocs=0;
           char tmp[8];
           sprintf(tmp, "p%d", nonameprocs++);
           strcat(sigprefix, tmp);
           strcat(sigprefix, "_");
           join(&yyval.txt, "%s/* %s: */\n", indent, tmp);
           ;
    break;}
case 90:
#line 819 "y.v2c"
{
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, yyvsp[-1].txt);
           strcat(sigprefix, "_");
           join(&yyval.txt, "%s/* %s: */\n", indent, yyvsp[-1].txt); myfree(&yyvsp[-1].txt); ;
    break;}
case 91:
#line 826 "y.v2c"
{ join(&yyval.txt, ""); ;
    break;}
case 92:
#line 827 "y.v2c"
{ join(&yyval.txt, "%s/* End of %s */\n", indent, yyvsp[0].txt); myfree(&yyvsp[0].txt); ;
    break;}
case 93:
#line 830 "y.v2c"
{
           /* Senza sensitivity: nessun controllo sui segnali */
           waitnum=0;
           join(&yyval.txt, "%s{\n"
                     "%%s" /* Questo diverra' il p_decl */
                     "%%s" /* Questo diverra' il waitswitch */
                     "%s%s%%s" /* Questo diverra' il _varinitcopy */
                     "%%s" /* Questo diverra' il p_body */
                     "%s}\n"
                     "%%s", /* Questo diverra' proclabel */
                     indent, INDENTS, indent, indent);
           /* Ora 'psensi' contiene '{%s%s%s%s}%s' opportunamente indentato */
           ;
    break;}
case 94:
#line 843 "y.v2c"
{
           /* Con sensitivity: controllo sui segnali... */
           char *t1;
           waitnum=0;
           t1=make_chglist();
           /* ...ma solo se sequenziale */
           if (cq==FALSE && t1[0]!=0) { /* Sequenziale con segnali non ignorati */
              join(&yyval.txt, "%sif (%s) {\n"
                        "%%s" /* Questo diverra' il p_decl */
                        "%%s" /* Questo diverra' il waitswitch */
                        "%s%s%%s" /* QUesto diverra' il _varinitcopy */
                        "%%s" /* Questo diverra' il p_body */
                        "%s%s}\n"
                        "%%s", /* Questo diverra' proclabel */
                        indent, t1, INDENTS, indent,
                        indent, INDENTS);
              }
           else { /* Combinatorio: == senza sensitivity */
              join(&yyval.txt, "%s{\n"
                        "%%s" /* Questo diverra' il p_decl */
                        "%%s" /* Questo diverra' il waitswitch */
                        "%s%s%%s" /* QUesto diverra' il _varinitcopy */
                        "%%s" /* Questo diverra' il p_body */
                        "%s}\n"
                        "%%s", /* Questo diverra' proclabel */
                        indent, INDENTS, indent, indent);
             }
           myfree(&t1);
           ;
    break;}
case 95:
#line 874 "y.v2c"
{
              if (!match(yyvsp[0].s->name, ignores)) /* Not ignored */
                 addchgsig(yyvsp[0].s->name, yyvsp[0].s->rleft, yyvsp[0].s->rright);
              else
                 warning("Sensitivity signal '%s' ignored", yyvsp[0].s->name);
              myfreen(2, &yyvsp[0].s->name, &yyvsp[0].s); ;
    break;}
case 96:
#line 880 "y.v2c"
{
              if (!match(yyvsp[0].s->name, ignores)) /* Not ignored */
                 addchgsig(yyvsp[0].s->name, yyvsp[0].s->rleft, yyvsp[0].s->rright);
              else
                 warning("Sensitivity signal '%s' ignored", yyvsp[0].s->name);
              myfreen(2, &yyvsp[0].s->name, &yyvsp[0].s); ;
    break;}
case 98:
#line 890 "y.v2c"
{
           char *tmp1;
           if (lastvarinitstr!=NULL)
              warning("Internal error - 'lastvarinitstr' not cleared");
           lastvarinitstr=yyvsp[-2].txt;
           tmp1=mymalloc(strlen(indent)+strlen("static int ;\n")+strlen(yyvsp[-5].txt)+1);
           tmp1[0]=0;
           if (*(yyvsp[-5].txt)) {
              sprintf(tmp1, "%sstatic int %s;\n", indent, yyvsp[-5].txt);
              }
           join(&yyval.txt, "%s"
                     "%s" /* static int ... */
                     "%s",
                     yyvsp[-7].txt,
                     tmp1,
                     yyvsp[0].txt);
           myfreen(4, &yyvsp[-7].txt, &yyvsp[-5].txt, &yyvsp[0].txt, &tmp1);
           ;
    break;}
case 99:
#line 909 "y.v2c"
{
           if (lastvarinitstr) { /* Initialization */
              int i=0;
              char *tmp1;
              yyval.txt=mymalloc(1); yyval.txt[0]=0;
              for (i=0; i<varinitnum; i++) {
                 tmp1=mymalloc(strlen(varinitlist[i])+strlen("=, ")
                               +strlen(lastvarinitstr)+1);
                 sprintf(tmp1, "%s=%s, ", varinitlist[i], lastvarinitstr);
                 yyval.txt=myrealloc(yyval.txt, strlen(yyval.txt)+strlen(tmp1)+1);
                 strcat(yyval.txt, tmp1);
                 myfree(&tmp1);
                 }
              yyval.txt[strlen(yyval.txt)-2]=';';
              yyval.txt[strlen(yyval.txt)-1]='\n';
/*            $$[strlen($$)]=0; Already there */
              myfree(&lastvarinitstr);
              }
           else join(&yyval.txt, "");
           while (varinitnum)
              myfree(varinitlist+(--varinitnum)); /* Automatically NULLed */
           ;
    break;}
case 100:
#line 932 "y.v2c"
{
                /* Le variabili vengono messe in lista solo se devono
                   far parte dello stato; sarebbe meglio metterle sempre,
                   settando opportunamente il field '->state' da dentro
                   ad addsig() usando excludevar() !! */
                if (!excludevar(yyvsp[0].txt)) { /* Put variable in state */
                   addsig(yyvsp[0].txt, TRUE);
                   /* Null string ==> Variable in state */
                   join(&yyval.txt, "");
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen(yyvsp[0].txt)+strlen(sigprefix)+1);
                   strcpy(varinitlist[varinitnum], sigprefix);
                   strcat(varinitlist[varinitnum++], yyvsp[0].txt);
                   }
                else {
                   warning("Variable %s excluded from state", yyvsp[0].txt);
                   join(&yyval.txt, "%s", yyvsp[0].txt); /* name */
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen(yyvsp[0].txt)+1);
                   strcpy(varinitlist[varinitnum++], yyvsp[0].txt);
                   }
                myfree(&yyvsp[0].txt);
                ;
    break;}
case 101:
#line 955 "y.v2c"
{
                if (!excludevar(yyvsp[-2].txt)) {
                   addsig(yyvsp[-2].txt, TRUE);
                   join(&yyval.txt, "%s", yyvsp[0].txt); /* $$=$3 is dangerous */
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen(yyvsp[-2].txt)+strlen(sigprefix)+1);
                   strcpy(varinitlist[varinitnum], sigprefix);
                   strcat(varinitlist[varinitnum++], yyvsp[-2].txt);
                   }
                else {
                   warning("Variable %s excluded from state", yyvsp[-2].txt);
                   if (*(yyvsp[0].txt)!=0) {
                      join(&yyval.txt, "%s, %s", yyvsp[-2].txt, yyvsp[0].txt); /* name, name ... */
                      }
                   else {
                      join(&yyval.txt, "%s", yyvsp[-2].txt);
                      }
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen(yyvsp[-2].txt)+1);
                   strcpy(varinitlist[varinitnum++], yyvsp[-2].txt);
                   }
                myfreen(2, &yyvsp[-2].txt, &yyvsp[0].txt);
                ;
    break;}
case 102:
#line 979 "y.v2c"
{ yyval.txt=NULL; ;
    break;}
case 103:
#line 980 "y.v2c"
{
            join(&yyval.txt, "%s", yyvsp[0].e->txt);
            myfreen(2, &yyvsp[0].e->txt, &yyvsp[0].e);
            ;
    break;}
case 104:
#line 987 "y.v2c"
{
           join(&yyval.txt, "%s%s%s", yyvsp[-2].txt, yyvsp[-1].txt, yyvsp[0].txt);
           myfreen(3, &yyvsp[-2].txt, &yyvsp[-1].txt, &yyvsp[0].txt);
           ;
    break;}
case 105:
#line 991 "y.v2c"
{
           join(&yyval.txt, "%s%s%s", yyvsp[-2].txt, yyvsp[-1].txt, yyvsp[0].txt);
           myfreen(3, &yyvsp[-2].txt, &yyvsp[-1].txt, &yyvsp[0].txt);
           ;
    break;}
case 114:
#line 1008 "y.v2c"
{
           signal *sp;
           sp=findsig(yyvsp[-4].txt);
           if (sp==NULL) {
              if (!excludevar(yyvsp[-4].txt)) warning("Variable '%s' not declared", yyvsp[-4].txt);
              /* Maybe something illegal passes this test, bu who cares? */
              join(&yyval.txt, "%s%s=%s;\n", indent, yyvsp[-4].txt, yyvsp[-1].txt);
              }
           else join(&yyval.txt, "%s%s=%s;\n", indent, sp->name, yyvsp[-1].txt);
           myfreen(2, &yyvsp[-4].txt, &yyvsp[-1].txt);
           ;
    break;}
case 115:
#line 1021 "y.v2c"
{
           join(&yyval.txt, "%sif (%s) {\n"
                     "%s" /* p_body */
                     "%s%s}\n"
                     "%s", /* elsepart */
                     indent, yyvsp[-8].txt,
                     yyvsp[-5].txt,
                     indent, INDENTS,
                     yyvsp[-3].txt);
           myfreen(3, &yyvsp[-8].txt, &yyvsp[-5].txt, &yyvsp[-3].txt);
           ;
    break;}
case 116:
#line 1033 "y.v2c"
{ join(&yyval.txt, ""); ;
    break;}
case 117:
#line 1034 "y.v2c"
{
             join(&yyval.txt, "%selse if (%s) {\n"
                       "%s"
                       "%s%s}\n"
                       "%s",
                       indent, yyvsp[-5].txt,
                       yyvsp[-2].txt,
                       indent, INDENTS,
                       yyvsp[0].txt);
             myfreen(3, &yyvsp[-5].txt, &yyvsp[-2].txt, &yyvsp[0].txt);
           ;
    break;}
case 118:
#line 1045 "y.v2c"
{
             join(&yyval.txt, "%selse {\n"
                       "%s"
                       "%s%s}\n",
                       indent,
                       yyvsp[-1].txt,
                       indent, INDENTS);
             myfree(&yyvsp[-1].txt);
           ;
    break;}
case 119:
#line 1055 "y.v2c"
{
           join(&yyval.txt, "%s", yyvsp[0].e->txt);
           myfreen(2, &yyvsp[0].e->txt, &yyvsp[0].e);
           make_chglist(); /* Pulisce: non ci interessa */
           ;
    break;}
case 120:
#line 1061 "y.v2c"
{
           join(&yyval.txt, "%s", yyvsp[0].txt);
           myfree(&yyvsp[0].txt);
           make_chglist(); /* Pulisce */
           ;
    break;}
case 122:
#line 1070 "y.v2c"
{
             join(&yyval.txt, "%sswitch (%s) {\n"
                       "%s"
                       "%s}\n",
                       indent, yyvsp[-7].txt,
                       yyvsp[-4].txt,
                       indent);
             myfreen(2, &yyvsp[-7].txt, &yyvsp[-4].txt);
             ;
    break;}
case 123:
#line 1080 "y.v2c"
{ join(&yyval.txt, ""); ;
    break;}
case 124:
#line 1081 "y.v2c"
{
             join(&yyval.txt, "%s%s\n" /* choice */
                       "%s" /* p_body */
                       "%s%sbreak;\n"
                       "%s", /* caselist */
                       indent, yyvsp[-6].txt,
                       yyvsp[-2].txt,
                       indent, INDENTS,
                       yyvsp[0].txt);
             myfreen(3, &yyvsp[-6].txt, &yyvsp[-2].txt, &yyvsp[0].txt);
             ;
    break;}
case 125:
#line 1092 "y.v2c"
{
             join(&yyval.txt, "%sdefault:\n" /* choice */
                       "%s", /* p_body */
                       indent,
                       yyvsp[-1].txt);
             myfree(&yyvsp[-1].txt);
             ;
    break;}
case 126:
#line 1100 "y.v2c"
{
             join(&yyval.txt, "case %s: ", yyvsp[0].txt);
             myfree(&yyvsp[0].txt);
             ;
    break;}
case 127:
#line 1104 "y.v2c"
{
             join(&yyval.txt, "case %s: %s", yyvsp[-2].txt, yyvsp[0].txt);
             myfreen(2, &yyvsp[-2].txt, &yyvsp[0].txt);
             ;
    break;}
case 128:
#line 1111 "y.v2c"
{
         sprintf(tmpbuf, "%s%s%s", yyvsp[-9].txt, yyvsp[-8].txt, yyvsp[-1].txt);
         join(&yyval.txt, tmpbuf, yyvsp[-5].txt);
         myfreen(4, &yyvsp[-9].txt, &yyvsp[-8].txt, &yyvsp[-5].txt, &yyvsp[-1].txt);
         ;
    break;}
case 129:
#line 1117 "y.v2c"
{ join(&yyval.txt, ""); ;
    break;}
case 130:
#line 1118 "y.v2c"
{ join(&yyval.txt, "%s/* %s: */\n", indent, yyvsp[-1].txt); myfree(&yyvsp[-1].txt); ;
    break;}
case 132:
#line 1121 "y.v2c"
{
               join(&yyval.txt, "%swhile (%s) {\n"
                         "%%s" /* p_body */
                         "%s%s}\n",
                         indent, yyvsp[0].txt,
                         indent, INDENTS);
               myfree(&yyvsp[0].txt);
               ;
    break;}
case 133:
#line 1129 "y.v2c"
{
               int mm='?', pm='?';
               if (yyvsp[-1].n==1) { mm='<'; pm='+'; } /* TO */
               if (yyvsp[-1].n==-1) { mm='>'; pm='-'; } /* DOWNTO */
               join(&yyval.txt, "%s{\n"
                         "%sint %s;\n"
                         "%sfor (%s=%s; %s%c=%s; %s%c%c) {\n"
                         "%%s"
                         "%s%s}\n"
                         "%s}\n",
                         indent,
                         indent, yyvsp[-4].txt,
                         indent, yyvsp[-4].txt, yyvsp[-2].txt, yyvsp[-4].txt, mm, yyvsp[0].txt, yyvsp[-4].txt, pm, pm,
                         indent, INDENTS,
                         indent);
               myfreen(3, &yyvsp[-4].txt, &yyvsp[-2].txt, &yyvsp[0].txt);
               ;
    break;}
case 134:
#line 1147 "y.v2c"
{ yyval.n=1; ;
    break;}
case 135:
#line 1148 "y.v2c"
{ yyval.n=-1; ;
    break;}
case 136:
#line 1152 "y.v2c"
{ join(&yyval.txt, "%scontinue;\n", indent); ;
    break;}
case 137:
#line 1156 "y.v2c"
{ join(&yyval.txt, "%sbreak;\n", indent); ;
    break;}
case 138:
#line 1160 "y.v2c"
{
             char *t1;
             if (proclabel==0) proclabel=make_proclabel();
             waitnum++;
             sprintf(tmpbuf, "case %d: goto %s;\n",
                             waitnum, t1=make_waitlabel());
             addwaitcase(tmpbuf, waitnum);
             join(&yyval.txt, "%s%s:\n"
                       "%sif (!(%s)) {\n"
                       "%s   "WAITINDEXNAME"=%d;\n"
                       "%s   goto %s;\n"
                       "%s   }\n",
                       indent, t1,
                       indent, yyvsp[-1].txt,
                       indent, waitnum,
                       indent, proclabel,
                       indent);
             myfreen(2, &yyvsp[-1].txt, &t1);
             ;
    break;}
case 139:
#line 1180 "y.v2c"
{
             join(&yyval.txt, "%s", yyvsp[0].txt);
             myfree(&yyvsp[0].txt);
             make_chglist(); /* Pulisce */
             ;
    break;}
case 140:
#line 1185 "y.v2c"
{
             char *t1;
             join(&yyval.txt, "%s", t1=make_chglist());
             needchg=TRUE;
             myfree(&t1);
             ;
    break;}
case 141:
#line 1192 "y.v2c"
{ addchgsig(yyvsp[0].s->name, yyvsp[0].s->rleft, yyvsp[0].s->rright);
                    myfreen(2, &yyvsp[0].s->name, &yyvsp[0].s); ;
    break;}
case 142:
#line 1194 "y.v2c"
{ addchgsig(yyvsp[0].s->name, yyvsp[0].s->rleft, yyvsp[0].s->rright);
                                myfreen(2, &yyvsp[0].s->name, &yyvsp[0].s); ;
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
#line 1197 "y.v2c"




/* End of v2c.y */
