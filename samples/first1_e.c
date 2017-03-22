/* Original file: first1.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */
#include "vlib.h"

/* first1.vhd
 * First Example File
 *
 * The vhdl source must contain both the entity and the architecture
 * declaration. You can put comments almost in any place and they will be
 * copied in the translation.
 * The name of the entity is used for the name of the output files.
 * The entity starts here: */
/* Now comes the architecture. This examples really does nothing useful; it
 * is just a demostration of the program behaviour and not of my VHDL skills... */
void first1_e(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {in1, in2, ctl, bogus, out1, aaa, bbb, c8, _MAX_};
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[in1] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[in2] = (in_data[0]>>_i_) & 0X0F; _i_+=4;
new[ctl] = (in_data[0]>>_i_) & 0XFFFF; _i_+=16;
if (new[ctl] > 0X7FFF) new[ctl] -= 0X10000;
new[bogus] = (in_data[0]>>_i_) & 0XFFFF; _i_+=16;
if (new[bogus] > 0X7FFF) new[bogus] -= 0X10000;
new[out1] = (in_data[0]>>_i_) & 0X0F; _i_+=4;
new[aaa] = (in_data[0]>>_i_) & 0X0F; _i_+=4;
new[bbb] = (in_data[0]>>_i_) & 0X0F; _i_+=4;
new[c8] = (in_data[0]>>_i_) & 0X03; _i_+=2;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];
    }
new[in1] = in_data[1];
new[in2] = in_data[2];
new[ctl] = in_data[3];
new[bogus] = in_data[4];

/* There are just a few VHDL types that are recognized,
 * and only IN and OUT directions are accepted. */
new[c8]=0;
for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

   /* In the architecture body you can place your code.
    * Some concurrent statements: */
   if (chg[in2]) {
      new[aaa]=old[in2];
      }
   if (chg[in1]) {
      new[bbb]=vcat(vcat(old[in1], old[in1], 1), old[in1], 1);
      }
   /* A sequential process */
   /* myproc1: */
   if (chg[bbb] || chg[in1]) {
            if (old[in1]==1 && old[bbb]==5) {
         if (chg[aaa]) {
            new[out1]=old[aaa];
            }
         }
      else {
         if (chg[bbb]) {
            new[out1]=old[bbb];
            }
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

new[in1] &= 0X01;
new[in2] &= 0X0F;
new[ctl] &= 0XFFFF;
new[bogus] &= 0XFFFF;
new[out1] &= 0X0F;
new[aaa] &= 0X0F;
new[bbb] &= 0X0F;
new[c8] &= 0X03;

out_data[0]=0; _i_=0;
out_data[0] |= new[in1] << _i_; _i_+=1;
out_data[0] |= new[in2] << _i_; _i_+=4;
out_data[0] |= new[ctl] << _i_; _i_+=16;
out_data[0] |= new[bogus] << _i_; _i_+=16;
out_data[0] |= new[out1] << _i_; _i_+=4;
out_data[0] |= new[aaa] << _i_; _i_+=4;
out_data[0] |= new[bbb] << _i_; _i_+=4;
out_data[0] |= new[c8] << _i_; _i_+=2;

out_data[1] = new[out1];
}

