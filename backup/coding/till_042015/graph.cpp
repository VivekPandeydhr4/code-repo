#include <iostream>
#include <vector>
using namespace std;
int Time;
void dfs_visit(vector<int> *G, int u, int *used, int *D, int *F);
void dfs(vector<int> G[], int n);
void DFS(vector<int> *G, int u,int *used);
int main()
{
  int n,m,j,i,u,v,used[100]={0};
  cin >> n >> m;
  vector<int> G[n+1];

  for(i=0;i<m;i++)
    {
      cin>>u>>v;
      //      cout <<u<<" "<<v<<endl;
      G[u].push_back(v);
      G[v].push_back(u);
    }
  vector<int>::iterator it;
  for(i=1;i<=n;i++)
    {
      cout << "node"<<i<<": ";
      it=G[i].begin();
      while(it!=G[i].end())
	{
	  cout << *it <<" ";
	  it++;
	}
      cout <<endl;
    }
  
  DFS(G,1,used);
  cout <<endl;
  return 0;
}
void DFS(vector<int> *G, int u,int *used)
{
  cout << u <<" ";
  used[u]=1;
  vector<int>::iterator it=G[u].begin();
  while(it!=G[u].end())
    {
      if(!used[*it]) DFS(G,*it,used);
      it++;
    }
}




void dfs_visit(vector<int> *G, int u, int *used, int *D, int *F)
{
  cout << u <<" ";
  used[u]=1;Time++;D[u]=Time;
  vector<int>::iterator it=G[u].begin();
  while(it!=G[u].end())
    {
      if(!used[*it]) dfs_visit(G,*it,used,D,F);
      it++;
    }
  Time++;F[u]=Time;
}

void dfs(vector<int> G[], int n)
{
  int u,i,used[100]={0},F[100],D[100];
  for(u=1;u<=n;u++)
    {
      if(!used[u])
	dfs_visit(G,u,used,D,F);
    }
  for(i=1;i<=n;i++)
    {
      cout<<D[i]<<","<<F[i]<<"  ";
    }
  cout <<endl;

}
