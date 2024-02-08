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
    delete [] _m_buffer;
    
    _m_size = 0;
    _m_buffer = nullptr;
  }
private:

  u_int _m_size { 1u };
  u_char _m_capacity__pow_2 { 0u }; // _m_capacity is always a power of 2

  u_ll* _m_buffer;
  // union __U
  // {
  //   u_ll _m_u;
  // } _m_d;

  void _m_grow(u_int _amount)
  {
    u_char expected_cap = _m_capacity__pow_2;
    while(_m_size + _amount > (1u << expected_cap)) { expected_cap++; }

    if(expected_cap > _m_capacity__pow_2)
    {
      _m_realloc(expected_cap);
    }
    else { _m_size += _amount; }
  }
  void _m_shrink(u_int _amount)
  {
    // if(_m_size - _amount)
  }
  void _m_realloc(u_char _cap__pow_2)
  {
    u_ll* buf = new u_ll [(1u << _cap__pow_2)];

    for(u_int u = 0u; u < (1u << _m_capacity__pow_2); u++)
    {
      buf[u] = _m_buffer[u];
    }

    for(u_int u = _m_capacity__pow_2; u < (1u << _cap__pow_2); u++)
    {
      buf[u] = 0ull;
    }

    delete [] _m_buffer;
    _m_buffer = buf;
  }

  void _m_add(const Big_uInt& rhs);
  void _m_mul(const Big_uInt& rhs);

public:
  // dest: lhs, (lhs >= rhs), lhs has extra space to fit the carry!
  static void _m_asm_add(u_ll* lhs, u_ll* rhs, u_short size__rhs);
  static void _m_asm_sub();
  static void _m_asm_mul();
  static void _m_asm_div();
  
};

int main()
{
  Big_uInt u { 123u }, u2 { 3432u };

  std::cout << sizeof(Big_uInt) << "\n";

  // std::cout << i << "\n";


  return 0;
}