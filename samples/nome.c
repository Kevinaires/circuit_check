/* Original file: Vhdl1.vhd
 * Translated by v2c 1.12
 * Integer size: 16 bits */

void nome(int in_data[], int out_data[])
{
int _i_=0;
int _cont_;
enum segnale {A, B, _MAX_};
int old[_MAX_];
int new[_MAX_];
int chg[_MAX_];
new[A] = (in_data[0]>>_i_) & 0X01; _i_+=1;
new[B] = (in_data[0]>>_i_) & 0X01; _i_+=1;

for (_i_=0; _i_<_MAX_; _i_++)
    {
       old[_i_]=new[_i_];
    }
new[A] = in_data[1];

for (_i_=0; _i_<_MAX_; _i_++)
    {
    chg[_i_]=old[_i_] ^ new[_i_];
    old[_i_]=new[_i_];
    }

do {
   _cont_=0;
   /* Start of Translation */

   /* p0: */
   if (chg[A]) {
            if ((old[A]==1)) {
         new[B]=0;
         }
      else {
         new[B]=1;
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

out_data[0]=0; _i_=0;
out_data[0] |= new[A] << _i_; _i_+=1;
out_data[0] |= new[B] << _i_; _i_+=1;

out_data[1] = new[B];
}

