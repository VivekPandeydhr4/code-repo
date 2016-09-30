#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{

  int T, N,i,j=1;
  vector<long long> A, B;
  vector<long long>::iterator it1,it2;
  long long result,x;
  scanf("%d\n",&T);
  while(j<=T)
    {
      scanf("%d\n",&N);
      A.clear();B.clear();
      for(i=0;i<N;i++) {scanf("%lld",&x); A.push_back(x);}
      for(i=0;i<N;i++) {scanf("%lld",&x); B.push_back(x);}

      sort(A.begin(),A.end());
      sort(B.begin(),B.end());
      for(result=0,it1=A.begin(),it2=B.end(),it2--;it1!=A.end();it1++,it2--)
	{
	  result+=(*it1) * (*it2);
	}
      cout <<"Case #"<<j<<": "<< result <<endl;    
      j++;
    }
  return 0;
}
