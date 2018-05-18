#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
 //Update to print the trace
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
/* Original file: seq1.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

void seq1(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {in1, in2, reset, out1, out2, _MAX_};
int p0_st;
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[in1] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[in2] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[reset] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[out1] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[out2] = (in_data[0]>>_i_) & 0X01; _i_+=1;
p0_st = (in_data[0]>>_i_) & 0XFFFF; _i_+=16;
if (p0_st > 0X7FFF) p0_st -= 0X10000;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];
    }
new[in1] = in_data[1];
new[in2] = in_data[2];
new[reset] = in_data[3];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

   /* p0: */
   if (chg[in1] || chg[in2] || chg[reset]) {
            if (old[reset]==0) {
         p0_st=0;
         new[out1]=0;
         new[out2]=0;
         }
      else if ((old[in1]==0 && old[in2]==0 && p0_st==0)) {
         new[out2]=1;
         }
      else if ((old[in1]==1 && old[in2]==1 && p0_st==1)) {
         new[out1]=1;
         }
      p0_st=~p0_st;
      }

   /* End of Translation */
   for (_i_=0; _i_<_MAX_; _i_++)
       {
       if (new[_i_]!=old[_i_]) _cont_=1;
       chg[_i_]=old[_i_] ^ new[_i_];
       old[_i_]=new[_i_];
       }
   } while (_cont_);

new[in1] &= 0X01;
new[in2] &= 0X01;
new[reset] &= 0X01;
new[out1] &= 0X01;
new[out2] &= 0X01;
p0_st &= 0XFFFF;

out_data[0]=0; _i_=0;
out_data[0] |= new[in1] << _i_; _i_+=1;
out_data[0] |= new[in2] << _i_; _i_+=1;
out_data[0] |= new[reset] << _i_; _i_+=1;
out_data[0] |= new[out1] << _i_; _i_+=1;
out_data[0] |= new[out2] << _i_; _i_+=1;
out_data[0] |= p0_st << _i_; _i_+=16;

out_data[1] = new[out1];
out_data[2] = new[out2];
}

