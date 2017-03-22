/*  A Bison parser, made from y.v2c  */

typedef union {
       char * txt;  /* String */
       int n;       /* Value  */
       expdata * e; /* For expressions */
       sigdata * s; /* For signals     */
       } YYSTYPE;

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

extern YYSTYPE yylval;
