#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    
  int pangram[256] = {0};
  int count = 0;
  string str;
  getline(cin, str);
  for (int i=0; i<str.length() && count != 26; i++)
    {
      if (((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
	  && (pangram[str[i]] != 1))
        {
	  //	  cout << str[i] << endl;
	  pangram[str[i]] = 1;
	  count++;
        }
    }
  if (count == 26)
    cout << "pangram" << endl;
  else
    cout << "not pangram" << endl;
  return 0;
}
