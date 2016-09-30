#include "header.h"

int partition(int arr[], int p, int r)
{
  int x = arr[r];
  int i = p-1;

  int j=0;

  for(j=p; j<=r-1; j++)
    {
      if(arr[j] <= x)
	{
	  i = i + 1;
	  swap (arr+i, arr+j);
	}
    }

  swap(arr+i+1, arr+r);
  return (i+1);
}

void quick_sort(int arr[], int p, int r)
{
  if(p<r)
    {
      int q=partition(arr, p, r);
      quick_sort(arr, p, q-1);
      quick_sort(arr, q+1, r);
    }
}

int main ()
{
  /*************************************************************/
  int arr[] = {-1, 11, 0, 2, 4, -1, 6, -2, 1, 10, -9, 8, 1, 1};
  int size = sizeof(arr)/sizeof(int);
  printf(" Array :=>\n");
  print(arr, size);
  /*************************************************************/

  quick_sort(arr, 0, size-1);
  printf("\nAfter sorting :=>\n");
  print(arr, size);
  printf("\n");
  return 0;
}
