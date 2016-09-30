#include <stdio.h>
#include <string.h>


void generic_swap(void *first, void *second, int bytes)
{
  char temp[bytes];
  memcpy(temp,first,bytes);
  memcpy(first,second,bytes);
  memcpy(second,temp,bytes);
}
int main()
{

  char a[100]="vikas kumar",b[100]="pandey";
  printf("%s,%s: ",a,b);
  generic_swap(a,b,12);
  printf("%s,%s\n",a,b);
  return 0;
}
