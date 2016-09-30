#include <iostream>
#include <vector>
#include <cstring>
#include <stack>
#include <queue>

#define NO_OF_NODES 9
using namespace std;
/*******************************************/
int Time;
vector<int> G[NO_OF_NODES+1];
int color[NO_OF_NODES+1];
unsigned int D[NO_OF_NODES+1];
unsigned int F[NO_OF_NODES+1];
int Top_Order[NO_OF_NODES];
int Index;
/*******************************************/
void DFS( int s);
//void DFS(vector<int> G[], int u);
void BFS(vector<int> G[], int s);
void MST(vector<int> G[], int s);
void Topological_Sort();
/*******************************************/
int main()
{
  int n,m,j,i,u,v;
  cin >> n >> m;
  for(i=0;i<m;i++)
    {
      cin>>u>>v;
      G[u].push_back(v);
      //G[v].push_back(u);
    }
  Topological_Sort();
  // DFS(1);
  // cout <<endl;
  // for(i=1;i<=n;i++)
  //   cout<<"("<<D[i]<<","<<F[i]<<")"<<",";
  cout <<endl;
  return 0;
}
void Topological_Sort()
{
  int i=0;
  Index=NO_OF_NODES-1;
  for(i=1;i<=NO_OF_NODES;i++)    
      if(!color[i]) DFS(i);
    
  cout <<endl;  
  for(i=0;i<NO_OF_NODES;i++)
    cout << Top_Order[i]<<",";
  cout <<endl;  
}

void DFS(int s)
{
  D[s]=Time++;  
  cout << s <<" ";  color[s]=1; 
  for(vector<int>::iterator it=G[s].begin();it!=G[s].end();it++)
    if(!color[*it]) DFS(*it);
  F[s]=Time++;
  Top_Order[Index--]=s;
}

void BFS(vector<int> G[], int s)
{
  int temp;
  queue<int> Q;
  vector<int>::iterator it;
  Q.push(s);
  color[s]=1;
  while(!Q.empty())
    {
      temp=Q.front();
      Q.pop();
      for(it=G[temp].begin();it!=G[temp].end();it++)
	{
	  if(!color[*it]) {Q.push(*it);color[*it]=1;}
	}
      cout << temp <<" ";
    }
}
/*
void MST(vector<int> G[], int s, int n)
{
  memset(D,-1,sizeof(D));
  memset(F,0,sizeof(F));
  D[s]=0;
  count=n;
  while(count)
    {
      temp=min(D,n);//return index of the min in D[1...n];
      D[temp]=0;
      vector<int>::iterator it=G[temp].begin();
      while(it!=G[temp].end())
	{
	  if(D[*it])
	}
    }

}
*/

