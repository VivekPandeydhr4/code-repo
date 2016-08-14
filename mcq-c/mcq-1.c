#include <stdio.h>


int main()
{

  int p = 10;
  void *q = &p;

  printf("P = %f\n", *(float*)q);
  return 0;
}
