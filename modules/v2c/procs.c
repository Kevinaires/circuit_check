/* procs.c */
/* by Cristian Ghezzi - (c) 1995 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "defs.h"
#include "procs.h"
#include "match.h"

/* Coi SUN la sprintf ritorna un puntatore alla stringa */
#ifdef SUN_OS
 #define SPRSIZE(x) strlen(x)
#else
 #define SPRSIZE(x) x
#endif

#define MAXCHGSIG 256

extern int yydebug;

char *ignores=NULL; /* Signal to be ignored */
int integersize=_INTEGERSIZE;
char **exclude=NULL; /* Lista dei pattern da escludere dallo stato */
BOOL cq=FALSE; /* Presenza del flag '-c' */

char sigprefix[1024]; /* Prefisso per segnali nei blocks */
signal **tmpslist; /* Elenco temporaneo di puntatori a segnali */
int tmpslist_size=0;
int tmpslist_alloc=10;
chgsignal *chglist[MAXCHGSIG]; /* Elenco di segnali cambiati */
int chglist_size=0;
char **waitcase; /* Elenco stringhe di case */
int waitcase_alloc=10;

int tot_in=0, tot_out=0; /* Numero totale segnali di IN e di OUT */

int outdata0size=0;

signal *shead, *stail; /* Lista dei segnali */
int lineno=1;

char indent[256]="";  /* Indentation string */




char * StringToLower(char * String)
/* Converts the upper-case characters of String in lower-case ones. */
{
char * result = String;
if (!String) return(result);
for (; *String; ++String)
    *String = tolower(*String);
return(result);
}



char *strreplace(char *str, char *from, char *to)
/* Replace every occurrence of substring 'from' in 'str' with 'to' */
{
char *p, *newstr;
char oldc;
int lenfrom, lento;
lenfrom=strlen(from);
lento=strlen(to);
newstr=mymalloc(1); newstr[0]=0;
do {
   p=strstr(str, from); /* Search substring */
   if (p==NULL) { /* No more found */
      newstr=myrealloc(newstr, strlen(newstr)+strlen(str)+1);
      strcat(newstr, str);
      return newstr;
      }
   oldc=*p; *p=0; /* Cut string */
   newstr=myrealloc(newstr, strlen(newstr)+strlen(str)+lento+1);
   strcat(newstr, str); strcat(newstr, to); /* Replace */
   *p=oldc; /* Rejoin string */
   str=p+lenfrom;
   } while(TRUE);
}



BOOL excludevar(char *var)
/* Check if var matches an element of the exclude-list */
{
int i=0;
if (!exclude) return FALSE;
while (exclude[i]!=NULL) if (match(exclude[i++], var)) return TRUE;
return FALSE;
}



void addwaitcase(char *str, int n)
{
if (waitcase_alloc<n)
   {
   waitcase_alloc+=10;
   waitcase=(char **)myrealloc(waitcase, waitcase_alloc*sizeof(char *));
   }
waitcase[n-1]=(char *)mymalloc(strlen(str)+1);
strcpy(waitcase[n-1], str);
}



char *make_waitcase(char *s, int n)
{
char *str=0;
int i;
str=(char *)mymalloc(1);
str[0]=0;
for (i=0; i<n; i++)
    {
    str=(char *)myrealloc(str, strlen(str)+strlen(s)+strlen(waitcase[i])+1);
    strcat(str, s);
    strcat(str, waitcase[i]);
    myfree(waitcase+i);
    }
return str;
}



int vval(char *str)
/* Ritorna il valore numerico della stringa binaria */
{
int i=0, val=0;
while (str[i]!=0)
   {
   val=(val<<1)+str[i++]-'0';
   }
return val;
}



char *make_waitlabel(void)
{
static wnum=0;
char *str;
str=(char *)mymalloc(strlen("_waitXX")+1);
sprintf(str, "_wait%0.2d", ++wnum);
return str;
}



char * make_proclabel(void)
{
char tmp[16];
char *s;
static pnum=0;
sprintf(tmp, "_proc%0.2d", ++pnum);
s=mymalloc(strlen(tmp)+1);
strcpy(s, tmp);
return s;
}



char *make_enum(void)
{
/* Crea lo statement per l'enumerazione dei segnali */
int a, s, nl=0;
BOOL v;
char *str, *strv;
char tmp[256];
signal *sp;
/* Enum dei segnali */
str=(char *)mymalloc(24+strlen(ignores)+1); /* Spazio per "enum segnale {" in eccesso ... */
strcpy(str, "enum segnale {");
if (*ignores) { strcat(str, ignores); strcat(str, ", "); }
sp=shead;
while (sp!=stail)
   {
   if (!sp->var) {
      tmp[0]=0;
      a=strlen(sp->name)+2; s=strlen(str); /* Bisogna contare 2 per ", " */
      if (s+a-nl>CHARS_PER_LINE) {
         strcpy(tmp, "\n              "); /* A capo */
         nl=s;
         }
      strcat(tmp, sp->name); strcat(tmp, ", ");
      str=(char *)myrealloc(str, s+strlen(tmp)+8); /* Spazio per "_MAX_);" */
      strcat(str, tmp);
      }
   sp=sp->next;
   }
strcat(str, "_MAX_};");

/* Dichiarazione delle variabili */
strv=(char *)mymalloc(20); /* Spazio per "\nint " in eccesso ... */
strcpy(strv, "\nint ");
sp=shead; v=FALSE; nl=0;
while (sp!=stail)
   {
   if (sp->var) {
      v=TRUE;
      tmp[0]=0;
      a=strlen(sp->name)+2; s=strlen(strv); /* Bisogna contare 2 per ", " */
      if (s+a-nl>CHARS_PER_LINE) {
         strcpy(tmp, "\n    "); /* A capo */
         nl=s;
         }
      strcat(tmp, sp->name); strcat(tmp, ", ");
      strv=(char *)myrealloc(strv, s+strlen(tmp)+1);
      strcat(strv, tmp);
      }
   sp=sp->next;
   }
strv[strlen(strv)-2]=';';
strv[strlen(strv)-1]=0;
if (v) {
   str=(char *)myrealloc(str, strlen(str)+strlen(strv)+1);
   strcat(str, strv);
   free(strv);
   }

return str;
}



char *make_newinit(void)
{
/* Builds the initialization of new[] with state values */
/* Expand compressed negative values */
char *str;
char tmp[256], tmp2[128];
int mask;
signal *sp;
str=(char *)mymalloc(1); str[0]=0;
if (cq==TRUE) return str; /* Combinatorial: no initialization */
sp=shead;
while (sp!=stail)
   {
   if (sp->state)
      {
      mask=((1<<sp->size)-1);
      if (!sp->var) { /* Signal */
         sprintf(tmp, "new[%s] = (in_data[0]>>_i_) & %0#4X; _i_+=%d;\n",
                      sp->name, mask, sp->size);
         if (sp->from < 0) { /* If can be negative, expand it */
            sprintf(tmp2, "if (new[%s] > %0#4X) new[%s] -= %0#4X;\n",
                    sp->name, sp->to, sp->name, 1<<sp->size);
            strcat(tmp, tmp2);
            }
         }
      else { /* Variabile */
         sprintf(tmp, "%s = (in_data[0]>>_i_) & %0#4X; _i_+=%d;\n",
                      sp->name, mask, sp->size);
         if (sp->from < 0) { /* Always can be negative, but check it anyway */
            sprintf(tmp2, "if (%s > %0#4X) %s -= %0#4X;\n",
                    sp->name, sp->to, sp->name, 1<<sp->size);
            strcat(tmp, tmp2);
            }
         }

      str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
      strcat(str, tmp);
      }
   sp=sp->next;
   }
return str;
}



char *make_newinput(void)
{
/* Builds the initialization of new[] with input values */
int move=0;
char *str;
char tmp[256];
signal *sp;
str=(char *)mymalloc(1); str[0]=0;
if (cq==TRUE) move=1;
else if (*ignores) move=-1;
sp=shead;
while (sp!=stail)
   {
   if (sp->dir==_IN)
      {
      sprintf(tmp, "new[%s] = in_data[%d];\n", sp->name, sp->pos-move);
      str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
      strcat(str, tmp);
      }
   sp=sp->next;
   }
return str;
}



char *make_outdataend(void)
{
/* Crea la sezione che assegna i valori d'uscita per out_data[] */
int move=0;
char *str;
char tmp[256];
BOOL expanded;
signal *sp;
str=(char *)mymalloc(1); str[0]=0;

/* A little explanation:
   Suppose you have a 4 bit integer; it can range from -8 to +7.
   Integers in C are usually 32 bits.
   Negative values are represented in complement.
   Problem 1: To return a value as output, it should never be out of range.
   Problem 2: To enter a value in the state, you have to use a small number
              of bits without losing sign information.
   Solution:
   Cut values at the less significant part;
   Put them in the state;
   If they are out of range, subtract 2^bits;
   Put them in output.
   The effect is to make values "cycle": +10 becomes -6, 8 becomes -8, 9 becomes -7,
   -9 becomes +7 ...
   Example:
   +3  (%00...00011) becomes +3  (%00...0011);
               ----                     ----
   +10 (%00...01010) becomes +10 (%00...1010);
               ----                     ----
   -7  (%11...11001) becomes +9  (%00...1001);
               ----                     ----
   -9  (%11...10111) becomes +7  (%00...0111);
               ----                     ----
   The results are complemented values using 4 bits.
   So +10 and +9 are actually negative numbers (4th bit is '1') and their true
   value is -6 and -7.
   After compiling the state, true values can be assigned to outputs simply by
   subtracting 16 to values greater than 7 (call this "expanding").

   Phase 1: cut everything
   Phase 2: assign state
   Phase 3: expand negatives
   Phase 4: assign outputs
 */


/* Phase 1: cut everything */
sp=shead;
while (sp!=stail)
   {
   if ((!cq && sp->state) || sp->dir==_OUT) { /* States or outs */
      if (!sp->var) { /* Signal */
         sprintf(tmp, "new[%s] &= %0#4X;\n",
                 sp->name, (1<<sp->size)-1);
         }
      else { /* Variable */
         sprintf(tmp, "%s &= %0#4X;\n",
                 sp->name, (1<<sp->size)-1);
         }
      str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
      strcat(str, tmp);
      }
   sp=sp->next;
   }

/* Phase 2: build state */
if (!cq) {
   str=(char *)myrealloc(str, strlen(str)+strlen("\nout_data[0]=0; _i_=0;\n")+1);
   strcat(str, "\nout_data[0]=0; _i_=0;\n");
   sp=shead;
   while (sp!=stail)
      {
      if (sp->state)
         {
         if (!sp->var) /* Signal */
            sprintf(tmp, "out_data[0] |= new[%s] << _i_; _i_+=%d;\n",
                         sp->name, sp->size);
         else /* Variable */
            sprintf(tmp, "out_data[0] |= %s << _i_; _i_+=%d;\n",
                         sp->name, sp->size);
         str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
         strcat(str, tmp);
         outdata0size+=sp->size;
         }
      sp=sp->next;
      }
   }

str=(char *)myrealloc(str, strlen(str)+2+1);
strcat(str, "\n"); /* Newline */

/* Phase 3: expand relatives */
expanded=FALSE;
sp=shead;
while (sp!=stail)
   {
   if (!sp->var) { /* Signal */
      if (sp->from < 0 && sp->dir==_OUT) { /* Relative: expand */
         expanded=TRUE;
         sprintf(tmp, "if (new[%s] > %0#4X) new[%s]-=%0#4X;\n",
                 sp->name, (1<<sp->size-1)-1, sp->name, 1<<sp->size);
         str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
         strcat(str, tmp);
         }
         /* Non relatives: do nothing */
      }
   else { /* Variable */
      if (sp->from < 0 && sp->dir==_OUT) { /* Relative: expand */
         expanded=TRUE;
         sprintf(tmp, "if (%s > %0#4X) %s-=%0#4X;\n",
                 sp->name, (1<<sp->size-1)-1, sp->name, 1<<sp->size);
         str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
         strcat(str, tmp);
         }
      /* Non relatives: do nothing */
      }
   sp=sp->next;
   }

if (expanded) {
   str=(char *)myrealloc(str, strlen(str)+2+1);
   strcat(str, "\n"); /* Newline */
   }

/* Phase 4: assign out values */
if (cq==TRUE) move=1;
sp=shead;
while (sp!=stail)
   {
   if (sp->dir==_OUT)
      {
      sprintf(tmp, "out_data[%d] = new[%s];\n",
              sp->pos-move, sp->name);
      str=(char *)myrealloc(str, strlen(str)+strlen(tmp)+1);
      strcat(str, tmp);
      }
   sp=sp->next;
   }

return str;
}



void addtmpsig(char *name)
{
/* Viene aggiunto un segnale '*name' nella lista dei segnali ma i suoi
   attributi sono temporaneamente inizializzati a zero; un puntatore
   ad esso e' aggiunto in coda a 'tmpslist[]' */
if (tmpslist_alloc==tmpslist_size)
   {
   tmpslist_alloc+=10;
   tmpslist=(signal **)myrealloc(tmpslist, tmpslist_alloc*sizeof(signal *));
   }
tmpslist[tmpslist_size++]=addsig(name, 0);
}



void copytmpslist(int dir, int tsize, BOOL state, fromto *ft)
{
/* I segnali inseriti con 'addtmpsig()' vengono completati */
/* 'state' e' TRUE se il segnale deve far parte dello stato */
/* Tutti i segnali nella 'tmpslist[]' hanno dimensione 'tsize' */
int i;
for (i=0; i<tmpslist_size; i++)
    {
    tmpslist[i]->dir = dir;
    tmpslist[i]->size = tsize;
    tmpslist[i]->state = state;
    tmpslist[i]->from=ft->from;
    tmpslist[i]->to=ft->to;
    /* Signal excluded from state ? */
    if (state==TRUE && excludevar(tmpslist[i]->name)) {
       tmpslist[i]->state = FALSE;
       warning("Signal %s excluded from state", tmpslist[i]->name);
       }
    tmpslist[i]->var = FALSE;
    if (dir==_IN) tmpslist[i]->pos = ++tot_in;
    else if (dir==_OUT) tmpslist[i]->pos = ++tot_out;
    }
tmpslist_size=0;
}



signal *addsig(char *name, BOOL var)/* , int dir, int size, BOOL state) */
{
/* Aggiunge un segnale o una variabile alla lista */
signal *sp=stail;
/* Viene aggiunto il prefisso dell'eventuale blocco in cui si trova */
stail->name = (char *)mymalloc(strlen(name)+strlen(sigprefix)+1);
stail->next = (signal *)mymalloc(sizeof(signal));
strcpy(stail->name, sigprefix); /* Tiene conto del blocco attuale */
strcat(stail->name, name);
/* Nel caso di segnali, i campi 'dir', 'size' e 'state' vengono sistemati
   al valore corretto da copytmpslist() */
stail->dir = _NONE;
stail->size = integersize;
stail->from = -(1<<integersize-1);
stail->to = (1<<integersize-1)-1;
stail->pos = 0;
/* Viene messo nello stato? */
if (!var) stail->state=FALSE;
else stail->state=TRUE;
stail->var=var; /* E' una variabile? */
stail = stail->next;
return sp;
}



void addchgsig(char *name, int rleft, int rright)
{
/* Aggiunge un segnale alla lista dei segnali di cui bisogna controllare *
 * un avvenuto cambiamento.                                              */
/* Se non c'e' range, rleft e rright sono a -1;
   se e' un bit, rleft e rright sono uguali;
   se e' un vettore, rleft e rright sono diversi. */
int i;
if (chglist_size==MAXCHGSIG)
   {
   warning("too many signals, increase MAXCHGSIG");
   return;
   }
for (i=0; i<chglist_size; i++)
    if (strcmp(name, chglist[i]->name)==0 &&
        rleft==chglist[i]->rleft &&
        rright==chglist[i]->rright)
        return;
chglist[chglist_size]=(chgsignal *)mymalloc(sizeof(chgsignal));
chglist[chglist_size]->name=(char *)mymalloc(strlen(name)+1);
strcpy(chglist[chglist_size]->name, name);
chglist[chglist_size]->rleft=rleft;
chglist[chglist_size++]->rright=rright;
}



char *make_chglist(void)
{
/* Crea i necessari confronti su chg[] */
int a, s, nl;
int i;
char *str;
char tmp[256];
char elm[256];
str=(char *)mymalloc(1);
str[0]=0;
if (chglist_size==0) return str;
nl=-strlen(indent)-4; /* 4="if (" */
for (i=0; i<chglist_size; i++)
   {
/*    if (chglist[i]->rright > -1) */
   if (chglist[i]->rright != chglist[i]->rleft) /* signal(3 downto 1) */
      sprintf(elm, "vpart(chg[%s], %d, %d) || ",
              chglist[i]->name, chglist[i]->rleft, chglist[i]->rright);
   else if (chglist[i]->rleft > -1) /* signal(3) */
      sprintf(elm, "vbit(chg[%s], %d) || ",
              chglist[i]->name, chglist[i]->rleft);
   else /* signal */
      sprintf(elm, "chg[%s] || ",
              chglist[i]->name);
   myfree(&chglist[i]->name);
   free(chglist[i]);
   tmp[0]=0;
   a=strlen(elm); s=strlen(str);
   if (s+a-nl>CHARS_PER_LINE) {
      sprintf(tmp, "\n%s    ", indent); /* A capo */
      nl=s-strlen(indent)-4;
      }
   strcat(tmp, elm);
   str=(char *)myrealloc(str, s+strlen(tmp)+1);
   strcat(str, tmp);
   }
chglist_size=0;
str[strlen(str)-4]=0; /* Toglie " || " */
return str;
}



signal *findsig(char *name)
{
/* Cerca un segnale nella lista dei segnali */
/* Deve tener conto del prefisso del blocco
   se gia' non c'e' un punto nel nome del segnale */
signal *sp;
char *stop, *fullname, *cp, oldchar;
if (*sigprefix=='_') warning("Internal error - Invalid sigprefix");

if (strchr(name, '.')==0) {
   /* 'name' e' un nome semplice: non indica un blocco */
   fullname=mymalloc(strlen(name)+strlen(sigprefix)+1);

   /* stop punta al carattere successivo a '_' oppure a 0 */
   stop=strrchr(sigprefix, '_');
   if (stop==NULL) stop=sigprefix-1;
   stop++;

   /* Il nome viene cercato prima nel blocco attuale,
    * poi in quelli via via precedenti fino a quello principale */
   do {
      oldchar=*stop; *stop=0; /* Taglio sigprefix */
      /* Nome completo: */
      sprintf(fullname, "%s%s", sigprefix, name);
      sp=shead;
      while (sp!=stail)
         {
         if (strcmp(sp->name, fullname)==0) {
            *stop=oldchar; myfree(&fullname); return sp; /* Trovato */
            }
         sp=sp->next;
         }
      /* Non trovato: si ripete eliminando un livello da sigprefix */
      *stop=oldchar; /* Incollo sigprefix */
      if (stop!=sigprefix) { /* Non siamo alla radice */
         if (*(stop-1)!='_') warning("Internal error - Missing '_'");
         *(--stop)=0; /* Ritaglio per nascondere l'ultimo '_' */
         cp=stop;
         stop=strrchr(sigprefix, '_'); /* Scendo di un livello */
         if (stop==NULL) stop=sigprefix-1;
         stop++; /* Carattere successivo a '_' oppure 0 */
         *cp='_'; /* Incollo '_' veccio */
         }
      else stop=NULL; /* Termina */
      } while (stop!=NULL);
   myfree(&fullname);
   /* Non trovato: non e' un segnale ne' una variabile */
   }

else {
   /* E' gia' relativo ad un blocco: rimpiazzo '.' con '_' */
   char *newname, i=0;
   newname=mymalloc(strlen(name)+1);
   do {
      if (*name=='.') newname[i++]='_';
      else newname[i++]=*name;
      } while (*(name++)!=0);
   sp=shead;
   while (sp!=stail)
      {
      if (strcmp(sp->name, newname)==0)
         { myfree(&newname); return sp; }
      sp=sp->next;
      }
   myfree(&newname);
   }

/* Signal or variable not declared */
return NULL;
}



void join(char **out, char *fmt, ...)
{
/* Assegna a '*out', dopo aver allocato lo spazio, la stringa risultante   *
 * dall'inserimento in 'fmt' dei parametri passati; funziona per parametri *
 * stringa, carattere o intero.                                            */
char tmp[32];
char *fmt2;
char *ins;
int ind;
char *p, *f;
int usedlen=0, fmtlen;
va_list ap;
va_start(ap, fmt);

fmtlen=strlen(fmt);

*out = (char *) mymalloc(fmtlen+1);
*out[0]=0; /* Serve se fmt=="" */
/* Non posso usare fmt direttamente: 'Segmentation Fault' ! */
fmt2 = (char *) mymalloc(fmtlen+1);
strcpy(fmt2, fmt);

for (p=fmt2, f=fmt2; *p; p++)
    {
    if (*p != '%')
       continue;
    /* Ho trovato % */
    if (*(p+1) == '%') {
       p++; /* Salto il prossimo carattere in modo da
               ignorare i %%s, che diventano %s */
       continue;
       }
    /* Ho trovato %s ma non %%s */

    if (f != p)
       {
       *p=0;
       usedlen+=SPRSIZE(sprintf(*out+usedlen, f));
       *p='%';

       }
    f=p+2; p++;

    if (*p=='s') {
       ins=va_arg(ap, char *);
       if (ins!=NULL && ins[0]!=0) {
          *out = (char *) myrealloc(*out, usedlen+strlen(ins)+fmtlen+1);
          usedlen+=SPRSIZE(sprintf(*out+usedlen, "%s", ins));
          }
       }
    else if (*p=='c') {
       ind=va_arg(ap, int);
       *out = (char *) myrealloc(*out, usedlen+1+fmtlen+1);
       usedlen+=SPRSIZE(sprintf(*out+usedlen, "%c", (unsigned char) ind));
       }
    else if (*p=='d') {
       ind=va_arg(ap, int);
       sprintf(tmp, "%d", ind);
       *out = (char *) myrealloc(*out, usedlen+strlen(tmp)+fmtlen+1);
       usedlen+=SPRSIZE(sprintf(*out+usedlen, "%d", ind));
       }
    }

if (f != p)
   sprintf(*out+usedlen, f);
va_end(ap);
}



void myfree(char **p)
{
if (*p==NULL) {
   warning("Internal Error - freeing a NULL pointer!");
   }
else {
   free(*p);
   *p=NULL;
   }
}



void myfreen(int n, /* char **pp */ ...)
{
char **p;
va_list ap;
va_start(ap, n); /* ap punta a pp */
while (n--) {
   p=va_arg(ap, char **);

   if (*p==NULL) {
      warning("Internal Error - freeing a NULL pointer!");
      }
   else {
      free(*p);
      *p=NULL;
      }
   }
va_end(ap);
}



void * mymalloc(size_t size)
{
void * a;
if (size==0) return NULL;
a=(void *)malloc(size);
if (a==NULL)
    warning("Out of memory allocating %d bytes", size);
return a;
}



void * myrealloc(void * p, size_t size)
{
void * a;
if (p!=NULL) a=(void *)realloc(p, size);
else return mymalloc(size);
if (a==NULL && size>0)
   warning("Out of memory reallocating %d bytes", size);
return a;
}



int bits(int n)
{
/* Ritorna il numero di bit necessari per rappresentare n+1 valori. */
int i=0;
while (n) {
 n=n>>1; i++;
 }
return i;
}



void build_cont(char *fname)
{
char *filename;
signal *sp;
sp=shead;
filename=mymalloc(strlen(fname)+strlen("ont")+1);
sprintf(filename, "%sont", fname);
if (!freopen(filename, "w", stdout)) {
   fprintf(stderr, "Warning: Can't open output file '%s'\n", filename);
   return;
   }
puts("parameters");
if (*ignores) tot_in++;
printf("input\t%d\n", tot_in+!cq);
if (!cq) printf("\tinteger\t[0,%d]\n", (1<<outdata0size)-1);
if (*ignores) { tot_in--; printf("\tinteger\t[0,1]\n"); }
while (sp!=stail)
   {
   if (sp->dir == _IN)
      {
      printf("\tinteger\t[%d,%d]\n", sp->from, sp->to);
      }
   sp=sp->next;
   }
sp=shead;
printf("output\t%d\n", tot_out+!cq);
if (!cq) printf("\tinteger\t[0,%d]\n", (1<<outdata0size)-1);
while (sp!=stail)
   {
   if (sp->dir == _OUT)
      {
       printf("\tinteger\t[%d,%d]\n", sp->from, sp->to);
      }
   sp=sp->next;
   }
}



void warning(char *fmt, ...)
{
char p[256];
va_list ap;
va_start(ap, fmt);
fprintf(stderr, "Warning at line %d: ", lineno);
vsprintf(p, fmt, ap);
fprintf(stderr, p);
fputc('\n', stderr);
va_end(ap);
}



void yyerror(char *s)
{
fprintf(stderr, "*** %s at line %d ***\n", s, lineno);
}



int yywrap()
{
/* I'm guessing its use ... */
return 1;
}

/* End of procs.c */
