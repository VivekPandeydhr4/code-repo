#include <iostream>
#include <climits>
#include <cstring>
#include <cstdlib>
#define ROW 6
#define COL 5
#define minimum(a,b) (a)<=(b)?(a):(b)
using namespace std;
/******************************************/

int Min_no_of_jumps_to_reach_end(int A[], int n)
{
  int i,j,*B,*C;
  B=(int*)malloc(n*sizeof(int));
  C=(int*)malloc(n*sizeof(int));

  for(i=0;i<n-1;i++) B[i]=INT_MAX;
  B[n-1]=0;C[n-1]=n;

  for(i=n-2;i>=0;i--)
    {
      for(j=i+1;j<=i+A[i] && j<n;j++)
	{
	  if(B[i]>B[j]+1) {B[i]=B[j]+1;C[i]=j;}
	}
    }
  cout << A[0]<<",";
    for(i=C[0];i<n;)
      {
	cout << A[i]<<",";
	i=C[i];
      }
    cout << endl;
  return B[0];
}

int keypad_problem(int n)
{
  int *B,i,j,sum,*A,*t;
  A=(int*)malloc(10*sizeof(int));
  B=(int*)malloc(10*sizeof(int));
  if(n<=0) return 0;
  for(i=0;i<10;i++) A[i]=1;
  for(j=2;j<=n;j++)
    {
      {t=A;A=B;B=t;}
      for(i=0;i<10;i++)
	{
	  A[i]=B[i];
	  if(i==0){A[i]+=B[8]; continue;}
	  if(i==8) A[i]+=B[0];
	  if(i!=3 && i!=6 && i!=9) A[i]+=B[i+1];
	  if(i!=1 && i!=4 && i!=7) A[i]+=B[i-1];
	  if(i!=1 && i!=2 && i!=3) A[i]+=B[i-3];
	  if(i!=7 && i!=8 && i!=9) A[i]+=B[i+3];
	}
    }
  for(sum=0,i=0;i<10;i++) sum+=A[i];
  return sum;
}

int largest_square_submatrix_of_all_1s(int M[][COL])
{// input is a binary matrix. not necessarily square.
  int **SSM,i,j,max,max_i,max_j;
  SSM=(int**)malloc(ROW*sizeof(int*));
  for(i=0;i<ROW;i++) SSM[i]=(int*)malloc(COL*sizeof(int));

  max=0;max_i=0;max_j=0;
  for(i=ROW-1;i>=0;i--)
    {
      for(j=COL-1;j>=0;j--)
	{
	  if(i==ROW-1||j==COL-1) {SSM[i][j]=M[i][j];}
	  else if(M[i][j]==0) SSM[i][j]=0;
	  else 
	    {
	      SSM[i][j]=minimum(SSM[i+1][j],SSM[i][j+1]);
	      SSM[i][j]=minimum(SSM[i][j],SSM[i+1][j+1]);
	      SSM[i][j]++;	  
	    }
	  if(SSM[i][j]>max) {max=SSM[i][j];max_i=i;max_j=j;}
	}
    }
  cout << max_i <<","<<max_j<<endl;;
  return max;	
}

int min_no_of_jumps_to_reach_end(int *A, int n)
{
  int *R=NULL,i,j,*B=NULL;
  R=(int*)malloc(n*sizeof(int));
  B=(int*)malloc(n*sizeof(int));
  R[n-1]=0;
  B[n-1]=-1;
  for(i=n-2;i>=0;i--)
    {
      R[i]=INT_MAX;
      for(j=i+1;j<n && j<=i+A[i];j++)
	{
	  if(R[i]>1+R[j]) {R[i]=1+R[j]; B[i]=j;}
	}
    }
  //Printing steps  
  for(i=0;i!=-1;)
    {
      cout<< A[i]<<"->";
      i=B[i];
    }
  cout <<endl;
  return R[0];
}

int longest_palindromic_subsequence(char *s)
{
  int l,i,j,d,**T=NULL;
  l=strlen(s);
  T=(int**)malloc(l*sizeof(int*));
  for(i=0;i<l;i++)
    {
      T[i]=(int*)malloc(l*sizeof(int));
      memset(T[i],0,l*sizeof(int));
    }
  for(d=1;d<=l;d++)
    {
      for(i=0;i<=l-d;i++)
	{
	  j=i+d-1;
	  if(d==1) T[i][j]=1;
	  else if(s[i]==s[j]) T[i][j]=T[i+1][j-1]+2;
	  else T[i][j]=(T[i+1][j]>=T[i][j-1]) ? T[i+1][j]:T[i][j-1];
	}
    }
  return T[0][l-1];
}

bool isPalindrome(char *s, int i, int j)
{
  for(;i<j;)
    {
      if(s[i]!=s[j]) return false;
      i++;j--;
    }
  return true;
}

int Min_palindrome_partitioning(char *s)
{
  int *PPL,l,i,j;
  l=strlen(s);
  PPL=(int*)malloc((l+1)*sizeof(char));  
  PPL[l]=0;
  
  for(i=l-1;i>=0;i--)
    {
      PPL[i]=INT_MAX;
      for(j=i;j<l;j++)
	{
	  if(isPalindrome(s,i,j))
	    {
	      if(PPL[i]>PPL[j+1]+1) PPL[i]=PPL[j+1]+1;
	    }
	}
    }
  cout <<s<<endl;
  for(i=0;i<=l;i++)
    cout <<PPL[i];
  cout <<endl;
  return PPL[0]-1;
}
/* WORKING BUT NEED TO DEFINE GETWORD AND ISVALID FUNCTION.
bool Word_break_problem(char *s,char **D,int n)
{
  char *w=NULL;
  bool *A=NULL;
  int l;
  l=strlen(s);
  //w=(char*)malloc((l+1)*sizeof(char));
  A=(bool*)malloc((l+1)*sizeof(bool));
  A[l]=true;

  for(i=l-1;i>=0;i--)
    {
      A[i]=false;
      for(j=i;j<l;j++)
	{	  
	  w=getWord(s,i,j);
	  if(isValid(D,n,w)&&A[j+1]) 
	    {
	      A[i]=true;break;
	    }
	}
    }
    return A[0];
}
*/

int  No_of_Decodings(int *A, int n)
{//expects only valid inputs
  int *D=NULL,i=0;
  D=new int[n+1];
  D[n]=1;
  D[n-1]=!(!A[n-1]);
  for(i=n-2;i>=0;i--)
    {
      if(A[i]==0) D[i]=0;
      else
	{
	  D[i]=D[i+1];
	  if(A[i]<2 ||A[i]==2 && A[i+1]<=6) D[i]+=D[i+2];
	}
    }
  return D[0];


}
/******************************************/
int main()
{
  char s[]="ababbbabbababa";
  int i,A[]={1,2,3,4};
  int M[ROW][COL]={{0,1,1,0,1},{1,1,0,1,0},{0,1,1,1,0},{1,1,1,1,0},{1,1,1,1,1},{0,0,0,0,0}};
  int size=sizeof(A)/sizeof(*A);
  cout<< No_of_Decodings(A,4)<<endl;
  //cout << Min_palindrome_partitioning(s)<<endl;
  //cout<<longest_palindromic_subsequence(s)<<endl;
  //cout << largest_square_submatrix_of_all_1s(M)<<endl;
  //cout << min_no_of_jumps_to_reach_end(A,size)<<endl;
  // cout << Min_no_of_jumps_to_reach_end(A,size)<< endl;
  // for(i=1;i<6;i++)
  //   cout << "n = "<< i <<"=> " << keypad_problem(i) <<"\n";

  return 0;
}
