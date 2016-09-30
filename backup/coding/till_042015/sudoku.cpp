#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int fun(int M[][9], int i, int j)
{
  int R,C,k,r,c,A[10],flag=0;
  memset(A,-1,sizeof(A));
  for(c=0;c<9;c++) A[M[i][c]]=0;
  for(r=0;r<9;r++) A[M[r][j]]=0;
  R=3*(i/3);C=3*(j/3);
  for(r=R;r<R+3;r++)
    {
      for(c=C;c<C+3;c++)
	{
	  A[M[r][c]]=0;
	}
    }  
  flag=0;
  for(r=i;r<9;r++)
    {
      for(c=0;c<9;c++)
	{
	  if(r==i && c==j) continue;
	  if(!M[r][c]){flag=1;break;}
	}
      if(flag) break;
    }

  for(k=1;k<10;k++)
    {
      if(A[k]) 
	{
	  M[i][j]=k;
	  if(!flag) return 1;
	  if(fun(M,r,c)) return 1;	    	  
	}     
    }    
  M[i][j]=0;
  return 0;
}
void sudoku_fill(int M[][9])
{
  int i,j,flag=0;
  for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
	{
	  if(!M[i][j]) {flag=1; break;}	  
	}
      if(flag) break;
    }
  if(flag)fun(M,i,j);  
  for(i=0;i<9;i++){
    for(j=0;j<9;j++)
      {
	cout << M[i][j]<<" ";
      }
    cout <<endl;
  }
}
int main()
{
  int M[9][9]={{3, 0, 6, 5, 0, 8, 4, 0, 0},
	       {5, 2, 0, 0, 0, 0, 0, 0, 0},
	       {0, 8, 7, 0, 0, 0, 0, 3, 1},
	       {0, 0, 3, 0, 1, 0, 0, 8, 0},
	       {9, 0, 0, 8, 6, 3, 0, 0, 5},
	       {0, 5, 0, 0, 9, 0, 6, 0, 0},
	       {1, 3, 0, 0, 0, 0, 2, 5, 0},
	       {0, 0, 0, 0, 0, 0, 0, 7, 4},
	       {0, 0, 5, 2, 0, 6, 3, 0, 0}};
  sudoku_fill(M);
  cout <<endl;
  return 0;
}
