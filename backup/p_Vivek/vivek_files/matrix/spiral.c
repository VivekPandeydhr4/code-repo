//#include "header.h"

#include<stdio.h>
#include<stdlib.h>

#define ROW 3
#define COLUMN 4

void print_matrix(int arr[][COLUMN])
{
  int i,j;

  for(i=0,j=0; i<ROW; i++)
    {
      for(j=0; j<COLUMN; j++)
	{
	  printf("%2d ", arr[i][j]);
	}
      printf("\n\t");
    }
}

void spiral_print(int arr[][COLUMN])
{
  int i, j, k;

  int row=ROW, col=COLUMN;

  for(k=0; row>=0 || col>=0; k++)
    {
      for (i=k, j=k; j<col+k; j++)
	printf("%d ", arr[i][j]);
      
      for (j--, i++; i<row+k; i++)
	printf("%d ", arr[i][j]);

      row--;
      col--;

      for (i--, j--; j>=k; j--)
	printf("%d ", arr[i][j]);

      for (i--, j++; i>k; i--)
	printf("%d ", arr[i][j]);

      row--;
      col--;      
    }
}

int main()
{

  int arr[][COLUMN] = { {1, 2, 3, 4}, 
			{5, 6, 7, 8}, 
			//			{9, 10, 11, 12},
			{13, 14, 15, 16}
                                        };

  printf("\n *** ***  Matrix *** *** \n\n\t");

  print_matrix(arr);

  printf("\n *** ***  Spiral *** *** \n\n");

  spiral_print(arr);

  printf("\n\n");

  return 0;
}
