#include <stdio.h>

int main()
{
  int tcase, num, i;
  
  int arr[100]={0};
  arr[0] = 1;
  for(i=1; i<100; i++)
    {
      arr[i] = arr[i-1]*(i+1);
    }
  //  scanf("%d", &tcase);
  //while(tcase--)
  //{
      scanf("%d", &num);
      printf("%d\n", arr[num-1]);
      //}
  
  return 0;
}
