#include <stdio.h>

int fun(int a)
{
  return (1+!(a-1));
}

int main()
{
  printf("fun(1)=%d\n",fun(1));
  printf("fun(2)=%d\n",fun(2));  
  return 0;
}
