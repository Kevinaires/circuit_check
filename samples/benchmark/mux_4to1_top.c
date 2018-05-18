#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
 //Update to print the trace
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
/* Original file: mux_4to1_top.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */
#include "vlib.h"

/* library IEEE;
 * use IEEE.STD_LOGIC_1164.ALL; */
void mux_4to1_top(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {SEL, X, A, _MAX_};
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[SEL] = (in_data[0]>>_i_) & 0X03; _i_+=2;
new[X] = (in_data[0]>>_i_) & 0X03; _i_+=2;
new[A] = (in_data[0]>>_i_) & 0X0F; _i_+=4;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];
    }
new[SEL] = in_data[1];
new[X] = in_data[2];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

  //@c2vhdl:ASSERT - severity ERROR;
    __MY_assert(!(SEL == __VERIFIER_nondet_int() && A == __VERIFIER_nondet_int()),"Both values of signals x and y are equal to 1");

   if (chg[SEL] || vbit(chg[A], 0) || vbit(chg[A], 1) || vbit(chg[A], 2) || 
       vbit(chg[A], 3)) {
      switch (old[SEL]) {
         case 0 : new[X]=vbit(old[A], 0); break;
         case 1 : new[X]=vbit(old[A], 1); break;
         case 2 : new[X]=vbit(old[A], 2); break;
         case 3 : new[X]=vbit(old[A], 3); break;
         default : new[X]=0;
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

new[SEL] &= 0X03;
new[X] &= 0X03;
new[A] &= 0X0F;

out_data[0]=0; _i_=0;
out_data[0] |= new[SEL] << _i_; _i_+=2;
out_data[0] |= new[X] << _i_; _i_+=2;
out_data[0] |= new[A] << _i_; _i_+=4;

out_data[1] = new[A];
}

