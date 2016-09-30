#include <iostream>

using namespace std;

template <typename T>
void print(T *arr, int count)
{
  for (int i=0; i<count; i++)
    {
      cout << arr[i] << " ";
    }
  cout << endl;
}

int main()
{
  int arrint[] = {1, 2, 3, 4, 5, 6};
  double arrdbl[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
  char arrchr[] = "hello";

  cout << "Int array" << endl;
  print(arrint, sizeof(arrint)/sizeof(arrint[0]));

  cout << "Double array" << endl;
  print(arrdbl, sizeof(arrdbl)/sizeof(arrdbl[0]));

  cout << "Char array" << endl;
  print(arrchr, sizeof(arrchr)/sizeof(arrchr[0]));

  return 0;
}
