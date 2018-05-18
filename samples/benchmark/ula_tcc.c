#include<stdio.h>
#define log_error(M, ...) fprintf(stderr,  M , __FILE__, __LINE__, ##__VA_ARGS__)
 //Update to print the trace
#define __MY_assert(A, M, ...) if(!(A)) {log_error(M, ##__VA_ARGS__); assert(A); }
/* Original file: Ula_tcc.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

/* library ieee;
 * use ieee.std_logic_1164.all; */
void ula_tcc(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {A, B, Binvertido, Op1, Resultado, and_port, or_port, mux2x1, _MAX_};
//__ESBMC_assume(_MAX_ <= 8);
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[A] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[B] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[Binvertido] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[Op1] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[Resultado] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[and_port] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[or_port] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[mux2x1] = (in_data[0]>>_i_) & 0X01; _i_+=1;

//assert(0);


for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];

    }
new[A] = in_data[1];
new[B] = in_data[2];
new[Binvertido] = in_data[3];
new[Op1] = in_data[4];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    
    }

do {
   _cont_=0;
   /* Start of Translation */

   /* p0: */
   if (chg[A] || chg[B] || chg[Binvertido] || chg[Op1]) {
            /*PORTA AND */
      if (chg[A] || chg[mux2x1]) {
	 __ESBMC_assume(old[A]==1);
	 __ESBMC_assume(old[mux2x1]==1);
         new[and_port]=old[A] & old[mux2x1];
         }
      /*PORTA OR */
      if (chg[A] || chg[mux2x1]) {
         new[or_port]=old[A] | old[mux2x1];
         }
      /*INVERSOR */
      if ((old[Binvertido]==0)) {
         if (chg[B]) {
            new[mux2x1]=old[B];
            }
         }
      else {
         if (chg[B]) {
            new[mux2x1]=~old[B];
            }
         }
      /*mux4x1 */
      if ((old[Op1]==0)) {
         if (chg[and_port]) {
            new[Resultado]=old[and_port];
	    assert(0);
	    assert(new[Resultado] == 0);
            }
         }
      else if ((old[Op1]==1)) {
         if (chg[or_port]) {
            new[Resultado]=old[or_port];
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

new[A] &= 0X01;
new[B] &= 0X01;
new[Binvertido] &= 0X01;
new[Op1] &= 0X01;
new[Resultado] &= 0X01;
new[and_port] &= 0X01;
new[or_port] &= 0X01;
new[mux2x1] &= 0X01;

out_data[0]=0; _i_=0;
out_data[0] |= new[A] << _i_; _i_+=1;
out_data[0] |= new[B] << _i_; _i_+=1;
out_data[0] |= new[Binvertido] << _i_; _i_+=1;
out_data[0] |= new[Op1] << _i_; _i_+=1;
out_data[0] |= new[Resultado] << _i_; _i_+=1;
out_data[0] |= new[and_port] << _i_; _i_+=1;
out_data[0] |= new[or_port] << _i_; _i_+=1;
out_data[0] |= new[mux2x1] << _i_; _i_+=1;

out_data[1] = new[Resultado];

}

