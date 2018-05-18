#include <assert.h>
#include <stdlib.h>

main()
{
 int i = __VERIFIER_nondet_int();
 int *a = malloc(12);
 int b[2] = {1,2};

 if(i > 5)
 {
  b[i] = 5;
  assert(0);
 }
 free(a);

}
