#include <stdio.h>
#include <stdlib.h>

#if 1
typedef struct bitfield
{
  unsigned int x: 4;
  unsigned int y: 5;

}btfld;
#endif

#if 0
typedef struct bitfield
{
  unsigned int x;
  unsigned int y;

}btfld;
#endif

int main()
{

  btfld b1;

  b1.x=0;
  b1.y=32;

  printf("Size of btfld = %lu\n", sizeof(b1));

  printf("Values of x = %d\n", b1.x);
  printf("Values of y = %d\n", b1.y);

  //  printf("Address of x = %p\n", &b1.x);
  //printf("Address of y = %p\n", &b1.y);

  printf("\n");
  return 0;
}
