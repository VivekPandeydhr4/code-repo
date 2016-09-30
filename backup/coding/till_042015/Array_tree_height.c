#include <stdio.h>
#include <stdlib.h>

void ht(int *A, int n, int i)
{
  if(A[i]>=0) 
    {
      ht(A,n,A[i]);
      A[i]=A[A[i]]-1;
    }
}
int height(int *A, int n)
{
  int i,min;
  for(i=0;i<n;i++) ht(A,n,i);
  for(min=A[0],i=1;i<n;i++) {printf("%d,",A[i-1]);if(A[i]<min) min=A[i];}
  printf("%d\n",A[i-1]);
  return -min;
}
int main()
{
  int A[7]={1,5,5,2,2,-1,3};
  int B[]={-1,0,0,1,1,3,5};
  printf("\nHeight of the tree: %d\n",height(B,7));
  return 0;
}
