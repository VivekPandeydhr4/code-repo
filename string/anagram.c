:q#include "header.h"

#define SIZE 256

int is_anagram(char *str1, char *str2)
{
  int i, j, flag;

  if (strlen(str1) != strlen(str2))
    return 0;
  
  for (i=0; i<strlen(str1); i++)
    {
      flag = 0;
      for (j=0; j<strlen(str2); j++)
	{
	  if (*(str1+i) == *(str2+j))
	    flag = 1;
	}
      if (flag == 0) return 0;
    }
  return 1;
}

int is_anagram_1(char *str1, char *str2)
{
  int arr[SIZE];
  int i;
  char *tmp;

  for (i=0; i<SIZE; i++)
    arr[i] = 0;

  tmp = str1;
  while(*tmp != '\0')
    {
      arr[*(tmp++)]++;
    }

  tmp = str2;
  while(*tmp != '\0')
    {
      arr[*(tmp++)]--;
    }

  for (i=0; i<SIZE; i++)
    {
      if (arr[i] != 0)
	return 0;
    }
  return 1;
}
int main()
{
  char *str1 = "reactive";
  char *str2 = "creative";

  printf (" Anagram = %s\n", is_anagram_1(str1, str2) ? "Yes" : "No");
  printf ("\n");
  return 0;
}
