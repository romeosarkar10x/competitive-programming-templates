#ifndef __ASM__MUL_HPP
#define __ASM__MUL_HPP

#include <iostream>
// #include <iomanip>

#include "global.hpp"
#include "__asm__add.hpp"


// const int Width = 20;


/*
** size__lhs >= size__rhs,
** @size__lhs - 1, @size__rhs - 1,
** @param: ans must have space to fit the result
*/
static void __asm__mul(const u_ll* lhs, const u_ll* rhs, const u_ll size__lhs, const u_ll size__rhs, u_ll* tmp, u_ll* ans)
{
  for(u_ll u = 0; u < size__rhs; u++)
  {
    asm(
      "movq $0, (%[tmp])\n\t"

      ".LOOP1:\n\t"
      "movq (%[lhs]), %%rax\n\t"
      "mulq %[rhs]\n\t"       // [rdx:rax]

      "addq %%rax, (%[tmp])\n\t"
      "adcq $0, %%rdx\n\t"
      "movq %%rdx, 8(%[tmp])\n\t"

      "leaq 8(%[lhs]), %[lhs]\n\t"
      "leaq 8(%[tmp]), %[tmp]\n\t"
      "dec  %[size__lhs]\n\t"       
      "jnz  .LOOP1"
      : 
      : [lhs]"r"(lhs), [rhs]"r"(rhs[u]), [tmp]"r"(tmp), [size__lhs]"r"(size__lhs)
      : "%rax", "%rdx"
    );
    
    // for(u_ll v = 0; v < u; v++) { std::cout << std::setw(Width) << 0 << " "; }
    // for(u_ll v = 0; v <= size__lhs; v++)
    // {
    //   std::cout << std::setw(Width) << tmp[v] << " ";
    // }
    // std::cout << "\n";

    __asm__add(ans + u, tmp, size__lhs + 1);
  }
}

#endif