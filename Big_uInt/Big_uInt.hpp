#include <iostream>
#include <utility>
#include <algorithm>

#include "Include/global.hpp"
#include "Include/__asm__add.hpp"
#include "Include/__asm__mul.hpp"
#include "Include/__asm__div__u_ll.hpp"

class Big_uInt
{
public:
  Big_uInt(u_int u) : Big_uInt(static_cast<u_ll>(u)) {}
  Big_uInt(u_ll t) : Big_uInt() { _m_buffer[0] = t; }



  Big_uInt(const Big_uInt& __u) : _m_size(__u._m_size), _m_capacity__pow_2(__u._m_capacity__pow_2), _m_buffer(new u_ll [_m_size])
  {
    for(u_int u = 0u; u < (1u << _m_capacity__pow_2); u++) { _m_buffer[u] = __u._m_buffer[u]; }
  }

  Big_uInt(Big_uInt&& __u) : _m_size(std::exchange(__u._m_size, 0u)), _m_capacity__pow_2(__u._m_capacity__pow_2), _m_buffer(std::exchange(__u._m_buffer, nullptr)) {} 

  Big_uInt operator+(const Big_uInt& rhs);
  Big_uInt operator-(const Big_uInt& rhs);
  Big_uInt operator*(const Big_uInt& rhs);
  Big_uInt operator/(const Big_uInt& rhs);
  Big_uInt operator%(const Big_uInt& rhs);

  const Big_uInt& operator+=(const Big_uInt& rhs) { _m_add(rhs); return *this; }
  const Big_uInt& operator-=(const Big_uInt& rhs);
  const Big_uInt& operator*=(const Big_uInt& rhs) { _m_mul(rhs); return *this; }
  // const Big_uInt& operator/=(const Big_uInt& rhs) { _m_div(rhs); return *this; }
  const Big_uInt& operator%=(const Big_uInt& rhs);

  Big_uInt operator<<(int i);
  Big_uInt operator>>(int i);

  Big_uInt operator<<=(int i);
  Big_uInt operator>>=(int i);
  
  Big_uInt operator&(const Big_uInt& rhs);
  Big_uInt operator|(const Big_uInt& rhs);
  Big_uInt operator^(const Big_uInt& rhs);

  bool operator<(const Big_uInt& rhs);
  bool operator>(const Big_uInt& rhs);

  bool operator>=(const Big_uInt& rhs);
  bool operator<=(const Big_uInt& rhs);

  bool operator==(const Big_uInt& rhs)
  {
    if(_m_size == rhs._m_size)
    {
      bool is_equal = true;

      for(u_ll u = 0u; u < _m_size; u++)
      {
        if(_m_buffer[u] != rhs._m_buffer[u])
        {
          is_equal = false;
          break;
        }
      }

      return is_equal;
    }

    return false;
  }

  bool operator==(u_ll u)
  {
    return (_m_size == 1u && _m_buffer[0] == u);
  }

  bool operator!=(const Big_uInt& rhs) { return !operator==(rhs); }
  bool operator!=(u_ll u) { return !operator==(u); }

  Big_uInt operator-();
  Big_uInt operator+();
  
  
  // operator u_int();
  // operator u_ll();

  std::string to_string__decimal()
  {
    std::string s;
    while(*this != 0u) { s += static_cast<char>(_m_div__u_ll(10ull)) + '0'; }
    std::reverse(s.begin(), s.end());
    return s;
  }

  ~Big_uInt()
  {
    if(_m_size != 0u)
    {
      delete [] _m_buffer;
      
      _m_size = 0u;
      _m_buffer = nullptr;
    }
  }
private:

  u_int _m_size;
  u_char _m_capacity__pow_2; // _m_capacity is always a power of 2

  u_ll* _m_buffer;

  Big_uInt() : _m_size(2u), _m_capacity__pow_2(1u), _m_buffer(new u_ll [2u]) { _m_buffer[1u] = 0ull; }

  void _m_increase_size__relative(u_int _amount)
  {
    u_char final_cap = _m_capacity__pow_2;
    while(_m_size + _amount > (1u << final_cap)) { final_cap++; }

    _m_increase_capacity(final_cap);

    _m_size += _amount;
  }

  void _m_increase_size__absolute(u_int _amount)
  {
    u_char final_cap = _m_capacity__pow_2;
    while(_amount > (1u << final_cap)) { final_cap++; }

    _m_increase_capacity(final_cap);

    _m_size = _amount;
  }

  void _m_increase_capacity(u_char _final_cap__pow_2)
  {
    if(_final_cap__pow_2 > _m_capacity__pow_2)
    {
      _m_realloc(_final_cap__pow_2);
    }
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

  void _m_trim()
  {
    while(_m_size >= 2u && _m_buffer[_m_size - 2u] == 0ll) { _m_size--; }
  }

  void _m_reserve(u_char _final_cap)
  {

    
  }
  void _m_shrink(u_int _amount)
  {
    // if(_m_size - _amount)
  }

  void _m_add(const Big_uInt& rhs)
  {
    Big_uInt rhs_copy = rhs;
    u_int size = std::max(this->_m_size, rhs_copy._m_size);

    this->_m_increase_size__absolute(size);
    rhs_copy._m_increase_size__absolute(size);

    __asm__add(_m_buffer, rhs._m_buffer, size);
    
    if((_m_buffer)[size - 1u] != 0ull) { _m_increase_size__relative(1u); }
  }

  void _m_mul(const Big_uInt& rhs)
  {
    Big_uInt product { 0ull };
    u_int final_size = _m_size + rhs._m_size - 1u;
    
    u_ll* tmp = new u_ll [final_size];
    product._m_increase_size__absolute(final_size);

    __asm__mul(_m_buffer, rhs._m_buffer, _m_size - 1u, rhs._m_size - 1u, tmp, product._m_buffer);

    product._m_trim();
    
    delete [] tmp;
    this->~Big_uInt();

    new (this) Big_uInt(std::move(product));
  }

  u_ll _m_div__u_ll(u_ll rhs)
  {
    u_ll remainder;
    Big_uInt quotient(*this);

    __asm__div__u_ll(_m_buffer, rhs, _m_size, quotient._m_buffer, &remainder);

    quotient._m_trim();

    this->~Big_uInt();
    new (this) Big_uInt(std::move(quotient));

    return remainder;
  }



public:


  static void _m_asm_div();
  static void _m_asm_sub();
  
};

