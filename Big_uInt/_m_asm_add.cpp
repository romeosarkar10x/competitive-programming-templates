#include <iostream>
#include "_global_def.hpp"

// (lhs >= rhs)
static void _m_asm_add(u_ll* lhs, u_ll* rhs, u_ll size)
{
  asm(
    "movq %0, %%r8\n\t"
    "movq %1, %%r9\n\t"
    "mov  %2, %%rcx\n\t"
    "mov  $1, %%al\n" // carry: al

    "LOOP:\n\t"
    "cmpb $1, %%al\n\t" // restore carry
    "movq (%%r9), %%rdx\n\t"
    "adcq %%rdx, (%%r8)\n\t" // add to lhs
    "setae  %%al\n\t" // set carry
    
    "addq $8, %%r8\n\t"
    "addq $8, %%r9\n\t"
    "dec  %%rcx\n\t"
    "jnz  LOOP\n"
    
    :
    : "g"(lhs), "g"(rhs), "g"(size)
    : "%rax", "rcx", "%rdx", "%r8", "%r9"
  );
}

/*
int main()
{
  u_ll a[] = { 3, 0, 0, 1, 3, 1, 0 }, b[] = { 2, 0, 0, ULONG_LONG_MAX, ULONG_LONG_MAX, 12, 0 };
  u_short size__b = sizeof(b) / sizeof(u_ll);

  _m_asm_add(a, b, size__b);
  
  for(int i = 0; i < size__b; i++) { std::cout << a[i] << " "; }
  std::cout << std::endl;

  // Output: 5 0 0 0 3 14 0

  return 0;
}
*/