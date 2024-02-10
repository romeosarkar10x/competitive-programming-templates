#include <iostream>
#include "Global.hpp"


// size: size - 1
static void _m_asm_shr(u_ll* lhs, u_ll size, u_ll n)
{
  asm(
    "movq %0, %%r8\n\t" // lhs
    "movw %1, %%rdx\n\t" // count
    "movb %2, %%rcx\n\t" // n
    
    "movq $1, %%r9\n\t" // mask
    "shlq %%cl, %%r9\n\t"
    "decq %%r9\n"

    "LOOP:\n\t"
    "movq 8(%%r8), %%rax\n\t"
    "shrq %%cl, (%%r8)\n\t"
    "andq %%r9, %%rax\n\t"
    "rorq %%cl, %%rax\n\t"
    "orq  %%rax, (%%r8)\n\t"
    
    "addq $8, %%r8\n\t"
    "decw %%rdx\n\t"
    "jnz  LOOP\n"
    :
    : "g"(lhs), "g"(size), "g"(n)
    : "%rax", "rcx", "%rdx", "%r8", "%r9"
  );
}


int main()
{
  u_ll a[] = { 8, 1, 8, 12, 0, 64, 256, 0 };
  int size__a = sizeof(a) / sizeof(u_ll);
  _m_asm_shr(a, static_cast<u_short>(size__a - 1), 4);

  for(int i = 0; i < size__a; i++)
  {
    std::cout << a[i] << " ";
  }
  std::cout << "\n";
  
  // Expected Output: 1 2 3 0
  return 0;
}