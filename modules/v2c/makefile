### V2C - VHDL to C translator
### Copyright (c) 1995, Cristian Ghezzi

### Change this section as needed

## For Unix Machines:
## If you are using SUN_OS you should define this instead of UNIX
## because it has a slightly different sprintf() function implementation.
# OS = SUN_OS
OS = UNIX
YACCRENAME1 = mv y.tab.c $*.c
YACCRENAME2 = -cmp -s $*.h y.tab.h || cp y.tab.h $*.h

## For MS_DOS Machines:
## I have never compiled under MS-DOS; it is pretty sure (by Murphy's law)
## that you will have a lot of problems.
# OS = MSDOS
# YACCRENAME1 = copy y.tab.c $*.c
# YACCRENAME2 = copy y.tab.h $*.h

## For Acorn RISC_OS Machines:
## Just forget this. I'm sure you don't even know what I'm talking of...
# OS = RISC_OS
# YACCRENAME1 = copy c.y_tab c.$* f~cd~v
# YACCRENAME2 = copy h.y_tab h.$* f~c
# CCFLAGS = -throwback -Desktop ^ -IC:
# LIBS = -LC:Stubs.o
# BELL = Echo |G

## For the C compiler:
## You may want to use a different compiler and add some flags (eg. -O).
# CC = cc
 CC = gcc
# CCFLAGS = -g

## If you don't modify the grammar files (*.y and *.l), you don't need
## to look at the following.

## For Flex
LEX = flex

## For Lex on Unix
# LEX = lex
# LEXRENAME = mv lex.yy.c $*.c

## For Bison
YACC = bison
YACCFLAGS = -d -y

## For Yacc
# YACC = yacc
# YACCFLAGS = -d


##############################################################################
# You should modify this section only if you have unterstood the structure of
# makefiles better than me (very likely).
# If this is the case, send me your changes.

.SUFFIXES: .y .l .c .o

all: v2c v2cx

v2c: v2cmain.o procs.o v2c.o yylex.o match.o
	$(CC) $(CCFLAGS) -o v2c v2cmain.o procs.o v2c.o match.o yylex.o $(LIBS)
	$(BELL)

v2cx: v2cx.o yylexx.o procs.o match.o
	$(CC) $(CCFLAGS) -o v2cx v2cx.o yylexx.o procs.o match.o $(LIBS)
	$(BELL)


## .y.h:
##	$(YACC) $(YACCFLAGS) $<
##	$(YACCRENAME1)
##	$(YACCRENAME2)
###.y.o:
###	$(YACC) $(YACCFLAGS) $<
###	$(YACCRENAME1)
###	$(YACCRENAME2)
###	$(CC) $(CCFLAGS) -c $*.c -ansi -D$(OS)
.y.c:
	$(YACC) $(YACCFLAGS) $<
	$(YACCRENAME1)
	$(YACCRENAME2)

###.l.o:
###	$(LEX) $<
###	$(LEXRENAME)
###	$(CC) $(CCFLAGS) -c $*.c -ansi -D$(OS)
.l.c:
	$(LEX) -L $<
	$(LEXRENAME)

.c.o:
	$(CC) $(CCFLAGS) -c $< -ansi -D$(OS)

#v2c.o:defs.h version.h
#v2cx.o: defs.h versionx.h
#yylex.o: yylex.l yylex.c
#yylex.c: v2c.h
#yylexx.o: v2cx.h
#v2cmain.o: defs.h version.h
#procs.o: defs.h

v2c.o:	v2c.c
#2c.o:	defs.h
#2c.o:	procs.h
#2c.o:	version.h
#2c.o:	match.h

v2cmain.o:	v2cmain.c
v2cmain.o:	defs.h
v2cmain.o:	procs.h
v2cmain.o:	version.h

procs.o:	procs.c
procs.o:	defs.h
procs.o:	procs.h
procs.o:	match.h

yylex.o:	yylex.c
#ylex.o:	defs.h
#ylex.o:	procs.h
#ylex.o:	v2c.h

match.o:	match.c

v2c.c:	v2c.y
v2c.c:	defs.h
v2c.c:	procs.h
v2c.c:	version.h
v2c.c:	match.h

yylex.c:	yylex.l
yylex.c:	defs.h
yylex.c:	procs.h
yylex.c:	v2c.h

v2cx.o:	v2cx.c
#2cx.o:	defs.h
#2cx.o:	procs.h
#2cx.o:	versionx.h
#2cx.o:	match.h

yylexx.o:	yylexx.c
#ylexx.o:	defs.h
#ylexx.o:	procs.h
#ylexx.o:	v2cx.h

v2cx.c:	v2cx.y
v2cx.c:	defs.h
v2cx.c:	procs.h
v2cx.c:	versionx.h
v2cx.c:	match.h

yylexx.c:	yylexx.l
yylexx.c:	defs.h
yylexx.c:	procs.h
yylexx.c:	v2cx.h

