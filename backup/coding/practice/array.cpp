#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
/****************************************/
int  f1(int *A, int s, int e)
{
  int mid;
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if(A[mid-1]>A[mid] && A[mid]<A[mid+1]) return mid;
      else if(A[mid]<A[e]) return f1(A,s,mid-1);
      else return f1(A,mid+1,e);
    }
  else return -1;
}
int Pivot_in_Sorted_rotated(int *A, int n)
{
  if(A[n-1]>A[0]) return 0;
  if(n>1 && A[n-1]<A[n-2]) return n-1;
  return f1(A,1,n-2);
}

int search_in_Sorted_Rotated_without_finding_pivot(int *A, int s, int e, int x)
{
  int mid;
  if(s<=e)
    {
      mid=s+(e-s)/2;
      if(A[mid]==x) return mid;
      else if((A[mid]<A[e] && (A[mid]<x && x<=A[e]))||(A[mid]>A[e] && (x>A[mid]||x<=A[e]))) return search_in_Sorted_Rotated_without_finding_pivot(A,mid+1,e,x);
      else return search_in_Sorted_Rotated_without_finding_pivot(A,s,mid-1,x);
    }
  else return -1;
}

void pascal_line(int n)
{
  int i,j,old,t,*A;
  A=(int*)malloc((n+1)*sizeof(int));
  A[0]=1;
  for(i=1;i<=n;i++)
    {
      old=1;
      for(j=1;j<i;j++)
	{
	  t=A[j];A[j]+=old;old=t;
	}
      A[j]=1;
    }
  for(i=0;i<=n;i++)  printf("%d ",A[i]);
  printf("\n");
}

// void comb(int *A, int s, int n, int *B, int k, int r)
// {
//   int i;
//   if(k==r){for(i=0;i<r;i++) printf("%d ", A[i]); printf("\n");}
//   else
//     {
//       for(i=s;i<=n-r+k;i++)
// 	{
// 	  B[k]=A[i];
// 	  comb(A,i+1,n,B,k+1,r);
// 	}      
//     }
// }

void comb(int A[], int C[], int n,int r, int k, int b )
{
  int i;
  if(b==r){for(i=0;i<r;i++) printf("%d ", C[i]);printf("\n");}
  else
    {
      for(i=k;i<=n-r+b;i++)
	{
	  C[b]=A[i];
	  comb(A,C,n,r,i+1,b+1);
	}

    }
}
void combination(int *A, int n, int r)
{
  int *B=(int*)malloc(r*sizeof(int));
  comb(A,B,n,r,0,0);
}

void perm(int *A, int s, int n)
{
  int i,t;
  if(s==n){for(i=0;i<n;i++)printf("%d ",A[i]);printf("\n");}
  else
    {
      for(i=s;i<n;i++)
	{
	  t=A[s];A[s]=A[i];A[i]=t;
	  perm(A,s+1,n);
	  t=A[s];A[s]=A[i];A[i]=t;
	}
    }
}
void permutaion(int *A, int n)
{
  perm(A,0,n);
}

void ReArrange_to_place_i_at_Ai(int *A, int n)
{//Erroneous
  int i,j,zero,t,t2;
  if(A && n>1)
    {
      zero=A[0];
      for(i=1;i<n;)
	{
	  if(A[i]<0) {i++;continue;}
	  j=i;t=A[i];
	  while(t>=0)
	    {
	      A[i]=-A[i];
	      t2=A[t];A[t]=i;
	      i=t;t=t2;
	    }
	  i=j+1;
	}
      A[zero]=0;
      for(i=0;i<n;i++) A[i]=-A[i];
    }
}
void sortAsWave(int A[], int n)
{
  int i,t;
  if(A && n>1)
    {
      for(i=0;i<n-1;i++)
	{
	  if((i%2 && A[i]>A[i+1])||(!(i%2) && A[i]<A[i+1])) {t=A[i];A[i]=A[i+1];A[i+1]=t;}
	}
    }
}

int min_distance_between_a_and_b(int *A, int n, int a, int b)
{
  int a_pos,b_pos,d,i,pre;
  if(a==b) return 0;
  if(n<=1) return -1;
  a_pos=b_pos=-1;

  for(i=0;i<n;i++)
    {
      if(A[i]==a || A[i]==b)
	{
	  if(A[i]==a) a_pos=i;
	  else b_pos=i;
	  if(a_pos>=0 && b_pos>=0) break;
	}
    }
  if(i==n) return -1;

  if(a_pos>b_pos) {d=(a_pos-b_pos); pre=a_pos;}    
  else {d=(b_pos-a_pos); pre=b_pos;}

  for(i++;i<n;i++)
    {
      if(A[i]==a || A[i]==b)
	{
	  if(A[i]==A[pre]) pre=i;
	  else
	    {
	      if(d>i-pre) d=i-pre;
	      pre=i;
	    }
	}
    }
  return d;
}
/****************************************/
int main()
{

  int i,size, A[]={3,4,5},a=3,b=5;
  
  size=(sizeof(A))/sizeof(A[0]);

  for(i=0;i<size;i++)
    cout <<A[i]<<" ";
  cout <<endl;
  cout <<"a:"<<a<<",b:"<<b<<endl;
  cout<<min_distance_between_a_and_b(A,size,a,b)<<endl;
  // sortAsWave(A,size);
  // cout <<endl;
  // for(i=0;i<size;i++)
  //   cout <<A[i]<<" ";

  // ReArrange_to_place_i_at_Ai(A,size);
  // cout<<endl;
  // for(i=0;i<size;i++)
  //   cout <<A[i]<<" ";
  
  //combination(A,size,3);
  //permutaion(A,size);
  //for(i=0;i<=20;i++)pascal_line(i);
  // for(i=0;i<size;i++)
  //   cout<< search_in_Sorted_Rotated_without_finding_pivot(A,0,size-1,A[i])<<endl;
  //cout<<Pivot_in_Sorted_rotated(A,size)<<endl;
  return 0;
}
