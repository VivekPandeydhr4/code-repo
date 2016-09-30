#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char first_non_repeat_char(char *str)
{
  int i, j;
  int len = strlen(str);

  for (i=0; i<len; i++)
    {
      int flag = 0;
      for (j=0; j<len; j++)
	{
	  if((i != j) && (*(str+i) == *(str+j)))
	    {
	      flag = 1;
	      continue;
	    }
	}
      if(!flag)
	return *(str+i);
    }
}

char first_non_repeat_char_2(char *str)
{
  int i;
  int tbl[256];
  int len = strlen(str);
  for (i=0; i<256; i++)
    {
      tbl[i] = 0;
    }
  
  i =0;
  
  while(*(str+i) != '\0')
    {
      tbl[*(str+(i++))]++;
    }
  
  for (i=0; i<len; i++)
    if (tbl[*(str+i)] == 1)
      return *(str+i);
}

int main ()
{
  char str[] = "vvvvl";//kvekkemarpandey";

  printf("String = %s\n", str);

  printf("First Character = %c\n", first_non_repeat_char_2(str));

  return 0;
}
