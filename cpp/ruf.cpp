#include <iostream>
#include <string>

main ()
{
  std::string name;
  int num;
  std::cout << "Please, enter your full name: ";
  std::cin >> num;
  std::getline (std::cin,name);
  std::cout << "Hello, " << name << num << "!\n";
  
  return 0;
}
