#include "header.h"

char *long_plndrm_str(char *str, int *size)
{
  int len = strlen(str);

  int i, j, k, l;

  char *tmp = NULL;

  for (i=0; i<len; i++)
    {
      for (j=len; j>i; j--)
	{
	  if (*(str+i)==*(str+j))
	    {
	      k = i+1;
	      l = j-1;
	      
	      while((k < l) && *(str+k) == *(str+l))
		{
		  k++;
		  l--;
		}
	      if ((k>=l) && ((j-i+1) > *size))
		{
		  tmp = str+i;
		  *size = j-i+1;
		}
	    }
	}
    }
  if (len == 1)
    {
      tmp = str;
      *size = len;
    }
  return tmp;
}

int main ()
{
  char str[] = "vvekacdbagbckakumarvir";
  char *pln;
  int size=0, i;
  
  printf("Given String = %s\n", str);

  pln = long_plndrm_str(str, &size);

  printf("Palindrom is of size %d = ", size);

  for(i=0; i<size; i++)
    printf("%c", *(pln+i));

  printf("\n");
  return 0;
}
