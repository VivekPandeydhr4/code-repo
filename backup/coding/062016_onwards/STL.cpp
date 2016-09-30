#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
using namespace std;
struct node
{
  int a,b;
};

class Edge
{
  int u;//head of an edge
  int v;//tail of the edge.
  int w;
  Edge(int tail, int edge_weight):v(tail),w(edge_weight)  {}
};
typedef struct Vertex
{
  int u;//name of the node
  int W;//node weight  
  vector<Edge> nbr;//adjacency_list
  int c;//color
  int d;//discovery_time
  int f;//Finish_time
}Vertex;


class Graph
{
  int n;
  int m;
  vector<Vertex> V(n+1);
public:
  Graph(int vertices_count):n(vertices_count),m(0)  {Vertex v={0,0,new Edge(),0,0,0}; V.push_back(v);}
  void add_edge(int u, int v, int w=0)
  {
    Edge *E=new Edge();
    V[u].push_back(E);
  }
  
}
//##############################################################
  
  





//##############################################################
class comp  
{  
 public:
  int operator()(const struct node& l, const struct node& r)  
  {  
    return l.a > r.a;  
  }  
}; 

int main_pq()
{
  int i,n; 
  struct node A[]={{10,20},{15,6},{100,71},{54,83}};
  n=sizeof(A)/sizeof(A[0]);
  priority_queue<struct node,vector<struct node>, comp > PQ;

  for(i=0;i<n;i++) {PQ.push(A[i]);cout<<A[i].a<<' ';} cout<<endl;
  while(!PQ.empty())
    {
      cout<<PQ.top().b<<' ';
      PQ.pop();
    }

  cout<<endl;return 0;
}
//##############################################################
