#include <iostream>

using namespace std;

template <typename T>
class stack
{
private:
  int size;
  int top;
  T *stkptr;

public:
  stack(int i=10;);
  ~stack()
  {
    delete [] stkprt;
  }

  bool push(T &);
  bool pop (T &);
  bool isempty()
  {
    return top == -1;
  }
  bool isfull()
  {
    return top == size-1;
  }

};

template <typename T>
stack<T> :: stack(int s)
{
  size = (s>o) ? s :10;
  top = -1;
  stkptr = new T[s];
}

template <typename T>
bool stack<T> :: push(T &pushval)
{
  if (!isfull())
    {
      stkptr[top++] = pushval;
      return true;
    }
  return false;
}

template<typename T>
bool stack<> :: pop(T &popval)
{
  if (!isempty())
    {
      popval = stkptr[top--];
      return true;
    }
  return false;
}

int main()
{

  return 0;
}
