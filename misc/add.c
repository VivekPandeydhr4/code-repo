#include <stdio.h>
#include <stdlib.h>

int sum(int n1, int n2)
{
  int a, b, c, i, rslt;
  
  i=0; rslt=0; c=0;

  while(n1 || n2)
    {
      a = n1&1;
      b = n2&1;

      if(a && b)
	{
	  if(c) {b=1;c=1;}
	  else {b=0;c=1;}
	}
      else if((a && !b) || (!a && b))
	{
	  if(c) {b=0;c=1;}
	  else {b=1; c=0;}
	}
      else
	{
	  if(c) {b=1; c=0;}
	  else {b=0; c=0;}
	}
      rslt = rslt | (b<<i);
      i++;
      n1 = n1>>1;
      n2 = n2>>1;
    }
  return rslt;
}

int main()
{

  int n1=5, n2=4;
  
  printf("Sum = %d\n", sum(n1, n2));
  return 0;
}
