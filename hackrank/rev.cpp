#include <iostream>
#include <string>
using namespace std;

string rev(string str)
{
  int i=0;
  int len = str.length();
  char tmp;
  
  while(len-i-1 > i)
    {
      tmp = str[i];
      str[i] = str[len-i-1];
      str[len-i-1] = tmp;
      i++;
    }
  return str;
}
int main()
{
  string str;
  int len;
  cout << "Enter a string" << endl;
  cin >> str;
  len = str.length();
  cout << "Given string is \n" << str << endl;
  str = rev(str[len/2]);
  cout << str << endl;
  return 0;
}
