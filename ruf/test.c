#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct stabc
{
  char a;
  char b;
  char c;
  int n;
}stab;

int main ()
{
  stab *ab = (stab*)malloc(sizeof(stab));

  ab->a='a';
  ab->b='b';
  ab->c='c';
  ab->n=5;

  printf("Element:- %c, %c, %c, %d\n", ab->a, ab->b, ab->c, ab->n);

  printf("Address:- %p, %p, %p, %p\n", &ab->a, &ab->b, &ab->c, &ab->n);

  printf("%d", *((char*)ab+4));


  printf("\n");
  return 0;
}
