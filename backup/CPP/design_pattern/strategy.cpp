#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

/******************************************************************
//                      Normal scenario

class D1
{
public:
  void f(){cout<<1<<' ';}
  void g(){cout<<2<<' ';}
  void h(){cout<<4<<' ';}
  void i(){cout<<7<<' ';}
};

class D2
{
public:
  void f(){cout<<1<<' ';}
  void g(){cout<<2<<' ';}
  void h(){cout<<4<<' ';}
  void i(){cout<<8<<' ';}
};

class D3
{
public:
  void f(){cout<<1<<' ';}
  void g(){cout<<3<<' ';}
  void h(){cout<<5<<' ';}
  void i(){cout<<9<<' ';}
};

class D4
{
public:
  void f(){cout<<1<<' ';}
  void g(){cout<<3<<' ';}
  void h(){cout<<6<<' ';}
  void i(){cout<<10<<' ';}
};
class D5
{
public:
  void f(){cout<<1<<' ';}
  void g(){cout<<3<<' ';}
  void h(){cout<<6<<' ';}
  void i(){cout<<11<<' ';}
};

int main()
{
  D1 d1;D2 d2;D3 d3;D4 d4;D5 d5;
  cout<<"\nD1 behaviour..."<<endl;
  d1.f();d1.g();d1.h();d1.i();
  cout<<"\nD2 behaviour..."<<endl;
  d2.f();d2.g();d2.h();d2.i();
  cout<<"\nD3 behaviour..."<<endl;
  d3.f();d3.g();d3.h();d3.i();
  cout<<"\nD4 behaviour..."<<endl;
  d4.f();d4.g();d4.h();d4.i();
  cout<<"\nD5 behaviour..."<<endl;
  d5.f();d5.g();d5.h();d5.i();


  cout<<endl;return 0;
}

******************************************************************/
//                 STRATEGY PATTERN Design

class GC
{//INTERFACE
public:
  virtual void g()=0;
};
class G_2:public GC
{
public:
  void g(){cout<<2<<' ';}
};
class G_3:public GC
{
public:
  void g(){cout<<3<<' ';}
};

class HC
{//INTERFACE
public:
  virtual void h()=0;
};

class H_4:public HC
{
public:
  void h(){cout<<4<<' ';}
};
class H_5:public HC
{
public:
  void h(){cout<<5<<' ';}
};
class H_6:public HC
{
public:
  void h(){cout<<6<<' ';}
};
////////////////////////

class B
{
public:
  GC *G;
  HC *H;
  void f(){cout<<1<<' ';}
  void g(){G->g();}
  void h(){H->h();}
  virtual void i()=0;
  void G_setter(GC* p){G=p;}
  void H_setter(HC *p){H=p;}
  
};
class D1:public B
{
public:
  void i(){cout<<7<<' ';}  
};
class D2:public B
{
public:
  void i(){cout<<8<<' ';}  
};
class D3:public B
{
public:
  void i(){cout<<9<<' ';}  
};
class D4:public B
{
public:
  void i(){cout<<10<<' ';}  
};
class D5:public B
{
public:
  void i(){cout<<11<<' ';}  
};


int main()
{
  D1 d1;D2 d2;D3 d3;D4 d4;D5 d5;
  G_2 g2;G_3 g3;H_4 h4;H_5 h5;H_6 h6;

  d1.G_setter(&g2);d1.H_setter(&h4);
  cout<<"\nD1 behaviour..."<<endl;
  d1.f();d1.g();d1.h();d1.i();

  d2.G_setter(&g2);d2.H_setter(&h4);
  cout<<"\nD2 behaviour..."<<endl;
  d2.f();d2.g();d2.h();d2.i();

  d3.G_setter(&g3);d3.H_setter(&h5);
  cout<<"\nD3 behaviour..."<<endl;
  d3.f();d3.g();d3.h();d3.i();

  d4.G_setter(&g3);d4.H_setter(&h6);
  cout<<"\nD4 behaviour..."<<endl;
  d4.f();d4.g();d4.h();d4.i();
  
  d5.G_setter(&g3);d5.H_setter(&h6);
  cout<<"\nD5 behaviour..."<<endl;
  d5.f();d5.g();d5.h();d5.i();

  cout<<endl;return 0;
}
/******************************************************************/
