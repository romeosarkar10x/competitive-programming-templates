#include <iostream>
#include <vector>
#include <string>

using u_int = unsigned int;
template<u_int _Offset = 0U>
class DisjointSet__Dyn
{

public:
  DisjointSet__Dyn() = default;
  
  void add_node(u_int node) {
    m_range_check(node);
    m_add_node(node);
  }

  void union_(u_int __node_a, u_int __node_b)
  {
    u_int node_a = __node_a - _Offset, node_b = __node_b - _Offset;
    m_range_check(node_a);
    m_range_check(node_b);
    m_add_node(node_a);
    m_add_node(node_b);
    
    m_union(node_a, node_b);
  }

  u_int find_parent(u_int __node)
  {
    u_int node = __node - _Offset;
    m_range_check(node);
    m_add_node(node);

    return m_find_parent(node) + _Offset;
  }

  bool is_joint(u_int __node_a, u_int __node_b)
  {
    u_int node_a = __node_a - _Offset, node_b = __node_b - _Offset;
    m_range_check(node_a);
    m_range_check(node_b);

    return (m_find_parent(node_a) == m_find_parent(node_b));
  }

  u_int n_groups() {
    return m_n;
  }

private:
  static_assert(_Offset == 0U || _Offset == 1U, "");
  
  enum : u_int { Uninitialized = 1444999222U };
  std::vector<u_int> m_parents;
  std::vector<u_int> m_size;
  u_int m_n = 0;

  inline void m_add_node(u_int node)
  {
    if(m_parents[node] == Uninitialized)
    {
      m_n++;
      // std::cout << "\e[32mnode created (" << node << ") : " << m_n << "\n\e[m";
      m_parents[node] = node;
    }
  }

  u_int m_find_parent(u_int node)
  {
    if(m_parents[node] == node) {
      return node;
    }
    
    return m_parents[node] = m_find_parent(m_parents[node]);
  }

  void m_union(u_int node_a, u_int node_b) {
    u_int parent__node_a = m_find_parent(node_a), parent__node_b = m_find_parent(node_b);
    
    if(parent__node_a == parent__node_b) {
      return;
    }
    
    m_n--;
    // std::cout << "\e[31mmerged (" << parent__node_a << " and " << parent__node_b << ") : " << m_n << "\e[m\n";
    m_parents[parent__node_b] = parent__node_a;
  }

  void m_range_check(size_t n) {
    if(n >= m_parents.size()) {
      m_parents.resize(n + 1U, Uninitialized);
    }
  }
};

int main()
{
  size_t n_nodes = 16U;
  DisjointSet__Dyn s;

  s.union_(2, 3);
  s.union_(3, 4);
  s.union_(3, 5);

  s.union_(1, 6);
  s.union_(1, 7);
  s.union_(1, 8);

  s.union_(12, 13);
  s.union_(12, 14);

  s.union_(9, 11);
  s.union_(15, 11);
  s.union_(16, 9);
  s.union_(10, 16);


  for(u_int node = 1U; node <= n_nodes; node++) {
    std::cout << node << ": " << s.find_parent(node) << "\n";
  }

  std::cout << "n_groups: " << s.n_groups() << "\n";

  s.union_(2, 1);
  std::cout << "n_groups: " << s.n_groups() << "\n";
  
  return 0;
}