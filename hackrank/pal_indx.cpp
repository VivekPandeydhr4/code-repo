#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void print_int(int )
{

}
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
  int tcase, num, first, second, result, i;
  cin >> tcase;
  int *arr = new int[tcase];
  int *ar1 = new int[tcase];
  bool *ans = new bool[tcase];
  for (i=0; i<tcase; i++)
    {
      cin >> num;
      arr[i] = num;
      ar1[i] = i;
    }
  isrton_sort(arr, ar1, tcase);
  first = 0;
  second = 1;
  result = 1;
    
  for (i=0; i<tcase; i++)
    {
      if (arr[ar1[i]])
        {
	  while(result < arr[ar1[i]])
            {
	      result = first + second;
	      first = second;
	      second = result;
            }
	  if(result == arr[ar1[i]])
	    ans[ar1[i]] = true;
	  else
	    ans[ar1[i]] = false;
        }
      else
	ans[ar1[i]] = true;
    }
  for (i=0; i<tcase; i++)
    {
      if (ans[i] == true) cout << "IsFibo" << endl;
      else cout << "IsNotFibo" << endl;
    }
  return 0;
}

