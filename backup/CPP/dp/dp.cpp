#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>
#define COL 10

using namespace std;
/******************************************************************/


/**
 * LCS: Find a subsequence common in both the strings having length maximum.
 * Input : two strings X and Y of any length. Let m:length(X), n:length(Y).
 * Output: Display the result subsequene and returns the length of it.
 * Time :  O(m*n) 
 * Space : O(m*n)
 */
int LongestCommonSubsequence(char *X, char *Y)
{//UNCOMMENT all the four commented lines to see the algorithm execution 
  int i,j,m=strlen(X),n=strlen(Y);
  int M[m+1][n+1],R[m+1][n+1];
  for(i=0;i<=m;i++)
    {
      for(j=0;j<=n;j++)
	{
	  if(i==0 || j==0)
	    {
	      M[i][j]=0;R[i][j]=0;
	    }
	  else
	    {
	      if(X[i-1]==Y[j-1])
		{
		  M[i][j]=M[i-1][j-1]+1;
		  R[i][j]=2;
		}
	      else
		{
		  M[i][j]=M[i-1][j];
		  R[i][j]=-1;
		  if(M[i][j-1]>M[i][j])
		    {
		      M[i][j]=M[i][j-1];
		      R[i][j]=1;
		    }
		}
	    }
	}
    }
 
  for(i=m;i>=0;i--)
    {
                                                //if(i)cout<<X[i-1]<<"  "; else cout<<"   ";
      for(j=0;j<=n;j++)
	{
	  cout<<M[i][j]<<" ";
	}
      cout<<endl;
    }
                                                //for(j=0;j<=n;j++) if(j)cout<<Y[j-1]<<" "; else cout<<"     ";
  cout<<endl<<endl;
  for(i=m;i>=0;i--)
    {
                                                //if(i)cout<<X[i-1]<<"  "; else cout<<"   ";
      for(j=0;j<=n;j++)
	{
	  cout<<R[i][j]<<" ";
	}
      cout<<endl;
    }
                                                 //for(j=0;j<=n;j++)       if(j)cout<<Y[j-1]<<" "; else cout<<"     "; cout<<endl;

  cout<<"Longest Commmon Subsequence is: ";
  i=m,j=n;
  int chosenOption=R[i][j];
  while(chosenOption)
    {
      switch(chosenOption)
	{
	case 1: j--;break;
	case -1: i--;break;
	case 2:cout<<X[i-1]<<' '; i--;j--;break;
	}
      chosenOption=R[i][j];
    }
  cout<<endl;
  return M[m][n];
}
/******************************************************************/



/**
 * MCM: Matrix Chain Multiplication
 *      Given a sequence of matrices with orders compatible for matrix multiplications.
 *      Find the optimal way to compute multiplication of the chain so the the number of 
 *      element multiplications will be minimum
 * Input : An array Order to specify the order of matrices and a number N. The Order matrix contains
 *         the rows count of each matrices in the sequence and columns count of the last matrix.Due to
 *         satisfying matrix multiplication properties this Order array with N elements can denote a 
 *         chain of N-1 such matrices.
 * Output : returns an integer specifying the minimum no of element multiplications to compute the MCM.
 */
int Matrix_Chain_Multiplication(int *Order, int N)
{
  int n=N-1,i,j,k,l,t;
  int M[n][n],R[n][n];
  for(l=1;l<=n;l++)
    {
      for(i=0;i<=n-l;i++)
	{
	  j=i+l-1;
	  if(l==1)
	    {
	      M[i][j]=0;
	      R[i][j]=0;
	    }
	  else
	    {
	      M[i][j]=INT_MAX;
	      for(k=i;k<j;k++)
		{
		  t=M[i][k]+M[k+1][j]+Order[i]*Order[k+1]*Order[j+1];
		  if(t<M[i][j])
		    {
		      M[i][j]=t;
		      R[i][j]=k;
		    }
		}	      
	    }
	}
    }
  return M[0][n-1];
}
/******************************************************************/
int main()
{
  int A[]={10,20,30};
  int n=sizeof(A)/sizeof(A[0]);
  char X[]="abcde",Y[]="falmcry";


  cout<<"Minimum no of multiplications: "<<Matrix_Chain_Multiplication(A,n);
  //cout<<"Length of LCS: "<<LongestCommonSubsequence(X,Y);

  cout<<endl; return 0;
}
