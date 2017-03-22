/* v2c.y */
/* by Cristian Ghezzi - (c) 1995 */

%{
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

%}

%union {
       char * txt;  /* String */
       int n;       /* Value  */
       expdata * e; /* For expressions */
       sigdata * s; /* For signals     */
       }

%token <txt> REM ENTITY IS PORT IN OUT INOUT END
%token <n>   BIT STD_ULOGIC_VECTOR INTEGER RANGE
%token <txt> ARCHITECTURE OF SIGNAL BEGN
%token <txt> NOT AFTER UNIT TO DOWNTO
%token <txt> NAME STRING
%token <n>   NATURAL
%token <txt> AND OR XOR
%token <txt> WHEN ELSE WITH SELECT OTHERS
%token <txt> BLOCK
%token <txt> PROCESS VARIABLE IF THEN ELSIF CASE LOOP WHILE FOR
%token <txt> NEXT EXIT WAIT UNTIL ON
%token <txt> LASTVALUE EVENT

%type <txt> trad rem remlist archi a_decl decl_init a_body signame signamelist
%type <s>   signal vec_range
%type <txt> a_stat a_assign sigvalue with selectlist
%type <txt> block bname1 b_decl b_body blockguard
%type <txt> process pname1 pname2 psensi p_decl
%type <txt> varnamelist var_init p_body _varinitcopy
%type <txt> p_stat p_assign ifstat elsepart p_expr p_exprc
%type <txt> case caselist choice
%type <txt> loop lname1 lname2 loopscheme next exit wait waitcond
%type <n>   loopdir
%type <n>   dir type
%type <e>   expr
%type <txt> exprc conf

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

/* Input file must contain entity declaration followed by architecture */
trad  : rem entity rem
        archi rem {
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
          join(&$$, "%s%s%s%s", $1, $3, $4, $5); puts($$);
          myfreen(5, &$$, &$1, &$3, &$4, &$5);
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
          }
      ;

/* Comments */
rem      : /* Empty */ { join(&$$, ""); }
         | remlist {
              join(&$$, "%s/*%s */\n", indent, $1);
              myfree(&$1); }
         ;
remlist  : REM /* $$=$1 automatic */
         | REM remlist {
               join(&$$, "%s\n%s *%s", $1, indent, $2);
               myfreen(2, &$1, &$2);
               }
         ;

/* Entity */
entity    : ENTITY NAME IS portstats END NAME ';' {
              join(&e_name, "%s", StringToLower($2));
              myfree(&$2);
              /* Inizialization of variables
                 used in the architecture translation */
              sigprefix[0]=0;
              indent[0]=0;
              process_present=FALSE;
              vlib_f=FALSE;
              if (!cq) needchg=TRUE; /* Sequential */
              }
          ;
portstats : PORT '(' portlist ')' ';' { }
          | PORT '(' portlist ')' ';' portstats { }
          ;
portlist  : signamelist ':' dirtype { myfree(&$1); }
          | signamelist ':' dirtype ';' portlist { myfree(&$1); }
          ;

/* When a signal with unknown direction and type is encountered, it is
   added to 'tmpslist[]' through a call to 'addtmpsig()' ... */
signamelist : NAME {
                if (match($1, ignores)) /* Clock */
                   join(&$$, "");
                else {
                   addtmpsig($1);
                   join(&$$, "new[%s]=%%s", $1); /* returns "old[name]=%s" */
                   }
                myfree(&$1);
                }
            | signamelist ',' NAME {
                if (match($3, ignores)) /* Clock */
                   join(&$$, "");
                else {
                   addtmpsig($3);
                   join(&$$, "%s, new[%s]=%%s", $1, $3); /* old[nm]=%s, old[nm]=%s */
                   }
                myfree(&$3);
                }
            ;
/* ... and when direction and type are later found, the signal list is compiled */
dirtype     : dir type {
                copytmpslist($1, $2, TRUE, &lastfromto); /* TRUE = signal in state */
                }
            ;
dir         : IN { $$=_IN; }
            | OUT { $$=_OUT; }
            ;
/* The value of 'type' is the length of the signal in bits */
/* 'lasttype' is used by '_docopy' to inherit the attribute */
/* Idem for 'lastfromto' */
type        : BIT { $$=1; lasttype=$$; lastfromto.from=0; lastfromto.to=1; }
            | STD_ULOGIC_VECTOR '(' vec_range ')' {
                $$=$3->rleft-$3->rright+1; /* (x to y) !! */
                lasttype=$$;
                lastfromto.from=0; lastfromto.to=(1<<$$)-1; /* (x to y) !!*/
                myfree((char **)&$3);
                }
            | INTEGER {
                int min, max;
                $$=integersize;
                lasttype=$$;
                min=-(1<<$$-1); max=(1<<$$-1)-1;
                lastfromto.from=min;
                lastfromto.to=max;
                }
            | INTEGER RANGE NATURAL TO NATURAL {
                $$=bits($5-$3);
                lasttype=$$;
                lastfromto.from=$3;
                lastfromto.to=$5;
                }
            ;
vec_range : NATURAL DOWNTO NATURAL {
              $$=(sigdata *)mymalloc(sizeof(sigdata));
              $$->rleft=$1;
              $$->rright=$3;
              }
          | NATURAL {
              $$=(sigdata *)mymalloc(sizeof(sigdata));
              $$->rleft=$1;
              $$->rright=$1; /* Same means 'bit' to addchgsig() */
              }
          ;
       /* | NATURAL TO NATURAL !!
          Se si considera il TO, bisogna stare attenti ai vettori costanti
          tipo "1010" e ai concatenamenti con "&" e a eventuali
          inversioni assegnando tra segnali di direzione diversa. */

/* Architecture */
archi : ARCHITECTURE NAME OF NAME IS a_decl
        BEGN doindent a_body END NAME ';' unindent {
          char *t1, *t2, *t3, *t4, *o1, *o2, *o6, *o7, *o8, *o9, *oA;
          /* Consistency check */
          if (strcmp(e_name, StringToLower($4))!=0) warning("Entity %s not found", $4);
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

          join(&$$, "void %s(int in_data[], int out_data[])\n" /**/
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
                    StringToLower($4), t1=make_enum(), o7, o6, t2=make_newinit(),
                    o1, t3=make_newinput(), $6, o2, $9, o9, oA, o2, t4=make_outdataend());
                    myfreen(16, &$2, &$4, &$6, &$9, &$11, &t1,
                    &t2, &t3, &t4, &o1, &o2, &o6, &o7, &o8, &o9, &oA);
          }
      ;
/* Extends indentation by one level */
doindent : /* Empty */ { strcat(indent, INDENTS); }
         ;
/* Shorten indentation by one level */
unindent : /* Empty */ { indent[strlen(indent)-INDENTL]=0; }
         ;
/* Declarative part of the architecture */
a_decl    : rem /* $$=$1 */
          | rem SIGNAL signamelist ':' type decl_init ';' _docopy a_decl
              {
              /* signamelist contains "old[x]=%s, ... old[y]=%s" */
              /* '_docopy' inherits from 'type' through 'lasttype' */
              char *init;
              init=mymalloc(1); init[0]=0;
              if ($6!=NULL) {
                 char *tmp;
                 tmp=strreplace($3, "%s", $6); /* Replace %s with $6 */
                 init=myrealloc(init, strlen(tmp)+strlen(";\n")+strlen(indent)+1);
                 sprintf(init, "%s%s;\n", indent, tmp);
                 myfreen(2, &tmp, &$6);
                 }
              join(&$$, "%s%s%s", $1, init, $9);
              myfreen(4, &$1, &init, &$3, &$9);
              }
          ;
_docopy : /* Empty */ { copytmpslist(_NONE, lasttype, TRUE, &lastfromto); }
                        /* Internal signals don't have a direction: '_NONE' */
        ;
decl_init : /* Empty */ { $$=NULL; }
          | ':' '=' expr {
             join(&$$, "%s", $3->txt);
             myfreen(2, &$3->txt, &$3);
             }
          ;

/* Architecture body */
a_body : rem a_stat rem {
           join(&$$, "%s%s%s", $1, $2, $3);
           myfreen(3, &$1, &$2, &$3);
           }
       | rem a_stat a_body {
           join(&$$, "%s%s%s", $1, $2, $3);
           myfreen(3, &$1, &$2, &$3);
           }
       ;
a_stat : a_assign
       | with
       | block
       | process
       ;
/* Algebric expressions */
expr : NAME {
         signal *sp;
         sp=findsig($1);
         if (sp==NULL && !excludevar($1)) warning("Name '%s' not declared", $1);
         /* Maybe something illegal passes this test, but who cares? */
         /* Loop variables will be signalled */
         $$=(expdata *)mymalloc(sizeof(expdata));
         if (sp && !sp->var) { /* signal */
            addchgsig(sp->name, -1, -1);
            $$->size=sp->size;
            join(&$$->txt, "old[%s]", sp->name);
            }
         else if (sp) { /* variable */
            join(&$$->txt, "%s", sp->name);
            }
         else join(&$$->txt, "%s", $1); /* Excluded variab. or loop var. or mistake */
         if (match($1, ignores)) {
            ignorethis=TRUE; /* Ignored signal */
            warning("Signal %s ignored", $1);
            }
         myfree(&$1);
         }
     | signame '(' vec_range ')' {
         vlib_f=TRUE;
         $$=(expdata *)mymalloc(sizeof(expdata));
         addchgsig($1, $3->rleft, $3->rright);
         $$->size=$3->rleft-$3->rright+1; /* occhio a (x to y) !! */
         if ($3->rleft != $3->rright) { /* signal(x downto y) */
            join(&$$->txt, "vpart(old[%s], %d, %d)",
                           $1, $3->rleft, $3->rright);
            }
         else { /* signal(x) */
            join(&$$->txt, "vbit(old[%s], %d)", $1, $3->rleft);
            }
         myfreen(2, &$1, &$3);
         }
     | NATURAL {
         $$=(expdata *)mymalloc(sizeof(expdata));
         $$->size=integersize;
         join(&$$->txt, "%d", $1);
         }
     | '\'' NATURAL '\'' { /* !! Controllare che sia una cifra sola !! */
         if ($2>9) warning("Value '%d' should be one character", $2);
         $$=(expdata *)mymalloc(sizeof(expdata));
         $$->size=1;
         join(&$$->txt, "%d", $2);
         }
     | STRING {
         $$=(expdata *)mymalloc(sizeof(expdata));
         $$->size=strlen($1);
         /* Binary strings are replaced with their value */
         join(&$$->txt, "%d", vval($1)); myfree(&$1);
         vlib_f=TRUE;
         }
     | expr '&' expr { /* Vector chaining */
         $$=(expdata *)mymalloc(sizeof(expdata));
         $$->size=$1->size+$3->size;
         join(&$$->txt, "vcat(%s, %s, %d)", $1->txt, $3->txt, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3);
         vlib_f=TRUE;
         }
     | '-' expr %prec UNARYMINUS {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "-%s", $2->txt);
         $$->size=$2->size;
         myfreen(2, &$2->txt, &$2); }
     | '+' expr %prec UNARYPLUS {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "+%s", $2->txt);
         $$->size=$2->size;
         myfreen(2, &$2->txt, &$2); }
     | expr '+' expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s+%s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr '-' expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s-%s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr '*' expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s*%s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr '/' expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s/%s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | NOT expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         $$->size=$2->size;
         join(&$$->txt, "~%s", $2->txt); myfreen(2, &$2->txt, &$2); }
     | expr AND expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s & %s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr OR expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s | %s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr XOR expr {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "%s ^ %s", $1->txt, $3->txt);
         $$->size=BIGGER($1->size, $3->size);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | '(' expr ')' {
         $$=(expdata *)mymalloc(sizeof(expdata));
         join(&$$->txt, "(%s)", $2->txt);
         $$->size=$2->size;
         myfreen(2, &$2->txt, &$2); }
     | NAME '\'' LASTVALUE {
         signal *sp;
         sp=findsig($1);
         if (sp==NULL && !excludevar($1)) warning("Name '%s' not declared", $1);
         $$=(expdata *)mymalloc(sizeof(expdata));
         if (sp && !sp->var) { /* signal */
            addchgsig(sp->name, -1, -1);
            $$->size=sp->size;
            join(&$$->txt, "lst[%s]", sp->name);
            needlst=TRUE;
            }
         else if (sp) { /* variable */
            warning("Illegal attribute on variable %s", $1);
            join(&$$->txt, "%s", sp->name);
            }
         else if (!match($1, ignores)) { /* Excluded variable or mistake */
           warning("Can't get last value of %s", $1);
           join(&$$->txt, "%s", $1);
          }
         else { /* Ignored signal */
           join(&$$->txt, "1 /* %s ignored */", ignores);
         }
         myfree(&$1);
         }

     ;

_resetignore: /* Null */ { ignorethis=FALSE; }
            ;

/* Conditional expressions */
exprc : conf { ignorethis=FALSE; }
      | '(' exprc ')' {
         join(&$$, "(%s)", $2);
         myfree(&$2); }
      | exprc AND exprc %prec ANDL {
         join(&$$, "%s && %s", $1, $3);
         myfreen(2, &$1, &$3); }
      | exprc OR exprc %prec ORL {
         join(&$$, "%s || %s", $1, $3);
         myfreen(2, &$1, &$3); }
      | NOT exprc %prec NOTL {
         join(&$$, "!%s", $2);
         myfree(&$2); }
     | NAME '\'' EVENT {
         signal *sp;
         sp=findsig($1);
         if (sp==NULL && !excludevar($1)) warning("Name '%s' not declared", $1);
         if (sp && !sp->var) { /* signal */
            join(&$$, "old[%s]!=lst[%s]", sp->name, sp->name);
            needlst=TRUE;
            }
         else if (sp) { /* variable */
            warning("'EVENT' illegal on variable %s", $1);
            join(&$$, "%s", sp->name);
            }
         else if (!match($1, ignores)) { /* Excluded variable or mistake */
           warning("Can't get last value of %s", $1);
           join(&$$, "%s", $1);
          }
         else { /* Ignored signal */
           join(&$$, "1 /* %s ignored */", ignores);
         }
         myfree(&$1);
         }
      ;

/* Comparisons */
conf : expr '=' expr %prec EQUAL {
         if (ignorethis) join(&$$, "1 /* %s ignored */", ignores);
         else join(&$$, "%s==%s", $1->txt, $3->txt);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr '>' expr {
         if (ignorethis) join(&$$, "1 /* %s ignored */", ignores);
         else join(&$$, "%s>%s", $1->txt, $3->txt);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr '>' '=' expr %prec BIGEQ {
         if (ignorethis) join(&$$, "1 /* %s ignored */", ignores);
         else join(&$$, "%s>=%s", $1->txt, $4->txt);
         myfreen(4, &$1->txt, &$4->txt, &$1, &$4); }
     | expr '<' expr {
         if (ignorethis) join(&$$, "1 /* %s ignored */", ignores);
         else join(&$$, "%s<%s", $1->txt, $3->txt);
         myfreen(4, &$1->txt, &$3->txt, &$1, &$3); }
     | expr '<' '=' expr %prec LESSEQ {
         if (ignorethis) join(&$$, "1 /* %s ignored */", ignores);
         else join(&$$, "%s<=%s", $1->txt, $4->txt);
         myfreen(4, &$1->txt, &$4->txt, &$1, &$4); }
     | expr '<' '>' expr %prec NOTEQ {
         if (ignorethis) join(&$$, "1 /* %s ignored */", ignores);
         else join(&$$, "%s!=%s", $1->txt, $4->txt);
         myfreen(4, &$1->txt, &$4->txt, &$1, &$4); }
     ;

/* --- Concurrent statements --- */

/* Assegnamento di un valore a un segnale */
a_assign : signal '<' '=' sigvalue {
           char *t1;
           t1=make_chglist();
           /* Se l'assegnamento e' sensibile ad altri segnali, *
            * si inserisce la condizione (se non sequenziale). */
           if (*t1!=0 && cq==FALSE)
              join(&$$, "%sif (%s) {\n"
                        "%s   %s"
                        "%s   }\n",
                        indent, t1,
                        indent, $4,
                        indent);
           else
              join(&$$, "%s%s",
                        indent, $4);
           myfreen(4, &$1->name, &$1, &$4, &t1);
           }
         ;
signal   : signame {
             /* 'lastsigasg' e' usato da 'sigvalue'; puo' contenere: *
              * new[signal]=expr                                     *
              * vins(&new[signal], x, y, expr)                       *
              * vins(&new[signal], x, x, expr)                       */
             sprintf(lastsigasg, "new[%s]=%%s", $1);
             $$=(sigdata *)mymalloc(sizeof(sigdata));
             $$->rleft=-1;
             $$->rright=-1;
             join(&$$->name, "%s", $1); myfree(&$1); }
         | signame '(' vec_range ')' { /* segnale(x downto y) */
                                       /* segnale(x)          */
             vlib_f=TRUE;
             sprintf(lastsigasg, "vins(&new[%s], %d, %d, %%s)",
                                 $1, $3->rleft, $3->rright);
             $$=(sigdata *)mymalloc(sizeof(sigdata));
             $$->rleft=$3->rleft;
             $$->rright=$3->rright;
             join(&$$->name, "%s", $1); myfreen(2, &$1, &$3); }
         ;
signame  : NAME {
             signal *sp;
             sp=findsig($1);
             /* Controllo di consistenza */
             if (sp==NULL || sp->var) {
                if (!match($1, ignores))
                   warning("%s is not a signal", $1);
                join(&$$, "%s", $1);
                }
             else join(&$$, "%s", sp->name);
             myfree(&$1);
             }
         ;
sigvalue : expr delay ';' {
             sprintf(tmpbuf, lastsigasg, $1->txt);
             join(&$$, "%s;\n", tmpbuf);
             myfreen(2, &$1->txt, &$1);
             }
         | expr delay WHEN _resetignore exprc';' {
             sprintf(tmpbuf, lastsigasg, $1->txt);
             join(&$$, "if (%s) %s;\n", $5, tmpbuf);
             myfreen(3, &$1->txt, &$1, &$5);
             }
         | expr delay WHEN _resetignore exprc ELSE sigvalue {
             sprintf(tmpbuf, lastsigasg, $1->txt);
             join(&$$, "if (%s) %s;\n"
                       "%s   else %s",
                       $5, tmpbuf,
                       indent, $7);
             myfreen(4, &$1->txt, &$1, &$5, &$7);
             }
         ;
delay    : /* empty */ { }
         | AFTER NATURAL UNIT {
             warning("Delay not yet implemented");
             }
         ;

/* With ... select ... */
with : WITH expr SELECT signal '<' '=' selectlist {
         char *t1=make_chglist();
         if (cq==FALSE)
            join(&$$, "%sif (%s) {\n"
                      "%s%sswitch (%s) {\n"
                      "%s"
                      "%s%s%s}\n"
                      "%s%s}\n",
                      indent, t1,
                      indent, INDENTS, $2->txt,
                      $7,
                      indent, INDENTS, INDENTS,
                      indent, INDENTS);
          else
            join(&$$, "%sswitch (%s) {\n"
                      "%s"
                      "%s%s}\n",
                      indent, $2->txt,
                      $7,
                      indent, INDENTS);
          myfreen(6, &$2->txt, &$2, &$4->name, &$4, &$7, &t1);
          }
     ;
selectlist : expr WHEN expr ';' {
               sprintf(tmpbuf, lastsigasg, $1->txt);
               join(&$$, "%s      case %s : %s; break;\n"
                         , indent, $3->txt, tmpbuf);
               myfreen(4, &$1->txt, &$3->txt, &$1, &$3);
               }
           | expr WHEN OTHERS ';' {
               sprintf(tmpbuf, lastsigasg, $1->txt);
               join(&$$, "%s      default : %s;\n"
                         , indent, tmpbuf);
               myfreen(2, &$1->txt, &$1);
               }
           | expr WHEN expr ',' selectlist {
               sprintf(tmpbuf, lastsigasg, $1->txt);
               join(&$$, "%s      case %s : %s; break;\n"
                         "%s"
                         , indent, $3->txt, tmpbuf
                         , $5);
               myfreen(5, &$1->txt, &$3->txt, &$1, &$3, &$5);
               }
           ;

block: bname1 BLOCK blockguard doindent b_decl BEGN b_body unindent
       END BLOCK bname2 ';' {
         char *point;
         join(&$$, $3, /* ...%s...%s...%s...%s... */
                   $1, /* bname1 */
                   $5, /* b_decl */
                   $7, /* b_body */
                   $1); /* bname1 */
         myfreen(4, &$1, &$3, &$5, &$7);
         /* Tolgo il prefisso del blocco attuale */
         sigprefix[strlen(sigprefix)-1]='\0';
         point=strrchr(sigprefix, '_');
         if (point==NULL) point=sigprefix;
         *point='\0';
         }
         ;
bname1 : NAME ':' {
           $$=$1;
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, $1);
           strcat(sigprefix, "_");
           }
       ;
bname2 : /* Null */
       | NAME { myfree(&$1); } /* NAME not used */
       ;
blockguard : /* Null */ {
               join(&$$, "%s/* Block %%s: */\n"  /* bname1 */
                         "%%s"                   /* b_decl */
                         "%%s"                   /* b_body */
                         "%s/* End of %%s */\n", /* b_name1 */
                        indent, indent);
               make_chglist(); /* Pulisce: non ci interessa */
               }
           | '(' _resetignore exprc ')' {
               join(&$$, "%s/* Block %%s: */\n"  /* bname1 */
                         "%sif (%s) {\n"
                         "%%s"                   /* b_decl */
                         "%%s"                   /* b_body */
                         "%s}\n"
                         "%s/* End of %%s */\n", /* b_name1 */
                        indent, indent, $3, indent, indent);
               myfree(&$3);
               make_chglist(); /* Pulisce: non ci interessa */
               }
           ;
b_decl : a_decl {
            /* Replace 'new[]' with 'old[]' */
            char *tmp;
            tmp=strreplace($1, "new[", "old[");
            join(&$$, "%s", tmp);
            myfree(&tmp);
            }
       ;
b_body : a_body
       ;


/* --- Processi sequenziali --- */

process : pname1 PROCESS psensi doindent p_decl _varinitcopy BEGN p_body unindent
          END PROCESS pname2 ';' {
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
            sprintf(tmpbuf, "%s%s%s", $1, $3, $12);
            join(&$$, tmpbuf, $5, w1, $6, $8, proclabel);
            myfreen(7, &w1, &$1, &$3, &$5, &$6, &$8, &$12);
            /* Tolgo il prefisso del blocco attuale */
            sigprefix[strlen(sigprefix)-1]='\0';
            point=strrchr(sigprefix, '_');
            if (point==NULL) point=sigprefix;
            *point='\0';
            if (proclabel) myfree(&proclabel);
            }
        ;
/* Nome all'inizio del processo -> commento */
pname1 : /* Empty */ {
           /* Creo e aggiungo il prefisso del blocco attuale */
           static nonameprocs=0;
           char tmp[8];
           sprintf(tmp, "p%d", nonameprocs++);
           strcat(sigprefix, tmp);
           strcat(sigprefix, "_");
           join(&$$, "%s/* %s: */\n", indent, tmp);
           }
       | NAME ':' {
           /* Aggiungo il prefisso del blocco attuale */
           strcat(sigprefix, $1);
           strcat(sigprefix, "_");
           join(&$$, "%s/* %s: */\n", indent, $1); myfree(&$1); }
       ;
/* Nome alla fine del processo -> commento */
pname2 : /* Empty */ { join(&$$, ""); }
       | NAME { join(&$$, "%s/* End of %s */\n", indent, $1); myfree(&$1); }
       ;
/* Sensitivity list */
psensi : /* Empty */ {
           /* Senza sensitivity: nessun controllo sui segnali */
           waitnum=0;
           join(&$$, "%s{\n"
                     "%%s" /* Questo diverra' il p_decl */
                     "%%s" /* Questo diverra' il waitswitch */
                     "%s%s%%s" /* Questo diverra' il _varinitcopy */
                     "%%s" /* Questo diverra' il p_body */
                     "%s}\n"
                     "%%s", /* Questo diverra' proclabel */
                     indent, INDENTS, indent, indent);
           /* Ora 'psensi' contiene '{%s%s%s%s}%s' opportunamente indentato */
           }
       | '(' sensilist ')' {
           /* Con sensitivity: controllo sui segnali... */
           char *t1;
           waitnum=0;
           t1=make_chglist();
           /* ...ma solo se sequenziale */
           if (cq==FALSE && t1[0]!=0) { /* Sequenziale con segnali non ignorati */
              join(&$$, "%sif (%s) {\n"
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
              join(&$$, "%s{\n"
                        "%%s" /* Questo diverra' il p_decl */
                        "%%s" /* Questo diverra' il waitswitch */
                        "%s%s%%s" /* QUesto diverra' il _varinitcopy */
                        "%%s" /* Questo diverra' il p_body */
                        "%s}\n"
                        "%%s", /* Questo diverra' proclabel */
                        indent, INDENTS, indent, indent);
             }
           myfree(&t1);
           }
       ;
/* Sensitivity list */
sensilist : signal {
              if (!match($1->name, ignores)) /* Not ignored */
                 addchgsig($1->name, $1->rleft, $1->rright);
              else
                 warning("Sensitivity signal '%s' ignored", $1->name);
              myfreen(2, &$1->name, &$1); }
          | sensilist ',' signal {
              if (!match($3->name, ignores)) /* Not ignored */
                 addchgsig($3->name, $3->rleft, $3->rright);
              else
                 warning("Sensitivity signal '%s' ignored", $3->name);
              myfreen(2, &$3->name, &$3); }
          ;
/* Dichiarazione di variabili */
p_decl : rem
       | rem VARIABLE varnamelist ':' type var_init ';' p_decl
           {
           char *tmp1;
           if (lastvarinitstr!=NULL)
              warning("Internal error - 'lastvarinitstr' not cleared");
           lastvarinitstr=$6;
           tmp1=mymalloc(strlen(indent)+strlen("static int ;\n")+strlen($3)+1);
           tmp1[0]=0;
           if (*($3)) {
              sprintf(tmp1, "%sstatic int %s;\n", indent, $3);
              }
           join(&$$, "%s"
                     "%s" /* static int ... */
                     "%s",
                     $1,
                     tmp1,
                     $8);
           myfreen(4, &$1, &$3, &$8, &tmp1);
           }
       ;
_varinitcopy: /* Null */ {
           if (lastvarinitstr) { /* Initialization */
              int i=0;
              char *tmp1;
              $$=mymalloc(1); $$[0]=0;
              for (i=0; i<varinitnum; i++) {
                 tmp1=mymalloc(strlen(varinitlist[i])+strlen("=, ")
                               +strlen(lastvarinitstr)+1);
                 sprintf(tmp1, "%s=%s, ", varinitlist[i], lastvarinitstr);
                 $$=myrealloc($$, strlen($$)+strlen(tmp1)+1);
                 strcat($$, tmp1);
                 myfree(&tmp1);
                 }
              $$[strlen($$)-2]=';';
              $$[strlen($$)-1]='\n';
/*            $$[strlen($$)]=0; Already there */
              myfree(&lastvarinitstr);
              }
           else join(&$$, "");
           while (varinitnum)
              myfree(varinitlist+(--varinitnum)); /* Automatically NULLed */
           }
           ;
varnamelist : NAME {
                /* Le variabili vengono messe in lista solo se devono
                   far parte dello stato; sarebbe meglio metterle sempre,
                   settando opportunamente il field '->state' da dentro
                   ad addsig() usando excludevar() !! */
                if (!excludevar($1)) { /* Put variable in state */
                   addsig($1, TRUE);
                   /* Null string ==> Variable in state */
                   join(&$$, "");
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen($1)+strlen(sigprefix)+1);
                   strcpy(varinitlist[varinitnum], sigprefix);
                   strcat(varinitlist[varinitnum++], $1);
                   }
                else {
                   warning("Variable %s excluded from state", $1);
                   join(&$$, "%s", $1); /* name */
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen($1)+1);
                   strcpy(varinitlist[varinitnum++], $1);
                   }
                myfree(&$1);
                }
            | NAME ',' varnamelist {
                if (!excludevar($1)) {
                   addsig($1, TRUE);
                   join(&$$, "%s", $3); /* $$=$3 is dangerous */
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen($1)+strlen(sigprefix)+1);
                   strcpy(varinitlist[varinitnum], sigprefix);
                   strcat(varinitlist[varinitnum++], $1);
                   }
                else {
                   warning("Variable %s excluded from state", $1);
                   if (*($3)!=0) {
                      join(&$$, "%s, %s", $1, $3); /* name, name ... */
                      }
                   else {
                      join(&$$, "%s", $1);
                      }
                   /* Initialization list */
                   varinitlist[varinitnum]=mymalloc(strlen($1)+1);
                   strcpy(varinitlist[varinitnum++], $1);
                   }
                myfreen(2, &$1, &$3);
                }
            ;
var_init : /* Empty */ { $$=NULL; }
         | ':' '=' expr {
            join(&$$, "%s", $3->txt);
            myfreen(2, &$3->txt, &$3);
            }
         ;

/* Corpo del processo */
p_body : rem p_stat rem {
           join(&$$, "%s%s%s", $1, $2, $3);
           myfreen(3, &$1, &$2, &$3);
           }
       | rem p_stat p_body {
           join(&$$, "%s%s%s", $1, $2, $3);
           myfreen(3, &$1, &$2, &$3);
           }
       ;

/* Statements sequenziali */
p_stat : a_assign
       | p_assign
       | ifstat
       | case
       | loop
       | next
       | exit
       | wait
       ;
/* Assegnamento di variabili */
p_assign : NAME ':' '=' p_expr ';' {
           signal *sp;
           sp=findsig($1);
           if (sp==NULL) {
              if (!excludevar($1)) warning("Variable '%s' not declared", $1);
              /* Maybe something illegal passes this test, bu who cares? */
              join(&$$, "%s%s=%s;\n", indent, $1, $4);
              }
           else join(&$$, "%s%s=%s;\n", indent, sp->name, $4);
           myfreen(2, &$1, &$4);
           }
         ;
/* if ... then ... else ... */
ifstat : IF _resetignore p_exprc THEN doindent p_body unindent elsepart END IF ';' {
           join(&$$, "%sif (%s) {\n"
                     "%s" /* p_body */
                     "%s%s}\n"
                     "%s", /* elsepart */
                     indent, $3,
                     $6,
                     indent, INDENTS,
                     $8);
           myfreen(3, &$3, &$6, &$8);
           }
       ;
elsepart : /* Empty */ { join(&$$, ""); }
         | ELSIF _resetignore p_exprc THEN doindent p_body unindent elsepart {
             join(&$$, "%selse if (%s) {\n"
                       "%s"
                       "%s%s}\n"
                       "%s",
                       indent, $3,
                       $6,
                       indent, INDENTS,
                       $8);
             myfreen(3, &$3, &$6, &$8);
           }
         | ELSE doindent p_body unindent {
             join(&$$, "%selse {\n"
                       "%s"
                       "%s%s}\n",
                       indent,
                       $3,
                       indent, INDENTS);
             myfree(&$3);
           }
         ;
p_expr : expr {
           join(&$$, "%s", $1->txt);
           myfreen(2, &$1->txt, &$1);
           make_chglist(); /* Pulisce: non ci interessa */
           }
       ;
p_exprc : exprc {
           join(&$$, "%s", $1);
           myfree(&$1);
           make_chglist(); /* Pulisce */
           }
        | p_expr /* Per espressioni tipo 'IF exists THEN' */
       ;

/* case ... is ... */
case : CASE p_expr IS doindent caselist unindent END CASE ';' {
             join(&$$, "%sswitch (%s) {\n"
                       "%s"
                       "%s}\n",
                       indent, $2,
                       $5,
                       indent);
             myfreen(2, &$2, &$5);
             }
         ;
caselist : /* Empty */ { join(&$$, ""); }
         | WHEN choice '=' '>' doindent p_body unindent caselist {
             join(&$$, "%s%s\n" /* choice */
                       "%s" /* p_body */
                       "%s%sbreak;\n"
                       "%s", /* caselist */
                       indent, $2,
                       $6,
                       indent, INDENTS,
                       $8);
             myfreen(3, &$2, &$6, &$8);
             }
         | WHEN OTHERS '=' '>' doindent p_body unindent {
             join(&$$, "%sdefault:\n" /* choice */
                       "%s", /* p_body */
                       indent,
                       $6);
             myfree(&$6);
             }
         ;
choice   : p_expr {
             join(&$$, "case %s: ", $1);
             myfree(&$1);
             }
         | p_expr '|' choice {
             join(&$$, "case %s: %s", $1, $3);
             myfreen(2, &$1, &$3);
             }
         ;

/* while/for ... loop ... */
loop : lname1 loopscheme LOOP doindent p_body unindent END LOOP lname2 ';' {
         sprintf(tmpbuf, "%s%s%s", $1, $2, $9);
         join(&$$, tmpbuf, $5);
         myfreen(4, &$1, &$2, &$5, &$9);
         }
     ;
lname1 : /* Empty */ { join(&$$, ""); }
       | NAME ':' { join(&$$, "%s/* %s: */\n", indent, $1); myfree(&$1); }
       ;
lname2 : pname2
loopscheme : WHILE _resetignore p_exprc {
               join(&$$, "%swhile (%s) {\n"
                         "%%s" /* p_body */
                         "%s%s}\n",
                         indent, $3,
                         indent, INDENTS);
               myfree(&$3);
               }
           | FOR NAME IN p_expr loopdir p_expr {
               int mm='?', pm='?';
               if ($5==1) { mm='<'; pm='+'; } /* TO */
               if ($5==-1) { mm='>'; pm='-'; } /* DOWNTO */
               join(&$$, "%s{\n"
                         "%sint %s;\n"
                         "%sfor (%s=%s; %s%c=%s; %s%c%c) {\n"
                         "%%s"
                         "%s%s}\n"
                         "%s}\n",
                         indent,
                         indent, $2,
                         indent, $2, $4, $2, mm, $6, $2, pm, pm,
                         indent, INDENTS,
                         indent);
               myfreen(3, &$2, &$4, &$6);
               }
           ;
loopdir    : TO { $$=1; }
           | DOWNTO { $$=-1; }
           ;

/* next */
next : NEXT ';' { join(&$$, "%scontinue;\n", indent); }
     ;

/* exit */
exit : EXIT ';' { join(&$$, "%sbreak;\n", indent); }
     ;

/* wait ... */
wait     : WAIT waitcond ';' {
             char *t1;
             if (proclabel==0) proclabel=make_proclabel();
             waitnum++;
             sprintf(tmpbuf, "case %d: goto %s;\n",
                             waitnum, t1=make_waitlabel());
             addwaitcase(tmpbuf, waitnum);
             join(&$$, "%s%s:\n"
                       "%sif (!(%s)) {\n"
                       "%s   "WAITINDEXNAME"=%d;\n"
                       "%s   goto %s;\n"
                       "%s   }\n",
                       indent, t1,
                       indent, $2,
                       indent, waitnum,
                       indent, proclabel,
                       indent);
             myfreen(2, &$2, &t1);
             }
         ;
waitcond : UNTIL _resetignore exprc {
             join(&$$, "%s", $3);
             myfree(&$3);
             make_chglist(); /* Pulisce */
             }
         | ON waitsig {
             char *t1;
             join(&$$, "%s", t1=make_chglist());
             needchg=TRUE;
             myfree(&t1);
             }
         ;
waitsig  : signal { addchgsig($1->name, $1->rleft, $1->rright);
                    myfreen(2, &$1->name, &$1); }
         | waitsig ',' signal { addchgsig($3->name, $3->rleft, $3->rright);
                                myfreen(2, &$3->name, &$3); }
         ;
%%



/* End of v2c.y */
