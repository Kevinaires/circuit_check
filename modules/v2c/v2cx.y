/* v2cx.y */
/* by Cristian Ghezzi - (c) 1995 */

%{
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

%}
%union { /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
       char * txt;  /* String */
       int n;       /* Value  */
       expdata * e; /* For expressions */
       sigdata * s; /* For signals     */
       }

%token USE LIBRARY GENERIC TYPE PROCEDURE FUNCTION ASSERT
%token CONSTANT COMPONENT FIL ALIAS ATTRIBUTE_STAT DISCONNECT
%token INOUT


%token ENTITY IS PORT INOUT END
%token <n> IN OUT INOUT
%token <n> BIT STD_ULOGIC_VECTOR INTEGER RANGE
%token <n> STD_ULOGIC QSIM_STATE
%token  ARCHITECTURE OF SIGNAL BEGN
%token NOT AFTER UNIT
%token <txt> NAME TO DOWNTO
%token STRING
%token <n> NATURAL
%token AND OR XOR
%token WHEN ELSE WITH SELECT OTHERS
%token BLOCK
%token PROCESS VARIABLE IF THEN ELSIF CASE LOOP WHILE FOR
%token NEXT EXIT WAIT UNTIL ON
%token CLKEXPR
%token LASTVALUE EVENT

%type <txt> signame signal
%type <txt> pname1
%type <n>   dir type
%type <s>    vec_range


%right '='
/* Logic operators: */
%left ORL
%left ANDL
/* Binary operators: */
%left OR
%left XOR
%left AND
/* Comparison: */
%left '<', '>', BIGEQ, LESSEQ, NOTEQ, EQUAL
%left  '+', '-'
/* !!! Guessing '&' operator precedence !!! */
%left  '*', '/', '&'
%right UNARYMINUS, UNARYPLUS, NOTL, NOT
%%

trad  : entity
        archi
      ;

/* Not recognized entity tokens */
notrece : /* Empty */
        | notelmt notrece
notelmt : USE { warning("'use' statement ignored"); }
        | LIBRARY { warning("'library' statement ignored"); }
        | GENERIC { warning("'generic' statement ignored"); }
        | TYPE { warning("'type' statement ignored"); }
        | CONSTANT { warning("'constant' statement ignored"); }
        | PROCEDURE { warning("'procedure' statement illegal"); }
        | FUNCTION { warning("'function' statement illegal"); }
        | ASSERT { warning("'assert' statement illegal"); }
        | FIL { warning("'file' statement ignored"); }
        | ALIAS { warning("'alias' statement ignored"); }
        | ATTRIBUTE_STAT { warning("'attribute' statement ignored"); }
        | DISCONNECT { warning("'disconnect' statement ignored"); }
        | COMPONENT { warning("'component' statement illegal"); }
        ;

entity    : notrece ENTITY NAME IS portstats END NAME ';' {
            sigprefix[0]=0;
            process_present=FALSE;
            seq_flag=FALSE;
            seq_tot=0; comb_tot=0;
            processing_process=FALSE;
            myfree(&$3);
          }
          ;
portstats : notrece
          | notrece PORT '(' portlist ')' ';' portstats
          ;
portlist  : signamelist ':' dirtype
          | signamelist ':' dirtype ';' portlist
          ;
signamelist : NAME { addtmpsig($1); myfree(&$1); }
            | signamelist ',' NAME { addtmpsig($3); myfree(&$3); }
            ;
dirtype     : dir type { copytmpslist($1, $2, TRUE, &dummyft); }
            ;
dir         : IN { $$=_IN; }
            | OUT { $$=_OUT; }
            | INOUT { warning("'inout' direction illegal"); }
            | error { warning("unknown direction"); yyerrok; }
            ;
type        : BIT { $$=1; }
            | QSIM_STATE { $$=1; }
            | STD_ULOGIC { $$=1; }
            | STD_ULOGIC_VECTOR '(' vec_range ')' {
                $$=$3->rleft-$3->rright+1; /* (x to y) ! */
                myfree((char **)&$3);
                }
            | INTEGER
            | INTEGER RANGE NATURAL TO NATURAL
            ;
vec_range : NATURAL DOWNTO NATURAL {
              $$=(sigdata *)mymalloc(sizeof(sigdata));
              $$->rleft=$1;
              $$->rright=$3;
              }
          | NATURAL {
              $$=(sigdata *)mymalloc(sizeof(sigdata));
              $$->rleft=$1;
              $$->rright=$1;
              }
          | NATURAL TO NATURAL { warning("'to' direction illegal"); }
          ;

/* Architecture */
archi : ARCHITECTURE NAME OF NAME IS a_decl
        BEGN a_body END NAME ';' { myfreen(3, &$2, &$4, &$10); }
      ;
/* Declarative part of the architecture */
a_decl    : notrece
          | SIGNAL signamelist ':' type decl_init ';' a_decl
          ;
decl_init : /* Empty */
          | ':' '=' expr
          ;
/* Architecture body */
a_body : a_stat
       | a_stat a_body
       ;
a_stat : a_assign
       | with
       | block
       | process
       | ASSERT { warning("'assert' statement illegal"); }
       ;
/* Algebric expressions */
expr : NAME {
         /* When we find a name, firstly we check if it is a declared variable;
            if this is the case, whe check if the variable has been assigned
            a value, ie if state is FALSE. */
         /* We don't bother of variables used but not declared */
         signal *sp;
         sp=findsig($1);
         if (sp!=NULL) {
            if (processing_process && !sp->var) { /* Signal */
                /* Compile signal list */
                /* Check if signal already there */
                BOOL present=FALSE;
                int i;
                for (i=0; i<procsigcount; i++)
                  if (strcmp(procsig[i]->name, $1)==0) {
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
         myfree(&$1);
         }
     | signame '(' vec_range ')' {
         signal *sp;
         sp=findsig($1);
         if (sp==NULL) warning("Undeclared signal '%s'", $1);
         else if (processing_process) {
            BOOL present=FALSE;
            int i;
            for (i=0; i<procsigcount; i++)
               if (strcmp(procsig[i]->name, $1)==0) {
                  present=TRUE;
                  break;
                  }
            if (!present) {
                procsig=myrealloc(procsig, (++procsigcount)*sizeof(signal *));
                procsig[procsigcount-1]=sp;
                }
            }
         myfree(&$1);
         }
     | NATURAL {}
     | '\'' NATURAL '\'' {}
     | STRING
     | expr '&' expr
     | '-' expr %prec UNARYMINUS
     | '+' expr %prec UNARYPLUS
     | expr '+' expr
     | expr '-' expr
     | expr '*' expr
     | expr '/' expr
     | NOT expr
     | expr AND expr
     | expr OR expr
     | expr XOR expr
     | '(' expr ')'
     | NAME '\'' LASTVALUE {
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          }
     ;

attribute : LASTVALUE {
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          }
          | EVENT {
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          }
          ;

/* Conditional expressions */
exprc : conf
      | '(' exprc ')'
      | exprc AND exprc %prec ANDL
      | exprc OR exprc %prec ORL
      | NOT exprc %prec NOTL
      | CLKEXPR attribute { clkcount++; }
      | NAME '\'' EVENT {
          printf("Diagnostic: attribute at line %d\n"
                 "            --> sequential architecture\n", lineno);
          seq_tot+=10;
          }
      ;

/* Comparisons */
conf : expr '=' expr %prec EQUAL
     | expr '>' expr
     | expr '>' '=' expr %prec BIGEQ
     | expr '<' expr
     | expr '<' '=' expr %prec LESSEQ
     | expr '<' '>' expr %prec NOTEQ
     | CLKEXPR { clkcount++; }
     | CLKEXPR attribute  '=' '\'' NATURAL '\'' { clkcount++; }
     ;

/* --- Concurrent statements --- */

/* Assegnamento di un valore a un segnale */
a_assign : signal '<' '=' sigvalue { myfree(&$1); }
         ;
signal   : signame { $$=$1; }
         | signame '(' vec_range ')' { $$=$1; }
         ;
signame  : NAME { $$=$1; }
         ;
sigvalue : expr delay ';'
         | expr delay WHEN exprc';'
         | expr delay WHEN exprc ELSE sigvalue
         ;
delay    : /* empty */
         | AFTER NATURAL UNIT {
             warning("'delay' has no effect");
             }
         ;

/* With ... select ... */
with : WITH expr SELECT signal '<' '=' selectlist { myfree(&$4); }
     ;
selectlist : expr WHEN expr ';'
           | expr WHEN OTHERS ';'
           | expr WHEN expr ',' selectlist
           ;

block: bname1 BLOCK blockguard b_decl BEGN b_body
       END BLOCK bname2 ';' {
         char *point;
         /* Tolgo il prefisso del blocco attuale */
         sigprefix[strlen(sigprefix)-1]='\0';
         point=strrchr(sigprefix, '_');
         if (point==NULL) point=sigprefix;
         *point='\0';
         }
         ;
bname1 : NAME ':' {
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, $1);
           strcat(sigprefix, "_");
           myfree(&$1);
           }
       ;
bname2 : /* Null */
       | NAME  { myfree(&$1); }
       ;
blockguard : /* Null */
           | '(' exprc ')' {
               if (clkcount>0) {
                  printf("Diagnostic: Clock check at line %d\n"
                         "            --> sequential architecture\n", lineno);
/*                seq_flag=TRUE; */
                  seq_tot+=10;
                  }
               clkcount=0; /* Initialize */
               }
           ;
b_decl : a_decl
       ;
b_body : a_body
       ;


/* --- Processi sequenziali --- */

process : pname1 PROCESS psensi p_decl BEGN p_body
          END PROCESS pname2 ';' {
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
                           procsig[i]->name, $1);
/*                  seq_flag=TRUE; */
                    seq_tot+=5;
                    allincluded=FALSE;
                    }
                 }
            /* All included? */
            if (allincluded) {
               printf("Diagnostic: All signals used in process '%s'\n"
                      "            are included in sensitivity list\n"
                      "            --> may be combinatorial\n", $1);
                      comb_tot++;
               }
            if (procsigcount) myfree((void *)&procsig);
            if (sensisigcount) myfree((void *)&sensisig);
            procsigcount=0;
            sensisigcount=0;

            processing_process=FALSE;
          }
        ;
pname1 : /* Empty */ {
           /* Creo e aggiungo il prefisso del blocco attuale */
           static nonameprocs=0;
           char tmp[8];
           sprintf(tmp, "p%d", nonameprocs++);
           strcat(sigprefix, tmp);
           strcat(sigprefix, "_");
           join(&$$, "%s", tmp);
           clk_in_sensi=FALSE;
           processing_process=TRUE;
           process_present=TRUE;
           firstline=TRUE;
           }
       | NAME ':' {
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, $1);
           strcat(sigprefix, "_");
           $$=$1;
           processing_process=TRUE;
           process_present=TRUE;
           clk_in_sensi=FALSE;
           firstline=TRUE;
           }
       ;
pname2 : /* Empty */
       | NAME { myfree(&$1); }
       ;
/* Sensitivity list */
psensi : /* Empty */
       | '(' sensilist ')'
       ;
/* Sensitivity list */
sensilist : signal {
              signal *sp;
              sp=findsig($1);
              if (sp==NULL) warning("Undeclared signal '%s'", $1);
              else {
                sensisig=myrealloc(sensisig, (++sensisigcount)*sizeof(signal *));
                sensisig[sensisigcount-1]=sp;
                }
              if (isclock($1)) {
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) clk_in_sensi=TRUE;
                }
              myfree(&$1);
              }
          | sensilist ',' signal {
              signal *sp;
              sp=findsig($3);
              if (sp==NULL) warning("Undeclared signal '%s'", $3);
              else {
                sensisig=myrealloc(sensisig, (++sensisigcount)*sizeof(signal *));
                sensisig[sensisigcount-1]=sp;
                }
              if (isclock($3)) {
                warning("Clock signal '%s' in sensilist", $3);
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) clk_in_sensi=TRUE;
                }
              myfree(&$3);
              }
          ;
/* Dichiarazione di variabili */
p_decl : /* Empty */
       | VARIABLE varnamelist ':' type var_init ';' p_decl
       | TYPE p_decl { warning("'type' statement ignored"); }
       | FIL p_decl { warning("'file' statement illegal"); }
       | ALIAS p_decl { warning("'alias' statement illegal"); }
       | ATTRIBUTE_STAT p_decl { warning("'attribute' statement ignored"); }
       | ASSERT p_decl { warning("'assert' statement illegal"); }
       | PROCEDURE p_decl { warning("'procedure' statement illegal"); }

       ;
varnamelist : NAME {
                addsig($1, TRUE); myfree(&$1);
                }
            | NAME ',' varnamelist {
                addsig($1, TRUE); myfree(&$1);
                }
            ;

var_init : /* Empty */
         | ':' '=' expr
         ;

/* Corpo del processo */
p_body : p_stat
       | p_stat p_body
       ;

/* Statements sequenziali */
p_stat : a_assign { firstline=FALSE; }
       | p_assign { firstline=FALSE; }
       | ifstat { firstline=FALSE; }
       | case { firstline=FALSE; }
       | loop { firstline=FALSE; }
       | next { firstline=FALSE; }
       | exit { firstline=FALSE; }
       | wait { firstline=FALSE; }
       ;
/* Assegnamento di variabili */
p_assign : NAME ':' '=' p_expr ';' {
             findsig($1)->state=FALSE;
             /* state is FALSE when a value has been assigned to a variable */
             /* (This is a different use of 'state' from 'v2c' sources) */
             myfree(&$1);
             }
         ;
/* if ... then ... else ... */
ifstat : IF p_exprc THEN p_body elsepart END IF ';' {
           /* If 'else' not found, probably is sequential */
           if (!elsefound) {
            printf("Diagnostic: 'if' without 'else' at line %d\n"
                   "            --> may be sequential\n", lineno);
/*              seq_flag=TRUE; */
             seq_tot++;
             }
           }
       ;
elsepart : /* Empty */
         | ELSIF p_exprc THEN p_body elsepart
         | ELSE p_body { elsefound=TRUE; }
         ;
p_expr : expr
       ;
p_exprc : exprc {
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
        }
        | p_expr { elsefound=FALSE; /* Initialize */ }
       ;

/* case ... is ... */
case : CASE p_expr IS caselist END CASE ';'
         ;
caselist : /* Empty */
         | WHEN choice '=' '>' p_body caselist
         | WHEN OTHERS '=' '>' p_body {
             printf("Diagnostic: 'other' statement at line %d:\n"
                    "            'case' may be a multiplexer\n"
                    "            --> may be combinatorial\n", lineno);
             comb_tot++;
             }
         ;
choice   : p_expr
         | p_expr '|' choice
         ;

/* while/for ... loop ... */
loop : lname1 loopscheme LOOP p_body END LOOP lname2 ';'
     ;
lname1 : /* Empty */
       | NAME ':' { myfree(&$1); }
       ;
lname2 : pname2
loopscheme : WHILE p_exprc
           | FOR NAME IN p_expr loopdir p_expr { myfree(&$2); }
           ;
loopdir    : TO {}
           | DOWNTO {}
           ;

/* next */
next : NEXT ';'
     ;

/* exit */
exit : EXIT ';'
     ;

/* wait ... */
wait     : WAIT waitcond ';'
         ;
waitcond : UNTIL exprc {
             if (clkcount>0) {
                printf("Diagnostic: Clock check at line %d\n"
                       "            --> sequential architecture\n", lineno);
/*              seq_flag=TRUE; */
                seq_tot+=10;
                }
             clkcount=0; /* Initialize */
             }
         | ON waitsig {
             if (waitclk) clk_in_sensi=TRUE;
             waitclk=FALSE;
             }
         ;
waitsig  : signal {
             if (isclock($1)) {
                signal *sp;
                sp=findsig($1);
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) waitclk=TRUE;
                }
             myfree(&$1);
             }
         | waitsig ',' signal {
             if (isclock($3)) {
                signal *sp;
                sp=findsig($3);
                if (sp!=NULL && sp->size==1 && sp->dir==_IN) waitclk=TRUE;
                }
             myfree(&$3);
             }
         ;
%%

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
