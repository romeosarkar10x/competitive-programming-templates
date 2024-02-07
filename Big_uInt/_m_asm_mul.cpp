#include <iostream>
#include <iomanip>
#include "_m_asm_add.cpp"


const int Width = 20;

// (lhs >= rhs) // pass size__lhs minus 1, size__rhs minus 1
static void _m_asm_mul(u_ll* lhs, u_ll* rhs, u_ll size__lhs, u_ll size__rhs, u_ll* tmp, u_ll* ans)
{
  for(u_ll u = 0; u < size__rhs; u++)
  {
    asm(
      "movq %0, %%r8\n\t"   // lhs
      "movq %1, %%r9\n\t"   // rhs[u]
      "movq %2, %%r10\n\t"  // tmp
      "mov  %3, %%rcx\n\t"  // size

      "movq $0, (%%r10)\n\t"

      ".LOOP1:\n\t"
      "movq (%%r8), %%rax\n\t"
      "mulq %%r9\n\t"       // ans: [rdx:rax]

      "addq %%rax, (%%r10)\n\t"
      "adcq $0, %%rdx\n\t"
      "movq %%rdx, 8(%%r10)\n\t"

      "addq $8, %%r8\n\t"
      "addq $8, %%r10\n\t"
      "dec  %%rcx\n\t"       
      "jnz  .LOOP1"
      : 
      : "g"(lhs), "g"(rhs[u]), "g"(tmp), "g"(size__lhs)
      : "%rax", "%rcx", "%rdx", "%r8", "%r9", "%r10"
    );
    
    for(u_ll v = 0; v < u; v++) { std::cout << std::setw(Width) << 0 << " "; }
    for(u_ll v = 0; v <= size__lhs; v++)
    {
      std::cout << std::setw(Width) << tmp[v] << " ";
    }
    std::cout << "\n";

    _m_asm_add(ans + u, tmp, size__lhs + 1);
  }
}


/*

int main()
{
  u_ll a[] = { 1, 1, 4, 1, 0 }, b[] = { 2, 2, ULONG_LONG_MAX, 1, 0 }, tmp[9] = {}, ans[9] = {};
  
  _m_asm_mul(a, b, 4, 4, tmp, ans);

  for(int i = 0; i < 9; i++)
  {
    std::cout << std::setw(Width) << ans[i] << " ";
  }
  std::cout << "\n";

  // 18 446 744 073 709 551 615
  return 0;
}

*/