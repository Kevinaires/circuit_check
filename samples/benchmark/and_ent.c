#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); } //Update to print the trace
/* Original file: AND_ent.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

/* library ieee;
 * use ieee.std_logic_1164.all; */
/*------------------------------------------------ */
void and_ent(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {x, y, F, _MAX_};
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[x] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[y] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[F] = (in_data[0]>>_i_) & 0X01; _i_+=1;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];
    }
new[x] = in_data[1];
new[y] = in_data[2];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

   /*@c2vhdl:ASSERT
    *assert not (x='0' and y='1')
    *report "Both values of signals x and y are equal to 1"
    *severity ERROR;
    *@c2vhdl:END */

//@c2vhdl:ASSERT - severity ERROR;
__MY_assert(!(x=='0' && y=='1'),"Both values of signals x and y are equal to 1");

   /* p0: */
   if (chg[x] || chg[y]) {
            /* compare to truth table */
      if (((old[x]==1) && (old[y]==1))) {
         new[F]=1;
         }
      else {
         new[F]=0;
         }
      }

   /* End of Translation */
   for (_i_=0; _i_<_MAX_; _i_++)
       {
       if (new[_i_]!=old[_i_]) _cont_=1;
       chg[_i_]=old[_i_] ^ new[_i_];
       old[_i_]=new[_i_];
       }
   } while (_cont_);

new[x] &= 0X01;
new[y] &= 0X01;
new[F] &= 0X01;

out_data[0]=0; _i_=0;
out_data[0] |= new[x] << _i_; _i_+=1;
out_data[0] |= new[y] << _i_; _i_+=1;
out_data[0] |= new[F] << _i_; _i_+=1;

out_data[1] = new[F];
}

