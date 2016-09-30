#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#define CHAPTERS 4
using namespace std;

vector<pair<int,int> > G[CHAPTERS+1];
int color[CHAPTERS+1];
/***************************************/
void DFS(int s, int weight)
{
  cout<< s<<","<<weight; color[s]=1;
  if(s==CHAPTERS) cout<<endl;
  for(vector<pair< int, int> >:: iterator it=G[s].begin();it!=G[s].end();it++)
    {
      if(!color[it->first]){DFS(it->first,weight+it->second);}
    }
}

void BFS(){}
void BFS_shortest_path_for_unweighted(){}
void DFS(){}
void Topological_sort(){}
void Shortest_Path_For_DAG(){}
void Prims_MST(){}
void Kruskals_MST(){}
void Bellman_Ford_Shortest_Path(){}
void Dijkstra_shortest_path(){}
void Flloyd_Warshal_All_Pairs_Shortest_Path(){}
void Ford_Fulkerson_Network_Flow(){}
/***************************************/
int main()
{
  int n,m,i,u,v,w;
  pair<int, int> p;
  cin >> n>>m;
  for(i=0;i<m;i++)
    {
      cin >>u>>v>>w;
      p.first=v;p.second=w;
      G[u].push_back(p);
    }
  for(i=1;i<=n;i++)
    {
        for(vector<pair< int, int> >:: iterator it=G[i].begin();it!=G[i].end();it++)
	  cout <<"("<<i<<","<<it->first<<","<<it->second<<"), ";
	cout <<endl;
    }  
  return 0;
}
