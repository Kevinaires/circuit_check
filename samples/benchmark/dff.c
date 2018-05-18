#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
 //Update to print the trace
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
/* Original file: dff.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

/* library ieee ;
 * use ieee.std_logic_1164.all; */
void dff(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {data_in, clock, data_out, _MAX_};
int lst[_MAX_];
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[data_in] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[clock] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[data_out] = (in_data[0]>>_i_) & 0X01; _i_+=1;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       lst[_i_]=new[_i_];
    }
new[data_in] = in_data[1];
new[clock] = in_data[2];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=lst[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

  //@c2vhdl:ASSERT - severity ERROR;
    __MY_assert(!(data_in == __VERIFIER_nondet_int() && clock == __VERIFIER_nondet_int()),"Both values of signals x and y are equal to 1");

   /* p0: */
   if (chg[data_in] || chg[clock]) {
            /* clock rising edge */
      if ((old[clock]==1 && old[clock]!=lst[clock])) {
         if (chg[data_in]) {
            new[data_out]=old[data_in];
            }
         }
      }

   /* End of Translation */
   for (_i_=0; _i_<_MAX_; _i_++)
       {
       if (new[_i_]!=old[_i_]) _cont_=1;
       lst[_i_]=old[_i_];
       chg[_i_]=lst[_i_] ^ new[_i_];
       old[_i_]=new[_i_];
       }
   } while (_cont_);

new[data_in] &= 0X01;
new[clock] &= 0X01;
new[data_out] &= 0X01;

out_data[0]=0; _i_=0;
out_data[0] |= new[data_in] << _i_; _i_+=1;
out_data[0] |= new[clock] << _i_; _i_+=1;
out_data[0] |= new[data_out] << _i_; _i_+=1;

out_data[1] = new[data_out];
}

