#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
 //Update to print the trace
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
/* Original file: comb1.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

void comb1(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {in1, in2, sel, out1, _MAX_};
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[in1] = (in_data[0]>>_i_) & 0XFFFF; _i_+=16;
if (new[in1] > 0X7FFF) new[in1] -= 0X10000;
new[in2] = (in_data[0]>>_i_) & 0XFFFF; _i_+=16;
if (new[in2] > 0X7FFF) new[in2] -= 0X10000;
new[sel] = (in_data[0]>>_i_) & 0X03; _i_+=2;
new[out1] = (in_data[0]>>_i_) & 0XFFFF; _i_+=16;
if (new[out1] > 0X7FFF) new[out1] -= 0X10000;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];
    }
new[in1] = in_data[1];
new[in2] = in_data[2];
new[sel] = in_data[3];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

   /* p0: */
   if (chg[in1] || chg[in2] || chg[sel]) {
            switch (old[sel]) {
         case 0: 
            if (chg[in1] || chg[in2]) {
               new[out1]=old[in1]+old[in2];
               }
            break;
         case 1: 
            if (chg[in1] || chg[in2]) {
               new[out1]=old[in1]-old[in2];
               }
            break;
         case 2: 
            if (chg[in1] || chg[in2]) {
               new[out1]=old[in1]*old[in2];
               }
            break;
         case 3: 
            new[out1]=0;
            break;
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

new[in1] &= 0XFFFF;
new[in2] &= 0XFFFF;
new[sel] &= 0X03;
new[out1] &= 0XFFFF;

out_data[0]=0; _i_=0;
out_data[0] |= new[in1] << _i_; _i_+=16;
out_data[0] |= new[in2] << _i_; _i_+=16;
out_data[0] |= new[sel] << _i_; _i_+=2;
out_data[0] |= new[out1] << _i_; _i_+=16;

if (new[out1] > 0X7FFF) new[out1]-=0X10000;

out_data[1] = new[out1];
}

