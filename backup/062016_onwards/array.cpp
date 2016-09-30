#include <iostream>
#include <cstdio>
using namespace std;
/*************************************************/
void print_array(int *A, int n)
{
  for(int i=0;i<n;i++)
    cout<<A[i]<<',';
  cout<<endl;
}
/*************************************************/
int smallest_subarray_having_sum_greater_than_k(int *A, int n, int k)
{
  int i, j, sum, ans_i, ans_j, ans_sum;
  i=j=0; sum=A[0];
  ans_i=ans_j=-1;
  while(j<n)
    {
      if(sum<=k)
	{
	  j++;
	  if(j<n) sum+=A[j];
	}
      else
	{
	  i++;
	  if(i<=j) sum-=A[i-1];
	  else {j=i;if(j<n) sum=A[j];}
	}

      if(sum>k)
	{
	  if(ans_i<0 || ans_j-ans_i>j-i)
	    {ans_i=i;ans_j=j;ans_sum=sum;}
	}
    }
  cout<<ans_i<<','<<ans_j<<endl;
  return ans_sum;
}
/*************************************************/
void rearrange_array_based_on_indexes_given_in_index_array(int *A, int *Index, int n)
{
  int i, pi, pv, ni;
  for(i=0;i<n;i++)
    {
      if(i==0 || Index[i]>0)
	{
	  pi=i;pv=A[i];
	  ni=Index[i];
	  while(ni!=i)
	    {
	      A[pi]=A[ni];
	      Index[pi]*=-1;
	      pi=ni;
	      ni=Index[ni];
	    }
	  A[pi]=pv;Index[pi]*=-1;
	  print_array(A,n);
	}
    }
  
}
/*************************************************/
int main()
{
  int i,n,A[]={1,4,45,6,0,19};//{1,11,100,1,0,200,3,2,1,250};
  int Index[]={3,2,0,1,5,4};
  n=sizeof(A)/sizeof(A[0]);

  print_array(A,n);
  print_array(Index,n);
  rearrange_array_based_on_indexes_given_in_index_array(A,Index,n);
  print_array(A,n);







  //cout<<smallest_subarray_having_sum_greater_than_k(A,n,51);

  cout<<endl;
  return 0;
}
