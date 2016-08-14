#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

  int i=0; 
  
  for (i=0; i<10; i++)
    {
      //srand(time(NULL));
      int r = rand()%12;
      
      printf("Rand = %d\n", r);
    }
  return 0;
}
