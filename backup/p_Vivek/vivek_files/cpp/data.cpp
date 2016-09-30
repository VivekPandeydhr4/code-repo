#include <iostream>

using namespace std;

class x
{
  char c;
};

class y : virtual public x
{

};

class z : virtual public x
{
  
};

class A : public y, public z
{

};

int main()
{
  x a, b, c, d;

  cout << "Size of X = " << sizeof(x) << endl;
  cout << "Size of Y = " << sizeof(y) << endl;
  cout << "Size of Z = " << sizeof(z) << endl;
  cout << "Size of A = " << sizeof(A) << endl;

  cout << "a at = " << &a << endl; 
  cout << "b at = " << &b << endl; 
  cout << "c at = " << &c << endl; 
  cout << "d at = " << &d << endl; 

  if (&a == &b) cout << "Yes" << endl;
  else cout << "No" << endl;
  
  return 0;
}
