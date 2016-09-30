#include <stdio.h>
unsigned int addition(unsigned int a, unsigned int b);
int main()
{

  printf("%u\n",addition(107,26));

  return 0;
}

unsigned int addition(unsigned int a, unsigned int b)
{
  int t;
  while(a&b)
    {
      t=(a&b)<<1;
      a=a^b;
      b=t;
    }
  return (a^b);

}
