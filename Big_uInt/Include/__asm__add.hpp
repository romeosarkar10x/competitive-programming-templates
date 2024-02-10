#ifndef __ASM__ADD_HPP
#define __ASM__ADD_HPP

#include <iostream>
#include "global.hpp"



/*
** size__lhs == size__rhs,
** destination: lhs,
** lhs must have extra space to fit the carry
*/
static void __asm__add(u_ll* lhs, u_ll* rhs, u_ll size)
{
  asm(
    "mov  $1, %%al\n"

    ".LOOP0:\n\t"
    "cmpb $1, %%al\n\t"         // restore carry
    "movq (%[rhs]), %%r10\n\t"
    "adcq %%r10, (%[lhs])\n\t"  // add with carry
    "setae  %%al\n\t"           // set carry
    
    "leaq 8(%[lhs]), %[lhs]\n\t"
    "leaq 8(%[rhs]), %[rhs]\n\t"
    
    "dec  %[size]\n\t"
    "jnz  .LOOP0\n"
    
    :
    : [lhs]"r"(lhs), [rhs]"r"(rhs), [size]"r"(size)
    : "%rax", "%r9"
  );
}


#endif