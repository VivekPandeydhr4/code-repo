#include <iostream>
#include <string>

using namespace std;

int op_count_palin(string str)
{
  int i=0, length=0, num=0;
  length = str.length();
    
  for(i=0; i<length/2; i++)
    {
      if(str[i] != str[length-i-1])
        {
	  if(str[i] > str[length-i-1])
	    num = num+(str[i] - str[length-i-1]);
	  else
	    num = num+(str[length-i-1] - str[i]);
        }
    }
  return num;
}

int main()
{
  string str = "abc";
  int n = 'z'-'a';//op_count_palin(str);
  cout << "n = " << n << endl;
  return 0;
}
