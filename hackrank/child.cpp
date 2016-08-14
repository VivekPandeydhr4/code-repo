#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


// It is NOT mandatory to use the provided template. You can handle the IO section differently.

int main() {
  /* The code required to enter n,k, candies is provided*/

  int N, K, unfairness;
  cin >> N >> K;
  int candies[N];
  for (int i=0; i<N; i++)
    cin >> candies[i];

 for (int i=0; i<N; i++)
   cout << candies[i] << " ";
 cout << endl;
  sort(candies, candies+N);

 for (int i=0; i<N; i++)
   cout << candies[i] << " ";
 cout << endl;
    
  for (int i=0,j=K-1; j<N; i++,j++)
    {
      if(i && (unfairness > (candies[j]-candies[i])))
	unfairness = candies[j]-candies[i];
      else unfairness = candies[j]-candies[i];
      
      cout << "i=" << i<< " j=" <<j<< " Unf="<<unfairness<<endl;
    }
  cout << unfairness << "\n";
  return 0;
}
