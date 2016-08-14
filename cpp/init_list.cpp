#include <iostream>

using namespace std;

class home
{
  int mem;
  int age;

public:
  /*  home()
  {
    cout << "@@@@ home constructor 111" << endl;
    mem = 10;
    age = 15;
  }
  */
  home(int x, int y) : mem(x), age(y)
  {
    cout << "@@@@ home constructor 222" << endl;
    //mem = x;
    //age = y;
  }

  void show ()
  {
    cout << mem << endl;
    cout << age << endl;
  }
};

class vill : public home
{
  int no_home;

public:
  vill() : home(2,3), no_home(5)
  {
    cout << "@@@@ village constructor 111" << endl;
    //no_home = 25;
  }

};
int main()
{

  //  home hm, hm1(5, 6);
  //hm1.show();
  
  vill v1;
  return 0;
}
