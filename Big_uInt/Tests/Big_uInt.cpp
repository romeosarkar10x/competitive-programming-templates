#include "../Big_uInt.hpp"

int main()
{
  Big_uInt u { 123234325325324234ull }, u2 { 3434253522323432432ull };
  u *= u2;
  
  std::cout << u.to_string__decimal() << "\n";
  return 0;
}