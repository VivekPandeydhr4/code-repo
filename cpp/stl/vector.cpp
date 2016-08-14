#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
  vector<string> names = get_names(argv);
  vector<string>:: iterator i;

  for(i=names.begin(); i != names.end(); i++)
    cout << *i << "";

  return 0;
}
