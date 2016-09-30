#include <stdio.h>
#define Reverse(x) *((char*)&x)<<24  | *((char*)&x+1)<<16 | *((char*)&x+2)<<8 |*((char*)&x+3)

int main()
{
  unsigned int x=31;
  printf("%x,%x\n",x,Reverse(x));
  return 0;
}
