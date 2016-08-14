#include <stdio.h>
#include <stdlib.h>

void insrton_sort(int arr[], int ar1[], int size)
{
  int i, j, key;

  for (i=1; i<size; i++)
    {
      key = ar1[i];
      j = i-1;

      while((arr[key]<arr[ar1[j]]) &&(j>=0))
	{
	  ar1[j+1] = ar1[j];
	  j = j-1;
	}
      ar1[j+1] = key;
    }
}

void isertion_sort(int arr[], int ar1[], int size)
{
  int i, j, key;

  for (i=1; i<size; i++)
    {
      key = arr[i];
      j = i-1;

      while((arr[key]<arr[j]) &&(j>=0))
	{
	  ar1[j+1] = ar1[j];
	  j = j-1;
	}
      ar1[j+1] = key;
    }  
}

int main()
{
  int arr[] = {2, 5, 3, 1, 8, 10, 4, 12, 11, 9};
  int size = sizeof(arr)/sizeof(arr[0]);
  int *ar1 = (int*)malloc(size*sizeof(arr[0]));
  int i;

  for (i=0; i<size; i++)
    ar1[i] = i;

  printf("arr\n");
  for (i=0; i<size; i++)
    printf("%d ", arr[i]);
  printf("\n");

  printf("ar1\n");
  for (i=0; i<size; i++)
    printf("%d ", ar1[i]);
  printf("\n");

  insrton_sort(arr, ar1, size);

  printf("AS ar1\n");
  for (i=0; i<size; i++)
    printf("%d ", ar1[i]);
  printf("\n");

  printf("AS arr\n");
  for (i=0; i<size; i++)
    printf("%d ", arr[i]);
  printf("\n");

  printf("sorted arr\n");
  for (i=0; i<size; i++)
    printf("%d ", arr[ar1[i]]);
  printf("\n");

  printf("\n");
  return 0;
}
