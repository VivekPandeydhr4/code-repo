#include<stdio.h>
#include<stdlib.h>

void print_matrix(int arr[][4], int len, int breath)
{
  int i,j;

  for(i=0,j=0; i<breath; i++)
    for(i++,j=0; j<len; j++)
      {
	printf("%d ", arr[i][j]);
	printf("\n");

      }  
}

void swap(int *a, int *b)
{
  int t ;
  t = *a;
  *a = *b;
  *b = t;
}
