#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>

void print(int arr[], int size)
{
  int i;

  for(i=0; i<size; i++)
    printf("%d ", arr[i]);
  printf("\n");

}

void swap(int *a, int *b)
{
  int t ;
  t = *a;
  *a = *b;
  *b = t;
}

#endif
