#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int del_char(string str)
{
  char chr;
  int count=0;
  for(int i=0; str[i]!='\0'; i++)
    {
      if(i==0) chr = str[i];
      else
        {
	  if(str[i] == chr) count++;
	  else
            {
	      chr = str[i];
            }
        }
    }
  return count;
}
int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
  int tcase, num;
  cin >> tcase;
  string str;
  getline(cin, str);

  while(tcase--)
    {
      string str;
      getline(cin, str);
      num = del_char(str);
      cout << num << endl;
    } 
  return 0;
}
