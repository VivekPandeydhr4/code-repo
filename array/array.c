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

int dup_withing_k_distant(int arr[], int n, int k)
{
  int i=0, j=0;

  for(i=0; i<n; i++)
    {
      for(j=i+1; j<=i+k && j<n; j++)
	{
	  if(arr[i] == arr[j])
	    return 1;
	}
    }
  return 0;
}
int maj_condidate(int arr[], int size)
{
  int maj_index=0, i=0, count=1;
  
  for(i=1; i<size; i++)
    {
      if(arr[i] == arr[maj_index]) count++;
      else count--;
      if(count==0)
	{
	  maj_index = i;
	  count++;
	}
    }
  return arr[maj_index];
}
void maj_element(int arr[], int size)
{
  int i=0, count=0;
  int condidate = maj_condidate(arr, size);
  for (i=0; i<size; i++)
    {
      if(arr[i] == condidate) 
	count++;
    }
  if(count > size/2) printf("Majority Element = %d\n", condidate);
  else printf("  None\n");
}

int fun(int *A, int n, int k)
{
  int i;
  
  for (i=0; i< 2*n-k-1; i++)
    {
      if (A[i]==0 && A[i+k+1]==0)
	{
	  A[i] = A[i+k+1] = k;
	  if (k==n) return 1;
	  else
	    {
	      int v = fun(A, n, k+1);
	      if (v==1) return 1;
	      else A[i] = A[i+k+1] = 0;
	    }
	}
    }
  return 0;
}

void filln(int n)
{
  int *A;
  A = (int*)malloc(2*n*sizeof(int));

  if (fun(A, n, 1)) print(A, 2*n);
  else printf("Not Possible\n");
     
}

int main()
{
  /*************************************************************/
  //  int arr[] = {21, 11, 0, 2, 14, 1, 16, 2, 1, 10, 9, -8, 51, 41, 41};
  int arr[] = {1, 2, 4, 4, 4, 5, 6, 4, 4};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  //  print(arr, size);
  /*************************************************************/
  
  //  maj_element(arr, size);

  filln(3);

  //  printf("\nSecond Minimum Element = %d\n", second_min(arr, size));
  //int k=3;
  //  printf("\n Dup within [%d] distance = %s\n", k, 
  //	 (dup_withing_k_distant(arr, size, k)?"Yes":"No"));
  printf("\n");
  return 0;
}
