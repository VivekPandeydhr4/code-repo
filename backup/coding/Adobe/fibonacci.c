#include <stdio.h>
#include <stdlib.h>
void Mat_multiply(int A[][2], int B[][2], int C[][2])
{
  C[0][0]=A[0][0]*B[0][0]+A[0][1]*B[1][0];
  C[0][1]=A[0][0]*B[0][1]+A[0][1]*B[1][1];
  C[1][0]=A[1][0]*B[0][0]+A[1][1]*B[1][0];
  C[1][1]=A[1][0]*B[0][1]+A[1][1]*B[1][1];
}
void Matrix_Power(int A[][2], int n)
{
  int B[2][2],C[2][2];
  if(n>1)
    {
      Matrix_Power(A,n/2);
      Mat_multiply(A,A,B);      
      if(n%2)
	{
	  C[0][0]=0;C[0][1]=1;C[1][0]=1;C[1][1]=1;
	  Mat_multiply(B,C,A);
	}
      else {A[0][0]=B[0][0];A[0][1]=B[0][1];A[1][0]=B[1][0];A[1][1]=B[1][1];}
    }
}
int fibonacci(int n)
{
  int A[2][2]={{0,1},{1,1}};
  if(n==0) return 0;
  else if(n<=2) return 1; 
  Matrix_Power(A,n-1);
  return A[1][1];
}
void print_matrix(int M[][2])
{
  int i,j;
  for(i=0;i<2;i++)
    {
      for(j=0;j<2;j++)
	printf("%d ",M[i][j]);
      printf("\n");
    }  
}
int main()
{  
  int i,**M;
  /* M=(int**)malloc(sizeof(int*)*2); */
  /* M[0]=(int*)malloc(sizeof(int)*2); */
  /* M[1]=(int*)malloc(sizeof(int)*2); */
  /* M[0][0]=1;  M[0][1]=2;  M[1][0]=3;  M[1][1]=4; */

  /* print_matrix(M); */
  for(i=0;i<20;i++)
    printf("%d\n",fibonacci(i));
  return 0;
}

