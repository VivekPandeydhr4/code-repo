#include <stdio.h>
#include <stdlib.h>

float Water_in_i_j_th_glass(float x, int i, int j)
{
  int m ,n, end;
  float curr,prev=0;
  float* A=malloc(1<<i*sizeof(float));
  A[0]=x;

  if(x<=0.0) return 0.0;
  printf("%f\n",A[0]);
  for(m=1;m<=i;m++)
    {
      end=(1<<m) -1;
      for(n=0;n<=end;n++)
	{
	  curr=A[n];
	  if(n==0) A[0]=(A[0]-1)/2;
	  else if(n==end) A[end]=(prev-1)/2;
	  else A[n]=(prev-1)/2+(A[n]-1)/2;
	  if(A[n]<=0) return 0.0;
	  if(m==i&&n==j) return A[n];
	  prev=curr;
	  printf("%f ",A[n]);
	}
      printf("\n");
    }
  return A[j];
}

int main()
{


  printf("%f\n",Water_in_i_j_th_glass(10.0,3,6));
  return 0;
}
