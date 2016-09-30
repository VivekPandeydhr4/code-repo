#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print(char *str)
{
  char *tmp;
  tmp = str;
  while (*tmp != '\0')
    {
      printf("%c", *tmp);
      tmp++;
    }
  //  printf("\n");

}

void swap(char *a, char *b)
{
  char t ;
  t = *a;
  *a = *b;
  *b = t;
}
