#include "header.h"

void rearrange(int arr[], int n)
{
  int i, j, k, t1, t2, zero;

  zero = arr[0];

  for (i=1; i<n; i++)
    {
      k=i;
      t1 = arr[i];
      while(t1>=0 && arr[t1] >= 0)
	{
	  t2 = arr[t1];
	  arr[t1] = -i;
	  i = t1;
	  t1 = t2;
	  if (i==0) break;
	}
      i = k;
    }
  
  arr[zero] = 0;
  for(i=0; i<n; i++)
    arr[i] = -arr[i];
}

int missing_AP(int *arr, int n)
{
  if (n<2) return -1;
  if (n==2)
    {
      if ((arr[1] - arr[0])%2) return -1;
      else
	return arr[0] + (arr[1] - arr[0]);
    }
  if (arr[1]-arr[0] != arr[2]-arr[1])
    {
      if (arr[1]-arr[0] < arr[2]-arr[1])
	return arr[1] + arr[1] - arr[0];
      else
	return arr[0] + arr[2] - arr[1];
    }
  
  int d = arr[1] - arr[0];
  int j=0;
  for (j=3; j<n; j++)
    {
      if (arr[j]-arr[j-1] != d)
	return arr[j-1] + d;
    }

  return -1;
}

int binary_search(int arr[], int s, int E, int d)
{
  int mid;

  if (s+1 == E) return arr[s]+d;

  mid = s+(E-s)/2;

  if (arr[mid] - arr[s] > (mid-s)*d)
    return binary_search(arr, s, mid, d);
  else
    return binary_search(arr, mid, E, d);
}

int missing_AP_1(int *arr, int n)
{
  if (n<2) return -1;
  if (n==2)
    {
      if ((arr[1] - arr[0])%2) return -1;
      else
	return arr[0] + (arr[1] - arr[0]);
    }
  if (arr[1]-arr[0] != arr[2]-arr[1])
    {
      if (arr[1]-arr[0] < arr[2]-arr[1])
	return arr[1] + arr[1] - arr[0];
      else
	return arr[0] + arr[2] - arr[1];
    }

  int d = arr[1] - arr[0];

  return binary_search(arr, 0, n-1, d);
}

int main()
{
  /*************************************************************/
  //  int arr[] = {1, 0};// 3, 1, 2, 4, 6, 8, 7, 5, 9};
  int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 20, 22};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  print(arr, size);
  /*************************************************************/
  
  printf("Missing No: %d", missing_AP (arr, size)); 
  /*
  rearrange(arr, size);

  printf("\n\t ***** After rearrange Array ***** \n\n  ");
  print(arr, size);
  */
  printf("\n");
  return 0;
}
