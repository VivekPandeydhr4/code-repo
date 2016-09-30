#include "header.h"


int second_min(int *arr, int size)
{
  int min=arr[0];
  int min_2=arr[0];
  int i=0;

  for (i=1; i<size; i++)
    {
      if (arr[i] < min)
	{
	  if (min != min_2)
	    min_2 = min;
	  min = arr[i];
	}
      else if ((arr[i] > min) && (arr[i] < min_2))
	{
	  min_2 = arr[i];
	}
    }
  return min_2;
}

int max_array(int arr[], int size)
{
  int m;

  if (size > 1)
    {
      m = max_array(arr+1, --size);
      if (m > arr[0])
	return m;
    }
  return arr[0];
}

int main()
{
  /*************************************************************/
  int arr[] = {21, 11, 0, 2, 14, 1, 16, 2, 1, 10, 9, -8, 51, 41, 41};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  print(arr, size);
  /*************************************************************/
  
  //  printf("\nSecond Minimum Element = %d\n", second_min(arr, size));
  printf("\n Maximum Element = %d\n", max_array(arr, size));
  printf("\n");
  return 0;
}
