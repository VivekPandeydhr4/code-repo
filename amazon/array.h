#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define ARR_SIZE(a) sizeof(a)/sizeof(a[0])

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
