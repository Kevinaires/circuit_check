#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
 //Update to print the trace
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
/* Original file: FlipFlop_D.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

/* library ieee;
 * use ieee. std_logic_1164.all;
 * use ieee. std_logic_arith.all;
 * use ieee. std_logic_unsigned.all; */
void flipflop_d(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {D, CLK, RST, Q, _MAX_};
int lst[_MAX_];
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[D] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[CLK] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[RST] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[Q] = (in_data[0]>>_i_) & 0X01; _i_+=1;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       lst[_i_]=new[_i_];
    }
new[D] = in_data[1];
new[CLK] = in_data[2];
new[RST] = in_data[3];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=lst[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

   /* p0: */
   if (chg[RST] || chg[CLK]) {
            if ((old[RST]==1)) {
         new[Q]=0;
         }
      else if ((old[CLK]==1 && old[CLK]!=lst[CLK])) {
         if (chg[D]) {
            new[Q]=old[D];
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

new[D] &= 0X01;
new[CLK] &= 0X01;
new[RST] &= 0X01;
new[Q] &= 0X01;

out_data[0]=0; _i_=0;
out_data[0] |= new[D] << _i_; _i_+=1;
out_data[0] |= new[CLK] << _i_; _i_+=1;
out_data[0] |= new[RST] << _i_; _i_+=1;
out_data[0] |= new[Q] << _i_; _i_+=1;

out_data[1] = new[Q];
}

