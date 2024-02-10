#include "../Include/__asm__mul.hpp"


int main()
{
  { // Test 1:
    u_ll a[] = { 1, 1, 4, 1, 0 }, b[] = { 2, 2, ULONG_LONG_MAX, 1, 0 }, tmp[9] = {}, ans[9] = {};
    
    __asm__mul(a, b, 4, 4, tmp, ans);

    for(int i = 0; i < 9; i++) { std::cout << ans[i] << " "; }
    std::cout << "\n";

    // Expected Output: 2 4 9 11 0 7 2 0 0 
  }

  return 0;
}
