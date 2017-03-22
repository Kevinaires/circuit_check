/* defs.h */
/* by Cristian Ghezzi - (c) 1995 */

#ifndef __defs_h
#define __defs_h

/* **************************** */
/* *   User Editable Values   * */
/* **************************** */


/* Name of the variable that holds the index
   to the current wait position in a process */
#define WAITINDEXNAME "_waitindex_"

/* Dimension (in bits) of outdata[0] */
#define OUTDATA0SIZE 32

/* Dimension of integers in the VHDL source */
#define _INTEGERSIZE 16
#define _INTEGERSIZES "16"

/* Characters per line in the translation */
#define CHARS_PER_LINE 80

/* Indentation spaces */
#define INDENTS "   "
#define INDENTL 3

/* Extension and directory separator character */
#ifdef SUN_OS
 #define UNIX
#endif
#ifdef UNIX
 #define EXTC '.'
 #define EXTS "."
 #define DIRSEP '/'
#endif
#ifdef MSDOS
 #define EXTC '.'
 #define EXTS "."
 #define DIRSEP '\\'
#endif
#ifdef RISC_OS
 #define EXTC '/'
 #define EXTS "/"
 #define DIRSEP '.'
#endif

/* *********************************** */
/* *   End of User Editable Values   * */
/* *********************************** */

/* #define FLEX_DEBUG */

#ifndef TRUE
#define TRUE 1
#define FALSE 0
typedef int BOOL;
#endif

enum dir {_IN, _OUT, _NONE};

typedef struct expdata
          {
          char * txt;
          int size; /* Numero di bit nel valore dell'espressione */
          } expdata;

typedef struct sigdata
          {
          char * name;
          int rleft; /* Valore sinistro del range (oppure -1) */
          int rright; /* Valore destro del range (oppure -1) */
          } sigdata;

typedef struct signal {
                      char *name; /* Nome */
                      int dir;    /* Direzione (categoria) */
                      int pos;    /* # d'ordine nella categoria */
                      int size;   /* Dimension */
                      int from;   /* Range */
                      int to;
                      unsigned int state: 1; /* TRUE se appartiene a stato */
                      unsigned int var: 1; /* TRUE se e' una variabile */
                      struct signal *next;
                      } signal;

typedef struct fromto { /* Range of values a signal can assume (for .cont) */
                      int from;
                      int to;
                      } fromto;

typedef struct chgsignal {
                      char *name; /* Nome */
                      int rleft; /* Estremo sinistro del range (oppure -1) */
                      int rright; /* Estremo destro del range (oppure -1) */
                      } chgsignal;
#endif

/* End of defs.h */
