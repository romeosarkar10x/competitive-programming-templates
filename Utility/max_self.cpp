#include <iostream>
#include <algorithm>


class MyClass
{
  int m_i;
  friend std::ostream& operator<<(std::ostream&, const MyClass&);

public:
  MyClass(int i) : m_i(i) {}
  bool operator<(const MyClass& object) const
  {
    std::cout << *this << ".operator<(const MyClass& " << object << ")\n";
    return (m_i < object.m_i);
  }
  MyClass operator+(const MyClass& object) const
  {
    std::cout << *this << ".operator+(const MyClass& " << object << ")\n";
    return m_i + object.m_i; 
  }
};

std::ostream& operator<<(std::ostream& o, const MyClass& object)
{
  o << "MyClass{ " << "m_i: " << object.m_i << " }";
  return o;
}


template<typename T>
inline void max_self(T& a, const T& b)
{
  a = std::max(a, b);
}

// template<typename T, typename ... Ts>
// T max(const T& t, const Ts& ... ts)
// {
//   // return (std::max(t, ts), ...);
//   T max = t;
//   (max_self(max, ts), ...);
//   return max;
// }

// template<typename ... Ts>
// auto sum(const Ts& ... ts)
// {
//   return (... + ts);
// }

template<typename T>
  void __max_self(T& m, const T& arg) { if(m < arg) { m = arg; } }

template<typename T, typename ... Ts>
  void max_self(T& m, const Ts& ... args) { (__max_self(m, args), ...); }

int main()
{
  MyClass object(2);
  max_self(object, MyClass(5), MyClass(3), MyClass(2), MyClass(7), MyClass(6));

  std::cout << object << "\n";

  // std::cout << sum(MyClass(5), MyClass(3), MyClass(2), MyClass(7), MyClass(6)) << "\n";
  return 0;
}