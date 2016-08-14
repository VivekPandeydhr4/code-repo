#include<stdio.h>
#include<unistd.h>

int main()
{
  printf("\n P Id: %d\n", (int)getpid());
  printf("\n PP Id: %d\n", (int)getppid());
  return 0;
}
