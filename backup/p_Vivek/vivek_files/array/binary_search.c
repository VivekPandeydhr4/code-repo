#include "header.h"
#include<math.h>

int nearPerfectSquare(int num)
{
  int n = 1;

  while (num > (n*n))
    n++;

  if (((n*n) - num) > (num - ((n-1)*(n-1))))
    return (n-1)*(n-1);
  else
    return n*n;
}

int main()
{
  /*************************************************************/
  int arr[] = {1, 11, 0, 2, 4, 1, 6, 2, 1, 10, 9, -8, 1, 1};
  int size = sizeof(arr)/sizeof(int);
  printf("\n\t ***** Array ***** \n\n  ");
  print(arr, size);
  /*************************************************************/

  int num = 23;
  printf("\nNear Perfect Square of %d = %d", num, nearPerfectSquare(num));
  printf("\n");
  return 0;
}
