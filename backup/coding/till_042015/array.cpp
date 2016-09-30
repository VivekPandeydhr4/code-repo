#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
int smallest_in_sortedRotatedArray(int *A, int n);
int* NextGreater(int A[], int n);
void merge_intervals();
int main()
{
  int i,*B, A[10]={12, 34, 1, 23, 4, 41, 56, 20, 34, 10};
  // i= smallest_in_sortedRotatedArray(A,10);
  merge_intervals();
  // B=NextGreater(A,10);
  // for(i=0;i<10;i++) 
  //   printf("%d ",A[i]);
  // printf("\n");
  // for(i=0;i<10;i++) 
  //   printf("%d ",B[i]);
  printf("\n");
  return 0;
}
bool comp(int a, int b)
{//a<b
  int i,j;
  if(a<0) i=-1*a;else i=a;
  if(b<0) j=-1*b;else j=b;
  if(i<j) return 1;
  else if(i==j && a<0) return 1;
  else return 0;
}
void merge_intervals()
{
  int i,a,b,*A,n,count;
  scanf("%d\n",&n);
  A=(int*)malloc(2*n*sizeof(int));
  scanf("(%d,%d)",&a,&b);
  for(i=0;i<n-1;i++)
    {
      A[2*i]=a;A[2*i+1]=(-1)*b;
      scanf(" (%d,%d)",&a,&b);
      //cout <<a <<" "<<b<<endl;

    }
  for(i=0;i<2*n;i++) 
     printf("%d ",A[i]);

  sort(A,A+2*n,comp);
  for(i=0;i<2*n;i++) 
     printf("%d ",A[i]);
  count=0;
  for(i=0;i<2*n;i++)
    {
      if(A[i]>=0)count++;
      else count--;
      if(A[i]>=0 && count==1) printf("(%d,",A[i]);
      if(A[i]<0 && count==0) printf("%d) ",A[i]);
    }
  printf("\n");
}
int* NextGreater(int A[], int n)
{
  stack<int> S;
  int i, *B;
  B=(int*)malloc(n*sizeof(int));
  memset(B,-1,n*4);
  
  for(i=0;i<n;i++)
    {
      while(!S.empty() && A[S.top()]<A[i]) {B[S.top()]=A[i];S.pop();}
      S.push(i);
    }
  return B;
}

int smallest_in_sortedRotatedArray(int *A, int n)
{
  int s,e,mid;
  s=0;e=n-1;
  while(s<=e)
    {
      if(A[s]<=A[e]) return s;
      mid=(s+e)/2;
      if(A[mid-1]>A[mid]) return mid;
      if(A[mid]<A[e])e=mid-1;
      else s=mid+1;
    }
  return -1;
}
