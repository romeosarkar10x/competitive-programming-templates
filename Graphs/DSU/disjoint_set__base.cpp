#include <iostream>
#include <vector>
#include <string>


using u_int = unsigned int;
// template<u_int _Offset = 0U>
class DisjointSet__Base
{

public:
  DisjointSet__Base(u_int n_nodes, bool create_all_nodes = false) : m_parents(n_nodes, Uninitialized)
  {
    if(create_all_nodes) {
      m_create_all_nodes();
    }
  }
  
  void union_(u_int node_a, u_int node_b)
  {
    // u_int node_a = __node_a - _Offset, node_b = __node_b - _Offset;
    m_range_check(node_a);
    m_range_check(node_b);
    m_create_node(node_a);
    m_create_node(node_b);

    m_union(node_a, node_b);
  }

  void union_if_exists(u_int node_a, u_int node_b)
  {
    if(exists(node_a) && exists(node_b)) {
      union_(node_a, node_b);
    }
  }


  void create_node(u_int node)
  {
    // u_int node = __node - _Offset;
    m_range_check(node);
    m_create_node(node);
  }

  u_int find_parent(u_int node)
  {
    // u_int node = __node - _Offset;
    m_range_check(node);
    m_exists_check(node);

    // return m_find_parent(node) + _Offset;
    return m_find_parent(node);
  }

  bool is_joint(u_int node_a, u_int node_b)
  {
    // u_int node_a = __node_a - _Offset, node_b = __node_b - _Offset;
    m_range_check(node_a);
    m_range_check(node_b);

    return (m_find_parent(node_a) == m_find_parent(node_b));
  }

  inline bool exists(u_int node)
  {
    // u_int node = __node - _Offset;
    m_range_check(node);

    return m_exists(node);
  }
  
  u_int n_groups() {
    return m_n_groups;
  }

protected:
  // static_assert(_Offset == 0U || _Offset == 1U, "");
  
  enum : u_int { Uninitialized = 1333999222U };
  std::vector<u_int> m_parents;
  u_int m_n_groups = 0U;

  void m_create_node(u_int node)
  {
    if(m_parents[node] == Uninitialized)
    {
      m_n_groups++;
      m_parents[node] = node;
    }
  }

  void m_union(u_int node_a, u_int node_b)
  {
    u_int parent__node_a = m_find_parent(node_a), parent__node_b = m_find_parent(node_b);
    
    if(parent__node_a == parent__node_b) {
      return;
    }
    
    m_n_groups--;
    m_parents[parent__node_b] = parent__node_a;
  }

  u_int m_find_parent(u_int node)
  {
    if(m_parents[node] == node) {
      return node;
    }
    
    return m_parents[node] = m_find_parent(m_parents[node]);
  }

  bool m_exists(u_int node) {
    return !(m_parents[node] == Uninitialized);
  }

  void m_exists_check(u_int node)
  {
    if(!m_exists(node)) {
      throw std::invalid_argument(
        "DisjointSet::m_exists_check: node (which is " +
        std::to_string(node) + ") does not exist"
      );
    }
  }

  void m_range_check(u_int node) {
    if(node >= m_parents.size()) {
      throw std::out_of_range(
        std::string("DisjointSet::m_range_check: node (which is ") +
        std::to_string(node) + ") >= this->size() (which is " +
        std::to_string(m_parents.size()) + ")"
      );
    }
  }

  void m_create_all_nodes()
  {
    for(u_int node = 0U; node < m_parents.size(); node++) {
      m_parents[node] = node;
    }

    m_n_groups = static_cast<u_int>(m_parents.size());
  }

};

// int main()
// {
//   u_int n_nodes = 10U;
//   DisjointSet__Base<1> s(n_nodes);

//   s.union_(2, 3);
//   s.union_(3, 4);
//   s.union_(3, 5);

//   s.union_(1, 6);
//   s.union_(1, 7);
//   s.union_(1, 8);

//   std::cout << s.n_groups() << std::endl;
  
//   s.union_if_exists(1, 9);
//   s.create_node(9);
  
//   std::cout << s.n_groups() << std::endl;
  
//   s.union_(9, 10);
//   std::cout << s.n_groups() << std::endl;

//   s.union_(1, 9);
//   std::cout << s.n_groups() << std::endl;



//   for(u_int node = 1U; node <= n_nodes; node++) {
//     std::cout << node << ": " << s.find_parent(node) << "\n";
//   }
  
//   return 0;
// }