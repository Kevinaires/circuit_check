/* vlib.h */
/* by Cristian Ghezzi - (c) 1995 */

#ifndef TRUE
 typedef int BOOL;
 #define TRUE 1
 #define FALSE 0
#endif

int vins(int *v1, int from, int to, int v2);
/* Inserisce nel vettore *v1, alle posizioni da from a to, il vettore v2;
   ritorna *v1 */

int vcat(int v1, int v2, int pos);
/* Ritorna la concatenazione dei vettori v1 e v2, con pos pari
 * alla dimensione di v2 */

int vbit(int vec, int pos);
/* Ritorna il valore 1 o 0 del bit di vec in posizione pos */

int vval(char *str);
/* Ritorna il valore numerico della stringa binaria */

BOOL veq(int vec, int from, int to, char *str);
/* Confronta i bit di vec da from a to con la stringa str;
   from puo' essere maggiore o minore di to, ma la stringa
   e' sempre presa da sinistra a destra (parte da str[0]). */

int vcmp(int vec1, int vec2, int from, int to);
/* Confronta i bit di vec1 da from a to con quelli di vec2,
   alla stessa posizione; from puo' essere maggiore o minore di to.
   Ritorna 0 se sono uguali. */

int vpart(int vec, int from, int to);
/* Ritorna la parte di vec dal bit from al bit to compresi,
   shiftandola nella parte piu' bassa. */



/* End of vlib.h */
