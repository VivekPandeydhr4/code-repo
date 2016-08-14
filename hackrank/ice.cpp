#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void isrton_sort(int arr[], int ar1[], int size)
{
  int i, j, key;

  for (i=1; i<size; i++)
    {
      key = ar1[i];
      j = i-1;

      while((arr[key]<arr[ar1[j]]) &&(j>=0))
        {
          ar1[j+1] = ar1[j];
          j = j-1;
        }
      ar1[j+1] = key;
    }
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int tcase=0;
  cin >> tcase;
  while(tcase--){
    int m=0, n=0, a;
    cin >> m;
    cin >> n;
    int *c = new int [n];
    int *cr = new int [n];
    for(int i=0; i<n; i++)
      {
        cin >> a;
        c[i] = a;
        cr[i] = i;
      }
    isrton_sort(c,cr,n);

    for(int i=0; i<n; i++)
      cout << c[cr[i]] << " ";
    cout << endl;

    for(int i=0, j=n-1; i<j; )
      {
        if((c[cr[i]]+c[cr[j]]) > m) j--;
        else if ((c[cr[i]]+c[cr[j]]) < m) i++;
        else 
	  {
	    if (cr[i] < cr[j])
	      cout << cr[i]+1 << " " << cr[j]+1 << endl;
	    else
	      cout << cr[j]+1 << " " << cr[i]+1 << endl;
            break;
	  }
      }
  }
  return 0;
}
