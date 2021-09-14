#include <iostream>
#include "vector.hpp"
int main()
{
  Vector<int> arrayInt{};
  arrayInt.push_back(5);
  arrayInt.push_back(-8);
  for (int &i: arrayInt)
  {
    std::cout << "i = " << i << "\n";
  }
  return 0;
}
