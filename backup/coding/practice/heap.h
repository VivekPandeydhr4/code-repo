#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int>& build_heap(int *A, int n)
{
  int i;
  vector<int> *v=new vector<int>()
;
  for(i=0;i<n-1;i++) v->push_back(A[i]);
  make_heap(v->begin(),v->end());
  return *v;
}
void insert_heap(vector<int>& v,int x)
{
  v.push_back(x);
  push_heap(v.begin(),v.end());
  cout<<"inserted: " << v.front()<<endl;
}
int extract_max(vector<int>& v)
{
  int x;
  x=v.front();
  pop_heap(v.begin(),v.end());
  v.pop_back();
  return x;
}



