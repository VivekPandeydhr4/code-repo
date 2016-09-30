#include <cstdio>
#include <iostream>
#include <algorithm>
#define ROW 3
#define COL 4
#define Parent(i) ((i-1)/2)
#define Left(i) (2*i+1)
#define Right(i) (2*i+2)
using namespace std;
int M[ROW][COL]={1,4,25,50,2,5,8,71,3,6,9,12};
/********************************************************/
void print_matrix()
{
  int i,j;
  for(i=0;i<ROW;i++)
    {
      for(j=0;j<COL;j++)
	{
	  cout <<M[i][j]<<' ';
	}
      cout<<endl;
    }

}
void min_heapify(pair<int, int> H[], int n, int i)
{
  int smallest,a,b;
  pair<int, int> t;
  smallest=i;
  if(i<n)
    {
      if(Right(smallest)<n)
	{
	  a=M[H[smallest].first][H[smallest].second];
	  b=M[H[Right(smallest)].first][H[Right(smallest)].second];
	  if(a>b) smallest=Right(smallest);
	}
      if(Left(smallest)<n)
	{
	  a=M[H[smallest].first][H[smallest].second];
	  b=M[H[Left(smallest)].first][H[Left(smallest)].second];
	  if(a>b) smallest=Left(smallest);
	}
      if(smallest!=i)
	{
	  t=H[i];H[i]=H[smallest];H[smallest]=t;
	  min_heapify(H,n,smallest);
	}
    }
}

int insert(pair<int, int> H[], int n, pair<int, int> p)
{
  pair<int, int> t;
  int i;
  H[n]=p;
  i=n;
  while(M[H[i].first][H[i].second]<M[H[Parent(i)].first][H[Parent(i)].second])
    {
      t=H[i];H[i]=H[Parent(i)];H[Parent(i)]=t;
      i=Parent(i);
    }
}

pair<int, int> extract_min(pair<int, int> H[], int n)
{
  pair<int , int> p;
  if(n>0)
    {
      p=H[0];
      H[0]=H[n-1];
      min_heapify(H,n,0);
      return p;
    }
}
void Make_heap(pair<int,int> H[], int n)
{
  int i;
  for(i=Parent(n-1);i>0;i--)
    min_heapify(H,n,i);
}
void sorted_merge_rows_of_the_rowwise_sorted_matrix()
{
  int i,k,size;
  pair<int , int> p;
  pair<int, int> H[ROW];
  for(i=0;i<ROW;i++)
    {
      H[i].first=i;H[i].second=0;
    }
  Make_heap(H,ROW);
  size=ROW;
  for(k=0;k<ROW*COL;k++)
    {
      p=extract_min(H,size);
      cout<<M[p.first][p.second]<<' ';
      p.second++;
      if(p.second>=COL) size--;
      else insert(H,size-1,p);
    }
}
/********************************************************/
int main()
{
  print_matrix();
  cout<<endl;
  sorted_merge_rows_of_the_rowwise_sorted_matrix();
  return 0;
}


