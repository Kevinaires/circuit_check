/*  A Bison parser, made from y.v2cx  */

typedef union { /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
       char * txt;  /* String */
       int n;       /* Value  */
       expdata * e; /* For expressions */
       sigdata * s; /* For signals     */
       } YYSTYPE;

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

extern YYSTYPE yylval;
