#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;
/*********************************************/
void print_array(int *A, int n)
{
  for(int i=0;i<n;i++) cout<<A[i]<<',';
  cout<<endl;
}
/*********************************************/

int kadane_algo_4_max_sum_contiguous_subarray(int *A, int n)
{
  int i, j, sum;
  int max_i=-1,max_j=-1,max_sum=INT_MIN;
  for(i=j=sum=0;j<n;)
    {
      sum+=A[j];cout<<i<<':'<<j<<'='<<sum<<',';
      if(sum<=0){sum=0;i=j+1;}
      else if(sum>max_sum){max_sum=sum;max_i=i;max_j=j;}
      j++;
    }
  cout<<endl<<max_i<<':'<<max_j<<endl;
  return max_sum;
}
/*int Longest_common_subsequence(char *S1, char *s2)
{
  int l1,l2;
  l1=strlen(S1);l2=strlen(S2);
  pair<int,pair<int,int> > **M;
  M= new pair<int, pair<int, int> > *[l1+1];
  for(i=0;i<=l1;i++)
    M[i]= new pair<int,pair<int, int> > [l2+1];

  for(i=0;i<=l1;i++)
    {
      for(j=0;j<=l2;j++)
	{
	  if(i==0 || j==0) M[i][j].first=0; M[i][j].second.first=-1;M[i][j].second.second=-1;
	  else if(S1[i-1]==S2[j-1]) M[i][j].first = M[i-1][j-1].first; M[i][j].second.first=i-1; M[i][j].second.second=j-1;
	  else 
	    {



	    }
	}
    }
    }*/

/*********************************************/
int wildcard_DP(char *P,char *T)
{
  int m, n, i, j,**WC;
  m=strlen(P),n=strlen(T);
  WC= new int*[m+1];
  for(i=0;i<=m;i++) WC[i]=new int[n+1];
  for(i=m;i>=0;i--)
    {
      for(j=n;j>=0;j--)
	{
	  if(!P[i] && !T[j]) WC[i][j]=1;
	  else if(!P[i] && T[j]) WC[i][j]=0;
	  else if(P[i]=='?')
	    {
	      if(!T[j]) WC[i][j]=0;
	      else WC[i][j]= WC[i+1][j+1];
	    }
	  else if(P[i]=='*')
	    {
	      WC[i][j]=WC[i+1][j]||WC[i][j+1]||WC[i+1][j+1];
	    }
	  else WC[i][j]=(P[i]==P[j])&&WC[i+1][j+1];

	}
    }
  return WC[0][0];
}
/*********************************************/
int is_C_interleaving_of_A_n_B(char *A, char *B, char *C)
{
  int i,j,l,m,n,**M;
  m=strlen(A);n=strlen(B);l=strlen(C);
  M=new int*[m+1];
  for(i=0;i<=m;i++) M[i]=new int[n+1];
  M[0][0]=1;
  for(j=1;j<=n;j++) M[0][j] = (B[j-1]==C[j-1] && M[0][j-1]);
  for(i=1;i<=m;i++) M[i][0] = (A[i-1]==C[i-1] && M[i-1][0]);
  for(i=1;i<=m;i++)
    {
      for(j=1;j<=n;j++)
	M[i][j]= (A[i-1]==C[i+j-1] && M[i-1][j]) || (B[j-1]==C[i+j-1]&&M[i][j-1]);
    }

  return M[m][n];
}
/*********************************************/
int main()
{

  int i,n,Arr[]={-2,-3,4,-1,-2,1,5,-3};
  char A[]="AAB",B[]="AAC",C[]="AAACAB";
  n=sizeof(A)/sizeof(A[0]);
  cout<<is_C_interleaving_of_A_n_B(A,B,C);
  //char P[]="a*bc?d", T[]="adhdjebcd";
  //print_array(A,n);
  //cout<<P<<endl<<T<<endl;
  //cout<<wildcard_DP(P,T);
  //cout<<kadane_algo_4_max_sum_contiguous_subarray(A,n);
  cout<< endl;
  return 0;
}
