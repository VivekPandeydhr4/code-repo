#include <iostream>
#include <algorithm>
#define Parent(i) ((i-1)/2)
using namespace std;
int main()
{
  pair<int, int> p,q[10];
  p.first=2;
  p.second=5;
  cout<<p.first<<':'<<p.second<<endl;
  q[0]=p;
  q[1]=q[0];
  cout<<q[1].first<<':'<<q[1].second;
  cout<<endl;
  return 0;
}
