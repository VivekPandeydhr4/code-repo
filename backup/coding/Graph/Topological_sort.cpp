#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
#include <cstring>
#define NO_OF_NODES 4
#define ARR(type,n) (type*)malloc(n*sizeof(type));
//#define INIT(base,x,size) memset(base,x,size)
using namespace std;
typedef vector<pair<int,int> > EDGES;


void DFS(EDGES *G, int n, int s, int *D, int *F, int *Color, int *Time, int *Top_Order, int *index)
{
  //cout <<s<<",";
  Color[s]=1;
  D[s]=(*Time)++;
  for(EDGES::iterator it=G[s].begin();it!=G[s].end();it++)
    if(!Color[it->first]) DFS(G,n,it->first,D,F,Color,Time,Top_Order,index);
  F[s]=(*Time);  
  Top_Order[(*index)--]=s;
}
int* topologocal_sort(EDGES *G, int n)
{
  int *D,*F,*Color,Time,*Top_Order,index;;
  Color=(int*)malloc((n+1)*sizeof(int));
  memset(Color,0,(n+1)*sizeof(int));
  D=(int*)malloc((n+1)*sizeof(int));
  F=(int*)malloc((n+1)*sizeof(int));
  Time=0;
  Top_Order=(int*)malloc((n)*sizeof(int));
  index=n-1;
  for(int i=1;i<=n;i++)
    {
      if(!Color[i]) DFS(G,n,i,D,F,Color,&Time,Top_Order,&index);
    }  
  return Top_Order;
}
void DAG_sortest_path(EDGES *G, int n, int s)
{
  int *dist,*parent,*Top_Order,i;

  dist=(int*)malloc((n+1)*sizeof(int));
  parent=(int*)malloc((n+1)*sizeof(int));
  
  for(i=0;i<=n;i++) {dist[i]=INT_MAX;parent[i]=0;}

  dist[s]=0;

  Top_Order=topologocal_sort(G,n);  
  for(i=0;i<n;i++)
    {
      for(EDGES::iterator it=G[Top_Order[i]].begin();it!=G[Top_Order[i]].end();it++)
	{
	  if(dist[it->first]>dist[Top_Order[i]]+it->second)
	    {
	      dist[it->first]=dist[Top_Order[i]]+it->second;
	      parent[it->first]=Top_Order[i];
	    }
	}
    }
  for(i=1;i<=n;i++) cout<<"("<<i<<","<<dist[i]<<"), ";
  cout<<endl;
}

int main()
{
  EDGES *G;
  int i,m,n,u,v,w,s;
  pair<int, int> p;
  cout<< "Enter no. of vertices and edges: ";
  cin >>n >>m;
  G=(EDGES*)malloc((n+1)*sizeof(EDGES));
  for(i=0;i<m;i++){
    cin >>u>>v>>w;
    p.first=v; p.second=w;
    G[u].push_back(p);
  }
  s=1;
  DAG_sortest_path(G,n,1);
  // for(i=1;i<=n;i++)
  //   {
  //     for(EDGES::iterator it=G[i].begin();it!=G[i].end();it++)
  // 	cout << "("<<i<<","<<it->first<<","<<it->second<<")";
  //     cout <<endl;
  //   }
}
