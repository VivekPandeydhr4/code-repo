#include <iostream>
#include <vector>
#include "heap.h"

using namespace std;

int main()
{
  int A[]={2,1},i;
  vector<int> v;
  v=build_heap(A,2);
  for(i=0;i<2;i++)
    cout<<extract_max(v)<<",";
  cout <<endl;
  return 0;
}
