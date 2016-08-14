#include "header.h"

void merge(int arr[], int p, int q, int r)
{
  int n1 = q - p + 1;
  int n2 = r - q;

  int left[n1], right[n2];

  int i=0, j=0, k=0;

  for(i=0; i<n1; i++)
    {
      left[i] = arr[p+i];
    }

  for(j=0; j<n2; j++)
    {
      right[j] = arr[q+j+1];
    }

  for(i=0, j=0, k=p; k<=r; k++)
    {
# if 0      
      if((j==n2) || (left[i] <= right[j]))
	{
	  //if (i<n1)
	    arr[k] = left[i++];
	}
      else 
	{
	  //if (j<n2)
	    arr[k] = right[j++];
	}
# endif

# if 1      
      if(i==n1 || j==n2)
	{
	  if(i==n1)
	    {
	      arr[k]=right[j++];
	    }
	  else
	    {
	      arr[k]=left[i++];
	    }
	}
      else
	{
	  if(left[i]<=right[j])
	    {
	      arr[k]=left[i++];
	    }
	  else
	    {
	      arr[k]=right[j++];
	    }
	}
# endif 

    }

}

void merge_sort(int arr[], int p, int r)
{
  if(p<r)
    {
      int q = (p+r)/2;
      merge_sort(arr, p, q);
      merge_sort(arr, q+1, r);
      merge(arr, p, q, r);
    }
}

int main ()
{
  /*************************************************************/
  int arr[] = {-1, 11, 0, 2, 4, 3, 12, 6, -2, 10, -9, 8, 1};
  int size = sizeof(arr)/sizeof(int);
  printf(" Array :=>\n");
  print(arr, size);
  /*************************************************************/

  merge_sort(arr, 0, size-1);
  printf("\nAfter sorting :=>\n");
  print(arr, size);
  printf("\n");
  return 0;
}
