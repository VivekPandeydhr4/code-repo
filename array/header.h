#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

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
