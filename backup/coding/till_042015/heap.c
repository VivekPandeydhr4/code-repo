#include <stdio.h>

#define Parent(i) ((i-1)/2)
#define Left(i) (2*i+1)
#define Right(i) (2*i + 2)


void Heap_Sort(int A[],int n);
int main()
{

  int i,A[]={6,3,9,8,2,4,0,5,7,1};
  Heap_Sort(A,10);
  for(i=0;i<10;i++)
    {
      printf("%d ",A[i]);
    }
  printf("\n");
  return 0;
}

void Max_heapify(int A[], int n, int i)
{
  int largest,t;
  if(i<=Parent(n-1))
    {
      largest=i;
      if(Left(i)<n && A[Left(i)]>A[largest]) largest=Left(i);
      if(Right(i)<n && A[Right(i)]>A[largest]) largest=Right(i);
      if(largest!=i)
	{
	  t=A[i];
	  A[i]=A[largest];
	  A[largest]=t;
	  Max_heapify(A,n,largest);
	}
    }
}

void Make_heap(int A[], int n)
{
  int i;
  for(i=Parent(n-1);i>=0;i--)
    Max_heapify(A,n,i);
}

void Heap_Sort(int A[],int n)
{
  int i,t;
  Make_heap(A,n);
  for(i=0;i<n-1;i++)
    {
      t=A[0];
      A[0]=A[n-1-i];
      A[n-1-i]=t;
      if(i==n-2)continue;
      Max_heapify(A,n-1-i,0);
    }
}
