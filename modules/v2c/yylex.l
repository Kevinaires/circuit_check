/* yylex.l */
/* by Cristian Ghezzi - (c) 1995 */

%{
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "procs.h"
#include "v2c.h"

void getrem(char *s, int skip);
void getstring(void);
void getstr(void);

extern int lineno;
extern YYSTYPE yylval;

static char buffer[1024];
%}
%%


[ \t] {;}

"--".*\n { getrem("", 2); return REM; }
"LIBRARY ".*\n|"library ".*\n {
    warning("'library' statement ignored");
    getrem(" library", 7); return REM;
    }
"USE ".*\n|"use ".*\n {
    warning("'use' statement ignored");
    getrem(" use", 3); return REM;
    }

\n { lineno++; fprintf(stderr, "Line:%4d\r", lineno); }

"ENTITY"|"entity" { return ENTITY; }
"IS"|"is" { return IS; }
"PORT"|"port" { return PORT; }
"IN"|"in" { return IN; }
"OUT"|"out" { return OUT; }
"BIT"|"bit"|"STD_ULOGIC"|"std_ulogic"|"QSIM_STATE"|"qsim_state" { return BIT; }
"STD_ULOGIC_VECTOR"|"std_ulogic_vector" { return STD_ULOGIC_VECTOR; }
"INTEGER"|"integer" { return INTEGER; }
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

\"[ \!#-~]*\" {
   getstring();
   return STRING;
}

[a-zA-Z_$][a-zA-Z0-9_$.]* {
   getstr();
   return NAME;
}

[0-9]+ {
   sscanf(yytext, "%d", &yylval.n);
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



void getrem(char *s, int skip)
{
/* Prende tutto fino a \n */
int i=0;
lineno++;
while (yytext[i+skip]!='\n')
      {
      buffer[i]=yytext[i+skip];
      i++;
      }
buffer[i]=0;
#ifdef MAI
 strcat(buffer, " */\n");
#endif

yylval.txt=(char *)mymalloc(strlen(buffer)+strlen(s)+1);
strcpy(yylval.txt, s);
strcat(yylval.txt, buffer);
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



/* End of yylex.l */
