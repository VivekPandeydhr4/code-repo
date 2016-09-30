#include <cstdio>
#include <iostream>
#include <cstdlib>
#define ROW 6
#define COL 6
#define N 6
using namespace std;
/******************************/

void print_matrix(int M[][N],int m, int n)
{
  int i,j;
  for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
	{
	  if(M[i][j]/10==0) cout <<" ";
	  cout << M[i][j]<<"  ";
	}
      cout <<"\n";
    }
}
int common_element(int M[][COL])
{
  int i,j,max_row,A[ROW]={0};  
  max_row=0;
  for(i=0;i<ROW;i++)
    if(M[max_row][0]<M[i][0]) max_row=i;
  for(i=0;i<ROW;i++)
    {
      while(M[i][A[i]] < M[max_row][A[max_row]])
	{
	  A[i]++;
	  if(A[i]==COL) return -1;
	}
      if(M[i][A[i]]>M[max_row][A[max_row]]) {max_row=i;i=-1;}
    }
  return M[max_row][A[max_row]];
}

void Rotate_90_degree(int M[][N])
{
  int rowStart,rowEnd,colStart,colEnd,t1,t2,t3,t4,i;
  rowStart=colStart=0;
  rowEnd=colEnd=N-1;
  
  while(rowStart<rowEnd)
    {
      for(i=0;i<rowEnd-rowStart;i++)
	{
	  t1=M[rowStart][colStart+i]; t2=M[rowStart+i][colEnd];
	  t3=M[rowEnd][colEnd-i];     t4=M[rowEnd-i][colStart];
	  
	  M[rowStart+i][colEnd]=t1; M[rowEnd][colEnd-i]=t2;
	  M[rowEnd-i][colStart]=t3; M[rowStart][colStart+i]=t4;
	}
      rowStart++;rowEnd--;colStart++;colEnd--;
    }
}

void spiral_printing(int M[][COL])
{
  int rowStart,rowEnd,colStart,colEnd,i,j;
  rowStart=colStart=0;
  rowEnd=ROW-1;colEnd=COL-1;
  while(rowStart<rowEnd && colStart<colEnd)
    {
      for(j=colStart;j<colEnd;j++) cout<<M[rowStart][j]<<",";
      for(i=rowStart;i<rowEnd;i++) cout<<M[i][colEnd]<<",";
      for(j=colEnd;j>colStart;j--) cout<<M[rowEnd][j]<<",";
      for(i=rowEnd;i>rowStart;i--) cout<<M[i][colStart]<<",";
      rowStart++;rowEnd--;colStart++;colEnd--;
    }
  if(colStart==colEnd) for(i=rowStart;i<=rowEnd;i++) cout << M[i][colStart] << ",";
  else if(rowStart==rowEnd) for(j=colStart;i<=colEnd;j++) cout << M[rowStart][j] << ",";
  cout<<endl;
}
/******************************/
int main()
{
  int M[ROW][COL]={{1,5,7,10,15,20},{2,5,9,16,18,20},{1,3,4,5,9,20},{4,5,9,12,16,20},{0,1,2,3,4,5}};
  int T[N][N]={{1,2,3,4,5,6},{7,8,9,10,11,12},{13,14,15,16,17,18},{19,20,21,22,23,24},{25,26,27,28,29,30},{31,32,33,34,35,36}};
  print_matrix(T,N,N);
  //Rotate_90_degree(T);
  cout <<endl<<endl;
  spiral_printing(T);
  //print_matrix(T,N,N);
  //cout <<common_element(M)<<endl;

  return 0;
}
