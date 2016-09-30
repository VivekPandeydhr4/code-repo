#include <iostream>
#include <algorithm>
using namespace std;

void print_array(int *A,int n)
{
  int i=0;
  for(i=0;i<n;i++) cout<<A[i]<<", ";
  cout <<endl;
}

int count_lesserTripletSum(int *A, int n, int k)
{
  int count,i,l,r;
  count=0;
  if(A && n>2)
    {
      sort(A,A+n);l=0;
      for(i=n-1;i>=2;i--)
	{
	  if(A[i]>=k) continue;
	  l=0;r=i-1;
	  while(l<r)
	    {
	      if(A[l]+A[r]+A[i]>=k) {count+=l;r--;}
	      if(A[l]+A[r]+A[i]<k) l++;
	    }
	}
      return count;
    }
  else return -1;
}
void merge(int *A, int *B, int s, int e)
{
  int mid, i,j,k;
  if(s<e)
    {
      mid=s+(e-s)/2;
      for(i=s;i<=mid;i++) B[i]=A[i];
      for(i=s,j=s,k=mid+1;j<=mid||k<=e;)
	{
	  if(j>mid||B[j]>A[k])
	    {
	      A[i]=A[k];k++;
	    }
	  else
	    {
	      A[i]=B[j];j++;
	    }
	  i++;
	}

    }

}

void merge_sort(int *A, int s, int e)
{
  int mid, *B=(int*)malloc((e-s+1)*sizeof(int));
  if(s<e)
    {
      mid=(s+(e-s)/2);
      merge_sort(A,s,mid);
      merge_sort(A,mid+1,e);
      merge(A,B,s,e);
    }
}
int inversion_merge(int *A, int *B, int s, int e)
{
  int mid, i,j,k,count=0;
  if(s<e)
    {
      mid=s+(e-s)/2;
      for(i=s;i<=mid;i++) B[i]=A[i];
      for(i=s,j=s,k=mid+1;j<=mid||k<=e;)
	{
	  if(j>mid||B[j]>A[k])
	    { 
	      if(k<=e){count+=(mid-j+1);}
	      A[i]=A[k];k++;
	      
	    }
	  else
	    {
	      A[i]=B[j];j++;
	    }
	  i++;
	}

    }
  return count;
}

int no_of_inversions(int *A, int s, int e)
{
  
  int l,r,m,mid, *B=(int*)malloc((e-s+1)*sizeof(int));
  if(s<e)
    {
      mid=(s+(e-s)/2);
      l=no_of_inversions(A,s,mid); 
      r=no_of_inversions(A,mid+1,e);      
      m=inversion_merge(A,B,s,e); 
      return l+r+m;
    }
  else return 0;
}
int gcd(int a, int b)
{
  int t;
  if(!a) return b;
  if(!b) return a;
  if(b>a) {t=a;a=b;b=t;}
  return gcd(b,a%b);
}
void left_rotate(int *A, int n, int k)
{
  int i,j,d,temp;
  d=gcd(n,k);
  for(i=0;i<k;i++)
    {
      j=i%d;
      temp=A[j];
      while(j+d<n)
	{
	  A[j]=A[j+d];
	  j=j+d;
	}
      A[j]=temp;
    }
}

/*********************************************/
int main()
{
  int A[]={1,2,3,4,5,6,7,8,9,10};//{7,6,9,2,4,-1};
  int B[5]={0};
  int n=sizeof(A)/sizeof(A[0]);
  print_array(A,n);

  //left_rotate(A,n,8);
  //cout<<gcd(4,10)<<endl;
  //cout<<no_of_inversions(A,0,n-1)<<endl;
  //cout<<inversion_merge(A,B,0,n-1)<<endl;
  //print_array(A,n);
  //cout <<count_lesserTripletSum(A,n,12)<<endl;
  return 0;

}
