#include <stdio.h>
#include <math.h>
 
int main()
{
  int arr[] = {1, 2, 3, 4, 5};
  int *p = NULL;
  p = arr;

  printf("Address of arr = %p", arr);
  printf("Address of arr+1 = %p", arr+1);
  printf("Address of arr+2 = %p", arr+2);
  printf("Address of arr+3 = %p", arr+3);
  printf("Address of arr+4 = %p", arr+4);

  arr++;

  printf("Address of arr = %p", arr);

  printf("\n");
  return 0;
}
