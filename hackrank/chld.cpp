#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#define TOTAL_CHAR 26
#define min(a, b) (a>=b)?b:a

using namespace std;
int minm(int a, int b)
{
  if(a>=b) return b;
  else return a;
}
int child_len(string str1, string str2)
{
  int arr1[TOTAL_CHAR] = {0};
  int arr2[TOTAL_CHAR] = {0};
  int len1 = str1.length();
  int len2 = str2.length();
  int count=0, tmp=0;

  for (int i=0, tmp=0; i<len1; i++)
    {
      tmp = str1[i] - 'A';
      arr1[tmp]++;

      tmp = str2[i] - 'A';
      arr2[tmp]++;
      
    }
  /*
  for (int i=0, tmp=0; i<len2; i++)
    {
      tmp = str2[i] - 'A';
      arr2[tmp]++;
    }
    
  for(int i=0; i<TOTAL_CHAR; i++)
    {
      count = count + minm(arr1[i], arr2[i]);
    }
  */
  return count;
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
  string str1, str2;
  int len=0;
  getline(cin, str1);
  getline(cin, str2);
  len = child_len(str1, str2);
  cout << len << endl;
  return 0;
}
