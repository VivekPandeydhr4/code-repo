#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int ang_count(string str)
{
  int i=0;
  int len = str.length();
  if (len%2) return -1;
  else
    {
      int cnt=0, j=0, flag=0;
      int m = len/2;
      for (i=0; i<m; i++)
        {
	  if (str[i] != str[m+i])
            {
	      flag = 0;
	      for(j=m; j<len; j++)
                {
		  if(str[i] == str[j])
                    {
		      flag=1;
                    }
                }
	      if(!flag)
                cnt++;
            }
        }
      return cnt;
    }
}
int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int tcase, num;
  string str;
  //cin >> tcase;
  getline(cin, str);
  /*while(tcase--)
    {
      getline(cin, str);
      num = ang_count(str);
      cout << num << endl;
      }*/
  num = ang_count(str);
  cout << num << endl;
  return 0;
}
