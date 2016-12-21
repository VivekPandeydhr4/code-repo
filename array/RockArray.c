#include "header.h"

int abs_sum_sorted_arr(int arr[], int size)
{
   int i=0, j=0, sum=0;

   for(i=0; i<size-1; i++)
    for (j=i+1; j<size; j++)
    	sum += arr[j]-arr[i];
    return sum;
}

int abs_sum_sorted_arr_1(int arr[], int size)
{
   int i=0, sum=arr[1]-arr[0];;
   int p_sum = arr[1]-arr[0];
   
   for(i=2; i<size; i++)
    {
        
    	p_sum = p_sum+(arr[i]-arr[i-1])*(i);
	sum = sum + p_sum;
	//printf("\nsum = %d,  p_sum = %d\n", sum, p_sum);
    }
    return sum;
}

int abs_sum_sorted_arr_2(int arr[], int size)
{
   int i=0, sum=0;

   for(i=0; i<size; i++)
    	sum += (arr[i])*(i)-(arr[i])*(size-i-1);
    return sum;
}

int main()
{
  /*************************************************************/
  //  int arr[] = {21, 11, 0, 2, 14, 1, 16, 2, 1, 10, 9, -8, 51, 41, 41};
  //int arr[] = {1, 2, 4, 4, 4, 5, 6, 4, 4};
  int arr[] = {3, 5, 8, 13, 14, 16, 21, 24, 27};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  print(arr, size);
  printf("\n");
  /*************************************************************/
  
  printf("==> Absolute sum 0 = %d\n", abs_sum_sorted_arr(arr, size));
  printf("==> Absolute sum 1 = %d\n", abs_sum_sorted_arr_1(arr, size));
  printf("==> Absolute sum 2 = %d\n", abs_sum_sorted_arr_2(arr, size));

  printf("\n");
  return 0;
}
