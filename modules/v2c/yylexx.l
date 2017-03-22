/* yylexx.l */
/* by Cristian Ghezzi - (c) 1995 */

%{
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "procs.h"
#include "v2cx.h"

void getstring(void);
void getstr(void);

extern int lineno;
extern YYSTYPE yylval;
extern BOOL clock_needed;

static char buffer[1024];
%}
%%


[ \t] {;}
"--".*\n { lineno++; } /* Discard comments */

"LIBRARY ".*\n|"library ".*\n { lineno++; return LIBRARY; }
"USE ".*\n|"use ".*\n { lineno++; return USE; }
"GENERIC(".*\n|"generic(".*\n { lineno++; return GENERIC; }
"TYPE ".*\n|"type ".*\n|"SUBTYPE ".*\n|"subtype ".*\n { lineno++; return TYPE; }
"PROCEDURE ".*\n|"procedure ".*\n { lineno++; return PROCEDURE; }
"FUNCTION ".*\n|"function ".*\n { lineno++; return FUNCTION; }
"ASSERT ".*\n|"assert ".*\n { lineno++; return ASSERT; }
"CONSTANT ".*\n|"constant ".*\n { lineno++; return CONSTANT; }
"COMPONENT ".*\n|"component ".*\n { lineno++; return COMPONENT; }
"FILE ".*\n|"file ".*\n { lineno++; return FIL; }
"ALIAS ".*\n|"alias ".*\n { lineno++; return ALIAS; }
"ATTRIBUTE ".*\n|"attribute ".*\n { lineno++; return ATTRIBUTE_STAT; }
"DISCONNECT ".*\n|"disconnect ".*\n { lineno++; return DISCONNECT; }

\n { lineno++; fprintf(stderr, "Line:%4d\r", lineno); }

"ENTITY"|"entity" { return ENTITY; }
"IS"|"is" { return IS; }
"PORT"|"port" { return PORT; }
"IN"|"in" { return IN; }
"OUT"|"out" { return OUT; }
"INOUT"|"inout" { return INOUT; }
"BIT"|"bit" { return BIT; }
"STD_ULOGIC_VECTOR"|"std_ulogic_vector" { return STD_ULOGIC_VECTOR; }
"INTEGER"|"integer" { return INTEGER; }
"STD_ULOGIC"|"std_ulogic" { return STD_ULOGIC; }
"QSIM_STATE"|"qsim_state" { return QSIM_STATE; }

"RANGE"|"range" { return RANGE; }
"TO"|"to" { return TO; }
"DOWNTO"|"downto" { return DOWNTO; }
"END"|"end" { return END; }
"ARCHITECTURE"|"architecture" { return ARCHITECTURE; }
"OF"|"of" { return OF; }
"SIGNAL"|"signal" { return SIGNAL; }
"BEGIN"|"begin" { return BEGN; }
"NOT"|"not" { return NOT; }
"WHEN"|"when" { return WHEN; }
"WITH"|"with" { return WITH; }
"SELECT"|"select" { return SELECT; }
"OTHERS"|"others" { return OTHERS; }
"ELSE"|"else" { return ELSE; }
"BLOCK"|"block" { return BLOCK; }
"PROCESS"|"process" { return PROCESS; }
"VARIABLE"|"variable" { return VARIABLE; }
"IF"|"if" { return IF; }
"THEN"|"then" { return THEN; }
"ELSIF"|"elsif" { return ELSIF; }
"CASE"|"case" { return CASE; }
"LOOP"|"loop" { return LOOP; }
"WHILE"|"while" { return WHILE; }
"FOR"|"for" { return FOR; }
"NEXT"|"next" { return NEXT; }
"EXIT"|"exit" { return EXIT; }
"WAIT"|"wait" { return WAIT; }
"UNTIL"|"until" { return UNTIL; }
"ON"|"on" { return ON; }
"AFTER"|"after" { return AFTER; }
"AND"|"and" { return AND; }
"OR"|"or" { return OR; }
"XOR"|"xor" { return XOR; }
"NS"|"ns" { return UNIT; }
"LAST_VALUE"|"last_value" { return LASTVALUE; }
"EVENT"|"event" { return EVENT; }

[a-zA-Z_$]*[a-zA-Z0-9_$.]*("clk"|"clock"|"Clk"|"CLK"|"Clock"|"CLOCK")[a-zA-Z0-9_$.]*(((" ")*"="(" ")*'[01]')|') {
   return CLKEXPR;
}

\"[ \!#-~]*\" {
   getstring();
   return STRING;
}

[a-zA-Z_$][a-zA-Z0-9_$.]* {
   getstr();
   return NAME;
}

[0-9]+ {
   return NATURAL;
}

. { return yytext[0]; }

%%

void getstr(void)
{
sscanf(yytext, "%s", buffer);
yylval.txt=(char *)mymalloc(strlen(buffer)+1);
strcpy(yylval.txt, buffer);
}



void getstring(void)
{
/* Prende una stringa escludendo le " */
int i=0;
do {
   buffer[i]=yytext[i+1];
   ++i;
   } while (yytext[i]!='"');
buffer[i-1]=0;
yylval.txt=(char *)mymalloc(strlen(buffer)+1);
strcpy(yylval.txt, buffer);
}



/* End of yylexx.l */
