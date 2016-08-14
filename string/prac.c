#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
  const char ch1 = 'z';
  const char ch2 = 'A';
  int arr['a' - 'A'] = {0};
  int size = sizeof(arr)/sizeof(int);

  printf("%c  -  %c, %c  -  %c\n",'A', 'Z', 'a', 'z');
  printf("%d - %d, %d - %d\n",'A', 'Z', 'a', 'z');

  printf("Size = %d", size);

  printf("\n");
  return 0;
}
