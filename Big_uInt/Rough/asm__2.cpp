#include <iostream>

int sum_14(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n)
{
  int result;

  asm(
    "addl %1, %0\n\t"
    "addl %2, %0\n\t"
    "addl %3, %0\n\t"
    "addl %4, %0\n\t"
    "addl %5, %0\n\t"
    "addl %6, %0\n\t"
    "addl %7, %0\n\t"
    "addl %8, %0\n\t"
    "addl %9, %0\n\t"
    "addl %10, %0\n\t"
    "addl %11, %0\n\t"
    "addl %12, %0\n\t"
    "addl %13, %0\n\t"
    "addl %14, %0\n\t"
    : "=g" (result)              // Output in a register
    : "g" (a), "g" (b), "g" (c), "g" (d), "g" (e), "g" (f), "g" (g), "g" (h), "g" (i), "g" (j), "g" (k), "g" (l), "g" (m), "g" (n), "0" (0) // Inputs
    :                             // No clobbered registers
  );
  return result;
}

int main()
{
  std::cout << sum_14(2, 4, 8, 23, 34, 88, 994, 234, 43, 43, 4, 34, 123, 9990) << "\n";
  return 0;
}
