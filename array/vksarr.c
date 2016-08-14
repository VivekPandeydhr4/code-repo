#include "header.h"

int max_sum_subarray(int *arr, int n)
{
  int sum, i, j, max_sum, max_i, max_j;

  i=j=sum=0;

  max_i=max_j=max_sum=-1;

  while(j < n)
    {
      sum = sum + arr[j];
      if (sum <= 0)
	{
	  i = j + 1;
	  sum = 0;
	}
      else if(sum > max_sum)
	{
	  max_sum = sum;
	  max_i = i;
	  max_j = j;
	}
      j++;
    }
  printf("Max Sum Indx ==> %d, %d \n",max_i, max_j);
  return max_sum;
}

int element_same_Indx(int arr[], int size)
{
  int S, E, mid;

  if (size>0)
    {
      S=0;
      E=size-1;
      while(S<=E)
	{
	  mid = S+(E-S)/2;
	  
	  if (arr[mid] == mid) return mid;
	  else if (arr[mid] < mid) S = mid+1;
	  else E = mid-1;
	}
      return -1;
    }
  else
    return -1;
}

int brick_ways_1(int n)
{
  if (n<0) return -1;
  if (n<=3) return 1;
  return (brick_ways_1(n-1)+brick_ways_1(n-4));
}

int brick_ways_2(int n)
{
  int *arr = (int*) malloc(sizeof(int)*(n+1));
  int j;
  arr[0]=arr[1]=arr[2]=arr[3]=1;
  
  for(j=0; j<=n; j++)
    arr[j]= arr[j-1] + arr[j-4];

  return arr[n];
}

void fun_2 (int *arr, int n, char *s, int i, int j)
{
  if (i>=n)
    {
      s[i] = '\0';
      printf(" %s\n",s);
    }
  else
    {
      if (arr[j])
	{
	  s[j] = arr[i]+ 'A'-1;
	  fun_2(arr, n, s, i+1, j+1);
	}
      if ((i<n-1)&&(arr[i]<2 || (arr[i]==2 && arr[i+1]<=6)))
	{
	  s[j] = 'A' + arr[i]*10 + arr[i]-1;
	  fun_2(arr, n, s, i+2, j+1);
	}
    }
}

void string(int arr[], int n)
{
  char *s;
  if (n>0)
    {
      s = (char*) malloc(n);
      memset(s, 0, n);
      fun_2(arr, n, s, 0, 0);
    }
}

int minJumps(int *arr, int size)
{
  int *jumps = (int*) malloc ((size+1)*sizeof(int));
  int min, i, j;
  if(size>0)
    {
      jumps[size] = 0;
      for (i=size-1; i>0; i--)
	{
	  min = INT_MAX;
	  for(j=i+1; j <= i+arr[i]; j++)
	    {
	      if (j>size) break;
	      if (min > jumps[j]) min = jumps[j];
	    }
	  if(min != INT_MAX)
	    jumps[i] = min+1;
	  else 
	    jumps[i] = min;
	}
      return jumps[1];
    }
  else
    return INT_MAX;
}

int making_change(int *D, int n, int k)
{
  int *T = (int*) malloc((n+1)*sizeof(int));
  int i, j;
  for(i=0; i<k; i++)
    {
      for(j=D[i]; j<=n; j++)
	{
	  T[j] += T[j-D[i]];
	}
    }
  return T[n];
}

void print_subsequence(int arr[], int *c, int max)
{
  if (max >= 0)
    {
      print_subsequence(arr, c, c[max]);
      printf("%d, ", arr[max]);
    }
  //printf("\n");
}

int largest_sum_increasing_subseq(int arr[], int n)
{
  int *B, *C, i, j, max;

  if (n>0)
    {
      B = (int *) malloc(n*sizeof(int));
      C = (int *) malloc(n*sizeof(int));

      for(i=0; i<n; i++)
	{
	  B[i] = arr[i];
	  C[i] = -1;
	  for (j=i-1; j>=0; j--)
	    {
	      if ((arr[j] < arr[i]) &&
		  (B[j]+arr[i] > B[i]))
		{
		  B[i] = B[j] + arr[i];
		  C[i] = j;
		}
	    }
	}
      max = 0;
      for (i=1; i<n; i++)
	{
	  if (B[i]>B[max])
	    max = i;
	}
      print_subsequence(arr, C, max);
      
    }
  return B[max];
}



int main()
{
  /*************************************************************/
  int arr[] = {1, 2, -3, 7, 8};//, 4, 5, -6, 4, -4};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  print(arr, size);                                                                                                               
  /*************************************************************/
  
  int n = largest_sum_increasing_subseq(arr, size);
  printf("\nSum = %d\n", n);

  //printf("Total Ways = %d", making_change(arr, size, 4));
  /*
  int arr1[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
  int size1 = sizeof(arr1)/sizeof(int);
  print(arr1, size1);
  printf("Min Jump = %d", minJumps(arr1, size1));

  //  string(arr, size);
  /*
  int no_way = brick_ways_2(4);
  printf("Brick ways = %d", no_way);

  /*
  int elmnt = element_same_Indx(arr, size);
  printf("Same Indx element = %d", elmnt);

  /*
  printf("Max Sum = %d\n",max_sum_subarray(arr, size));
  */
  printf("\n");
  return 0;
}
