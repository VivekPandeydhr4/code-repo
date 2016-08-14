#include <stdio.h>
#include <string.h>

int subtract (int n1, int n2)
{
  int n = n1 + n2;
  return n;
}

int main()
{
  int sum = subtract(5, 7);
  
  char ch[] = "Hello";
  
  printf("Size = %d", sizeof(ch));
  printf("Length = %d", strlen(ch));

  printf("\n");
  return 0;
}
