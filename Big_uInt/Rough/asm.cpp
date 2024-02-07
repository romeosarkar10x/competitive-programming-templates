#include <iostream>

int sum_4(...)
{
  asm(
    "movl %ecx, %eax\n\t"
    "addl %edx, %eax\n\t"
    "addl %r8d, %eax\n\t"
    "addl %r9d, %eax\n\t"
    "popq	%rbp\n\t"
    "ret\n\t"
  );
}

int main()
{
  std::cout << sum_4(2, 4, 8, 23) << "\n";
  return 0;
}