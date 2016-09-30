#include <stdio.h>

void add_1(int *x)
{
  ++(*x);
}
int main ()
{

  int x=7;
  
  printf("%d\n", x);

  add_1(&x);

  printf("%d\n", x);

  return 0;
}
