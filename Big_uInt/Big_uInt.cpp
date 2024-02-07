#include <iostream>
#include "_global_def.hpp"

class Big_uInt
{
public:
  // Big_uInt(long long l) : Big_uInt() { _m_p[0] = l; }
  // Big_uInt(int i) : Big_uInt(static_cast<ll>(i)) {}

  Big_uInt(u_ll t) {}
  Big_uInt(u_int u) : Big_uInt(static_cast<u_ll>(u)) {}

  Big_uInt(std::string s);

  std::string to_string();

  Big_uInt operator+(const Big_uInt& rhs);
  Big_uInt operator-(const Big_uInt& rhs);
  Big_uInt operator*(const Big_uInt& rhs);
  Big_uInt operator/(const Big_uInt& rhs);
  Big_uInt operator%(const Big_uInt& rhs);

  Big_uInt operator+=(const Big_uInt& rhs);
  Big_uInt operator-=(const Big_uInt& rhs);
  Big_uInt operator*=(const Big_uInt& rhs);
  Big_uInt operator/=(const Big_uInt& rhs);
  Big_uInt operator%=(const Big_uInt& rhs);

  Big_uInt operator<<(int i);
  Big_uInt operator>>(int i);

  Big_uInt operator<<=(int i);
  Big_uInt operator>>=(int i);
  
  Big_uInt operator&(const Big_uInt& rhs);
  Big_uInt operator|(const Big_uInt& rhs);
  Big_uInt operator^(const Big_uInt& rhs);

  Big_uInt operator<(const Big_uInt& rhs);
  Big_uInt operator>(const Big_uInt& rhs);

  Big_uInt operator>=(const Big_uInt& rhs);
  Big_uInt operator<=(const Big_uInt& rhs);
  Big_uInt operator==(const Big_uInt& rhs);
  Big_uInt operator!=(const Big_uInt& rhs);

  Big_uInt operator-();
  Big_uInt operator+();
  
  // operator int ();
  // operator long long();
  
  operator u_int();
  operator u_ll();



  ~Big_uInt()
  {
    delete [] _m_p;
    
    _m_size = 0;
    _m_p = nullptr;
  }
private:

  u_short _m_size { 1u };
  u_char _m_capacity__pow_2 { 0u }; // _m_capacity is always a power of 2

  u_ll* _m_p;
  // union __U
  // {
  //   u_ll _m_u;
  // } _m_d;


  // Big_uInt() : _m_size(1u), _m_capacity__pow_2(0u) {}

  void _m_add(const Big_uInt& rhs);

public:
  // dest: lhs, (lhs >= rhs), lhs has extra space to fit the carry!
  static void _m_asm_add(u_ll* lhs, u_ll* rhs, u_short size__rhs)
  {
    asm(
      "movq %0, %%r10\n\t"
      "movq %1, %%r11\n\t"
      "mov  %2, %%cx\n\t"
      "dec %%cx\n\t"
      "jz LABEL_EXIT\n"
      "LABEL_EXIT:\n\t"
      
      :
      : "r"(lhs), "r"(rhs), "r"(size__rhs)
      : "%r10", "%r11", "%cx"
    );
  }
  static void _m_asm_sub() {}
  static void _m_asm_mul() {}
  static void _m_asm_div() {}
  
};

int main()
{
  Big_uInt u { 123u }, u2 { 3432u };

  std::cout << sizeof(Big_uInt) << "\n";

  // std::cout << i << "\n";


  return 0;
}