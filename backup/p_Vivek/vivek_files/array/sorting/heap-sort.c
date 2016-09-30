#include "header.h"

void max_heapify(int arr[], int pos, int size)
{
  int left = 2*pos+1;
  int right = 2*(pos+1);

  int largest;

  if((left < size) && (arr[left] > arr[pos]))
    largest = left;
  else largest = pos;

  if((right < size) && (arr[right] > arr[largest]))
    largest = right;

  if(largest != pos)
    {
      swap(arr+pos, arr+largest);
      max_heapify(arr, largest, size);
    }
}

void build_max_heap(int arr[], int length)
{
  int i=0;
  
  for(i=(length-1)/2; i>=0; i--)
    {
      max_heapify(arr, i, length-1);
    }
}

void heap_sort(int arr[], int size)
{
  int i=0;
  
  build_max_heap(arr, size);

  for(i = size-1; i>=0; i--)
    {
      swap(arr, arr+i);
      size--;
      max_heapify(arr, 0, size);
    }
}

int main ()
{
  /*************************************************************/
  int arr[] = {-1, 11, 0, 2, 4, 5, 6, -2, 1, 10, -9, 8, 16, 14};
  int size = sizeof(arr)/sizeof(int);
  printf(" Array :=>\n");
  print(arr, size);
  /*************************************************************/

  heap_sort(arr, size);
  printf("\nAfter sorting :=>\n");
  print(arr, size);
  printf("\n");
  return 0;
}
