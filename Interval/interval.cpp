#include <iostream>
#include <limits>

namespace cp
{
  class interval
  {
    int m_l;
    int m_r;
    bool m_is_valid;

    void m_extend_left();
    void m_extend_right();

  public:
    interval(int l, int r);
    interval();

    interval(const interval&) = default;
    interval(interval&&) = default;
    
    interval& operator=(const interval&) = default;
    interval& operator=(interval&&) = default;
    
    ~interval() = default;

    interval& _union(const interval& rhs);
    interval& _intersection(const interval& rhs);

    interval& extend_left(int k);
    interval& extend_right(int k);
    interval& extend(int k);
    
    interval& slide(int k);

    int l() const;
    int r() const;
    int size() const;
    bool contains(int n) const;
    bool contains(const interval& rhs) const;

    bool is_valid() const;

    static bool is_disjoint(const interval& lhs, const interval& rhs);
    static bool is_intersecting(const interval& lhs, const interval& rhs);

    void reset();

    interval operator||(const interval& rhs); // union
    interval operator&&(const interval& rhs); // intersection
    
    interval operator+(int k); // slide
    interval operator-(int k); // slide
  };

  inline interval::interval(int l, int r) : m_l(l), m_r(r), m_is_valid(true)
  {
    if(l > r) { m_is_valid = false; }
  }

  inline interval::interval() : interval(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) {}

  inline void interval::reset()
  {
    new (this) interval;
  }

  inline interval& interval::_union(const interval& rhs)
  {
    if(!m_is_valid || !rhs.m_is_valid || is_disjoint(*this, rhs))
    {
      m_is_valid = false;
      return *this;
    }

    m_l = std::min(m_l, rhs.m_l);
    m_r = std::max(m_r, rhs.m_r);
    return *this;
  }

  inline interval& interval::_intersection(const interval& rhs)
  {
    if(!m_is_valid || !rhs.m_is_valid || is_disjoint(*this, rhs))
    {
      m_is_valid = false;
      return *this;
    }

    m_l = std::max(m_l, rhs.m_l);
    m_r = std::min(m_r, rhs.m_r);
    return *this;
  }

  inline interval& interval::extend_left(int k)
  {
    // if(std::numeric_limits<int>::min() -  > k)
    // {
    //   m_l = std::numeric_limits<int>::min();
    //   return *this;
    // }

    m_l -= k;
    return *this;
  }

  inline interval& interval::extend_right(int k)
  {
    // if(std::numeric_limits<int>::max() - m_r < k)
    // {
    //   m_r = std::numeric_limits<int>::max();
    //   return *this;
    // }

    m_r += k;
    return *this;
  }

  inline interval& interval::extend(int k)
  {
    (void) extend_left(k);
    (void) extend_right(k);
    return *this;
  }

  inline interval& interval::slide(int k)
  {
    (void) extend_left(-k);
    (void) extend_right(k);
    return *this;
  }

  inline int interval::l() const { return m_l; }
  inline int interval::r() const { return m_r; }

  inline int interval::size() const
  {
    if(!m_is_valid)
    {
      return -1;
    }

    return m_r - m_l + 1;
  }

  inline bool interval::contains(int n) const
  {
    if(!m_is_valid)
    {
      return false;
    }

    return m_l <= n && n <= m_r;
  }

  inline bool interval::contains(const interval& i) const
  {
    if(!m_is_valid || !i.m_is_valid)
    {
      return false;
    }
    
    return m_l <= i.m_l && i.m_r <= m_r;
  }

  inline bool interval::is_valid() const
  {
    return m_is_valid;
  }

  inline bool interval::is_disjoint(const interval& lhs, const interval& rhs)
  {
    return lhs.m_r < rhs.m_l || rhs.m_r < lhs.m_l;
  }

  inline bool interval::is_intersecting(const interval& lhs, const interval& rhs)
  {
    return !is_disjoint(lhs, rhs);
  }

  inline interval interval::operator||(const interval& rhs)
  {
    interval ans(*this);
    return ans._union(rhs);
  }

  inline interval interval::operator&&(const interval& rhs)
  {
    interval ans(*this);
    return ans._intersection(rhs);
  }

  inline interval interval::operator+(int k)
  {
    interval ans(*this);
    return ans.slide(k);
  }

  inline interval interval::operator-(int k)
  {
    interval ans(*this);
    return ans.slide(-k);
  }

  inline std::istream& operator>>(std::istream& __i, interval& rhs)
  {
    int l, r;
    __i >> l >> r;

    new (&rhs) interval (l, r);
    return __i;
  }

  inline std::ostream& operator<<(std::ostream& __o, const interval& rhs)
  {
    if(!rhs.is_valid())
    {
      __o << "[ invalid ]";
    }
    else
    {
      __o << "[" << rhs.l() << ", " << rhs.r() << "]";
    }

    return __o;
  }
}

int main()
{
  cp::interval i(5, 55), i2(3, 12);

  std::cout << "i: " << i << "\n";
  std::cout << "i2: " << i2 << "\n";

  std::cout << "i && i2: " << (i && i2) << "\n"; // union
  std::cout << "i || i2: " << (i || i2) << "\n"; // intersection

  std::cout << "i.slide(3): " << (i.slide(3)) << "\n"; // slide
  std::cout << "i2.extend(2): " << (i2.extend(2)) << "\n"; // extend

  std::cout << "i: " << i << "\n";
  std::cout << "i2: " << i2 << "\n";

  return 0;
}