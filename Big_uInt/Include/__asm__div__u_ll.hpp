#include <iostream>
#include "global.hpp"

// size = lhs_size;
static void __asm__div__u_ll(u_ll* lhs, u_ll rhs, u_ll size, u_ll* quot, u_ll* rem)
{
  asm(
    "movq %[lhs], %%r8\n\t"   //  r8: lhs
    "movq %[rhs], %%r9\n\t"   //  r9: rhs
    "movq %[quot], %%r10\n\t" // r10: quotient 
    "movq $1, %%rdx\n\t"      // rdx: mask
    "movq $0, %%rax\n\t"      // rax: dividend -> remainder
    "movq %[size], %%rcx\n\t" // rcx: size

    "leaq -8(%%r8, %%rcx, 8), %%r8\n\t"     // lhs :: lhs + 8 * (size - 1)
    "leaq -8(%%r10, %%rcx, 8), %%r10\n\t"   // quotient :: quotient + 8 * (size - 1)
    
    "movq (%%r8), %%r11\n\t"    // r11: next
    "movq $0, %%r12\n" // r12: curr quotient

    ".LOOP3:\n\t"
    "rorq %%rdx\n\t"  // rotate mask

    "shlq $1, %%rax\n\t"
    "jnc  .NO_CARRY\n\t"
    "subq %%r9, %%rax\n\t"
    "orq %%rdx, %%r12\n"
    
    ".NO_CARRY:\n\t"
    "test %%rdx, %%r11\n\t"
    "jz   .ZERO\n\t"
    "incq %%rax\n"
    ".ZERO:\n\t"

    "cmpq %%r9, %%rax\n\t"
    "jb .BELOW\n\t"
    "subq %%r9, %%rax\n\t"
    "orq %%rdx, %%r12\n"

    ".BELOW:\n\t"

    "test $1, %%rdx\n\t"
    "jz .LOOP3\n\t"

    "movq %%r12, (%%r10)\n\t"
    "subq $8, %%r10\n\t"
    "movq $0, %%r12\n\t"

    "subq $8, %%r8\n\t"
    "movq (%%r8), %%r11\n\t"

    "decq %%rcx\n\t"
    "jnz .LOOP3\n\t"
    
    
    "movq %[rem], %%r9\n\t"
    "movq %%rax, (%%r9)\n\t"
    
    :
    : [lhs]"m"(lhs), [rhs]"m"(rhs), [quot]"m"(quot), [size]"m"(size), [rem]"m"(rem)
    : "%rax", "rcx", "%rdx", "%r8", "%r9", "%r10", "%r11", "%r12"
  );
}

/*

int main()
{
  u_ll a[] = { 73, 1, 1, 4, 16, 0 }, b = (1ull << 62), size = 6;
  u_ll quot[6] = { 24, 49, 122, 9, 88, 0 }, rem = 998877;

  __asm__div__u_ll(a, b, size - 1, quot, &rem);

  for(u_ll u = 0; u < size; u++)
  {
    std::cout << quot[u] << " ";
  }
  std::cout << "\n" << rem << "\n";

  
    // Expected Output:
    //   4 4 16 64 0 0 
    //   73
  
  return 0;
}

*/