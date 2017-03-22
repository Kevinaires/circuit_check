/* v2cmain.c */
/* by Cristian Ghezzi - (c) 1995 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include "defs.h"
#include "procs.h"
#include "version.h"


extern char *ignores;
extern integersize;
extern char **exclude;
extern signal *shead, *stail;
extern signal **tmpslist;
extern int tmpslist_alloc;
extern char **waitcase;
extern int waitcase_alloc;
extern int yyparse(void);
extern int outdata0size;
extern BOOL cq;

char *outfile;    /* Output file */
char *sourcefile; /* Input file */


static int usage(void)
{
   fputs("Usage: v2c [-c] [-s<n>] [-k<name>] <filename> [-x <list>]\n"
         "  -c       Force combinatorial translation\n"
         "  -s<n>    Size of 'integer'; default = "_INTEGERSIZES" bits\n"
         "  -k<name> Ignore clock-signal <name>\n"
         "  -x       Exclude variables from state\n"
         "           <list> is a space-separated list of"
#ifdef UNIX
         " escaped"
#endif
         " regular expressions\n"
         "Eg: v2c counter.vhd -x sum "
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
int in, i, e;
BOOL ex=FALSE;
char *ch;

fprintf(stderr, "VHDL to C translator - (c) by C.Ghezzi - "
                VERSION " " DATE "\n");
if (argc<2) {
   return usage();
   }

for (i=1, in=0, e=0; i<argc; i++) {
    if (strcmp(argv[i], "-c")==0 && cq==FALSE) cq=TRUE;
/*     else if (in==0 && *argv[i]=='-') return usage(); */
    else if (strncmp(argv[i], "-s", 2)==0) {
      integersize=atoi(argv[i]+2);
      if (integersize==0) {
         fputs("Wrong '-s' syntax\n", stderr);
         return usage();
         }
      }
    else if (strncmp(argv[i], "-k", 2)==0) { /* Flag -k */
      int len=strlen(argv[i]);
      if (len<3) {
         fputs("Wrong '-k' syntax\n", stderr);
         return usage();
         }
      if (ignores!=NULL) {
         fputs("Duplicated '-k' flag: ignored\n", stderr);
         }
      else {
         len-=2;
         ignores=mymalloc(len+1);
         strcpy(ignores, argv[i]+2);
         ++e;
         exclude=myrealloc(exclude, e*sizeof(char *));
         exclude[e-1]=mymalloc(strlen(ignores)+1);
         strcpy(exclude[e-1], ignores);
         }
      }
    else if (in==0) in=i;
    else if (strcmp(argv[i], "-x")==0) ex=TRUE;
    else if (ex==TRUE) {
            ++e;
            exclude=myrealloc(exclude, e*sizeof(char *));
            exclude[e-1]=mymalloc(strlen(argv[i])+1);
            strcpy(exclude[e-1], argv[i]);
            }
    else return usage();
    }

if (ex && !exclude) return usage();

if (exclude) {
   exclude=myrealloc(exclude, (e+1)*sizeof(char *));
   exclude[e]=NULL; /* Chiude la lista */
   }

if (ignores==NULL) {
   ignores=mymalloc(1);
   ignores[0]=0;
   }

/* Temporary output file */
/* Can't use full pathname 'cause rename() could fail */
ch=tmpnam(NULL);
outfile=strrchr(ch, DIRSEP);
if (outfile==NULL) outfile=ch;
else outfile++;
sourcefile=(char *)mymalloc(strlen(argv[in])+1);
strcpy(sourcefile, argv[in]);

if (!freopen(sourcefile, "r", stdin)) {
   fprintf(stderr, "Error: Can't open input file '%s'\n", sourcefile);
   return(1);
   }

if (!freopen(outfile, "w", stdout)) {
   fprintf(stderr, "Error: Can't open output file '%s'\n", outfile);
   fclose(stdin);
   return(1);
   }

shead=(signal *)mymalloc(sizeof(signal));
stail=shead;
tmpslist=(signal **)mymalloc(tmpslist_alloc*sizeof(signal *));
waitcase=(char **)mymalloc(waitcase_alloc*sizeof(char *));
yyparse();
fclose(stdout);
fclose(stdin);
if (outdata0size>OUTDATA0SIZE && cq==FALSE) fprintf(stderr, "Warning: outdata[0] is %d bits long.\n", outdata0size);
if (outdata0size==0 && cq==FALSE) fprintf(stderr, "Warning: outdata[0] is %d bits long.\n", outdata0size);
return(0);
}



/* End of v2cmain.c */
