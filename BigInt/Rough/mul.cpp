#include <iostream>

int main()
{
  unsigned int a = 1000000, b = 2000000;
  unsigned int c = 9, d = 2;

  asm(
    "movl %2, %%eax\n\t"
    // "movl %3, %%edx\n\t"
    "mull %3\n\t"
    "movl %%eax, %0\n\t"
    "movl %%edx, %1\n\t"
    : "=g"(c), "=g"(d)
    : "g"(a), "g"(b)
    : "%eax", "%edx"
  );

  std::cout << a << " " << b << " " << c << " " << d << "\n";
  return 0;
}