#include <stdio.h>
#include <string.h>

#define COLUMN 7

void print_matrix(char mat[][COLUMN], int row)
{
  int i=0, j=0;
  
  for (i=0, j=0; i<row; i++)
    {
      for (j=0; j<COLUMN; j++)
	{
	  printf("%c ", mat[i][j]);
	}
      printf("\n\t");
    }
}

int main()
{
  char mat[][COLUMN] = { {'a', 'b', 'c', 'd', 'e', 'f', 'g'},
			 {'h', 'i', 'j', 'k', 'l', 'm', 'n'},
			 {'o', 'p', 'q', 'r', 's', 't', 'u'},
			 {'v', 'w', 'x', 'y', 'z', '1', '2'},
			 {'3', '4', '5', '6', '7', '8', '9'}
  };

  int row = sizeof(mat)/sizeof(mat[0]);
  printf("\n   **** Given  Matrix ****\n\n\t");

  print_matrix(mat, row);


  //  printf("Row = %d", row);
  printf("\n");
  return 0;
}
