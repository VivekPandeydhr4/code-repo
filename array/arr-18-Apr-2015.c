#include "header.h"

int max_diff(int *arr, int n)
{
  int i, j;
  int max_diff=0;

  for (i=0; i<n; i++)
    {
      for (j=i+1; j<n; j++)
	{
	  if ((arr[j]>arr[i]) && 
              ((arr[j]-arr[i]) > max_diff))

	    max_diff = arr[j] - arr[i];
	}
    }

  return max_diff;
}

int max_diff_2(int arr[], int n)
{
  int i, j;
  int max_diff=arr[1] - arr[0];
  int min_element = arr[0];

  for (i=1; i<n; i++)
    {
      if (arr[i] - min_element > max_diff)
	max_diff = arr[i] - min_element;

      if (arr[i] < min_element)
	min_element = arr[i];
    }
  return max_diff;
}

int main()
{
  /*************************************************************/
  int arr[] = {2, 3, 10, 6, 14, 8};
  int size = sizeof(arr)/sizeof(int);
  printf("\n ***** Array ***** \n");
  print(arr, size);                                                                                                               
  /*************************************************************/

  printf("Max Diff = %d\n", max_diff(arr, size));

  printf("Max Diff 2 = %d\n", max_diff_2(arr, size));
 
  printf("\n");
  return 0;
}
