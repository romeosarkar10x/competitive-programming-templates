#include "_global_def.hpp"

static void _m_asm_div__long_long(u_ll* lhs, u_ll rhs, u_short size, u_ll* quot, u_ll* rem)
{
  asm(
    "movq %1, %%r8\n\t" // lhs 
    "movq %2, %%
    
    :
    : "g"(lhs), "g"(rhs), "g"(size)
    : "%rax", "rcx", "%rdx", "%r8", "%r9"
  );
}


int main()
{
  long long a[] = { 0, 1, 1, 4, 16, 0 }, b = (1ull << 62);


  return 0;
}