#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_substr(char *str1, char* str2)
{
  int i, j;
  
  for (i=0, j=0; i<strlen(str1) && j<strlen(str2); i++)
    {
      if (*(str1+i) == *(str2+j))
	j++;     
    }
  
  if (j==strlen(str2))
    return 1;
  return 0;
}

int main ()
{
  char str1[] = "asgdhvhdgcbviudjwydveq";
  char str2[] = "vivek";

  printf("String 1 = %s\n", str1);
  printf("String 2 = %s\n", str2);

  printf("is substring = %s\n", (is_substr(str1, str2)) ? "Yes" : "No");

  return 0;
}
