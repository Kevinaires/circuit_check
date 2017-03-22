/* procs.h */
/* by Cristian Ghezzi - (c) 1995 */

#ifndef __procs_h
#define __procs_h

char * StringToLower(char * String);
char *strreplace(char *str, char *from, char *to);
BOOL excludevar(char *var);
void addwaitcase(char *str, int n);
char *make_waitcase(char *s, int n);
int vval(char *str);
char *make_waitlabel(void);
char *make_proclabel(void);
char *make_enum(void);
char *make_newinit(void);
char *make_newinput(void);
char *make_outdataend(void);
void addtmpsig(char *name);
void copytmpslist(int dir, int tsize, BOOL state, fromto *ft);
signal *addsig(char *name, BOOL state);
void addchgsig(char *name, int upbit, int lowbit);
char *make_chglist(void);
signal *findsig(char *name);
void join(char **out, char *fmt, ...);
void myfree(char **p);
void myfreen(int n, ...);
void * mymalloc(size_t size);
void * myrealloc(void * p, size_t size);
int bits(int n);
void build_cont(char *filename);
void warning(char *fmt, ...);
void yyerror(char *s);

#endif

/* End of procs.h */
