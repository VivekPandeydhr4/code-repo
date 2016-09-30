#include<stdio.h>
#include<stdlib.h>

#define SIZE 5

#define min2(a, b) (a < b) ? (a) : (b)

#define min3(a, b, c) (min2(a,b) < c) ? (min2(a,b)) : (c) 

void print_matrix(int arr[SIZE][SIZE])
{
  int i,j;

  for(i=0,j=0; i<SIZE; i++)
    {
      for(j=0; j<SIZE; j++)
	{
	  printf("%2d ", arr[i][j]);
	}
      printf("\n");
    }
}

int minimum(int x, int y, int z)
{
  int a;
  if (x < y)
    a = x;
  else
    a = y;

  if (a < z)
    return a;
  else
    return z;
}
void max_matrix(int arr[SIZE][SIZE])
{
  int i, j;
  int max = 0, i_max = -1, j_max = -1;
  
  for (i=0; i<SIZE; i++)
    {
      for (j=0; j<SIZE; j++)
	{
	  if (arr[i][j])
	    {
	      arr[i][j] = 1 + minimum(arr[i-1][j], arr[i][j-1], arr[i-1][j-1]);
	      if(arr[i][j] > max)
		{
		  max = arr[i][j];
		  i_max = i;
		  j_max = j;
		}
	    }
	}
    }
  printf("\n\tMax Matrix Index arr[%d][%d] of size %d\n",i_max-max+1,j_max-max+1,max);
}
int main()
{

  int arr[SIZE][SIZE] = { {1, 0, 1, 1, 0}, 
		 	  {0, 0, 1, 1, 1}, 
			  {0, 1, 1, 1, 1},
			  {1, 1, 1, 1, 1},
                          {0, 1, 0, 0, 1}
                                        };

  printf("\n *** ***  Matrix *** *** \n\n");

  print_matrix(arr);
  printf("\n\n");

  max_matrix(arr);

    //printf("Min = %d", min3(2, 14, 65));
  printf("\n\n");

  return 0;
}
