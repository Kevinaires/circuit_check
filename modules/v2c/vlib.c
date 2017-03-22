/* vlib.c */
/* by Cristian Ghezzi - (c) 1995 */


#ifndef BOOL
 typedef int BOOL;
 #define TRUE 1
 #define FALSE 0
#endif



int vins(int *v1, int from, int to, int v2)
/* Inserisce nel vettore *v1, alle posizioni da from a to, il vettore v2 */
/* Ritorna *v1 */
{
int i;
int mask;

if (from > to ) /* Swap */
   {
   i=from; from=to; to=i;
   }

mask=(2<<to)-(1<<from); /* Fornisce i bit da from a to a 1 */

*v1=( *v1 & (~mask) ) | ( (v2<<from) & mask );

return *v1;

}



int vcat(int v1, int v2, int pos)
{
/* Ritorna la concatenazione dei vettori v1 e v2, con pos pari
 * alla dimensione di v2 */
return (v1<<pos) & v2;
}



int vbit(int vec, int pos)
/* Ritorna il valore 1 o 0 del bit di vec in posizione pos */
{
return (vec & 1<<pos) >> pos;
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



BOOL veq(int vec, int from, int to, char *str)
/* Confronta i bit di vec da from a to con la stringa str;
   from puo' essere maggiore o minore di to, ma la stringa
   e' sempre presa da sinistra a destra (parte da str[0]). */
/* Ovvero 'veq(v, 0, 4, "10100")' inizia confrontando
   v(0) con '1', mentre 'veq(v, 4, 0, "10100")' confronta
   v(4) con '1' e v(0) con '0'. */
{
int i;
int step, mask;

if (from > to ) /* Swap */
   {
   i=from; from=to; to=i;
   }


for (i=from; i<=to; i++)
    {
    mask = 1<<i;
    if ( (vec & mask) != (*(str++)-'0')*mask ) return FALSE;
    }
return TRUE;
}



int vcmp(int vec1, int vec2, int from, int to)
/* Confronta i bit di vec1 da from a to con quelli di vec2,
   alla stessa posizione; from puo' essere maggiore o minore di to.
   Ritorna 0 se sono uguali. */
{
int i;
int mask;

if (from > to ) /* Swap */
   {
   i=from; from=to; to=i;
   }

mask=(2<<to)-(1<<from); /* Fornisce i bit da from a to a 1 */

return (vec1 & mask) - (vec2 & mask);

}



int vpart(int vec, int from, int to)
/* Ritorna la parte di vec dal bit from al bit to compresi,
   shiftandola nella parte piu' bassa. */
{
int i;
int mask;

if (from > to ) /* Swap */
   {
   i=from; from=to; to=i;
   }

mask=(2<<to)-(1<<from); /* Mette i bit da from a to a 1 */

return (vec & mask) >> from;
}



/* End of vlib.c */
