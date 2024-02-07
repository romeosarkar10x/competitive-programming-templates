#include <iostream>

int main()
{
  unsigned long long l = 2000000000000;

  unsigned int i = *reinterpret_cast<unsigned int*>(&l);
  unsigned int i2 = *(reinterpret_cast<unsigned int*>(&l) + 1);

  std::cout << i << " " << i2 << "\n";

  return 0;
}