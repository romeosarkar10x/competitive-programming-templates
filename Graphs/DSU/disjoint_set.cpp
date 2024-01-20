#include "disjoint_set__base.cpp"
#include <unordered_map>

template<typename _Tp, typename _Hash = std::hash<_Tp>>
class DisjointSet : public DisjointSet__Base
{
public:
  DisjointSet(u_int n_nodes, bool create_all_nodes = false) : DisjointSet__Base(n_nodes, create_all_nodes) {}
  void union_(u_int node_a, u_int node_b);
  void union_if_exists(u_int node_a, u_int node_b);
  void create_node(u_int node);
  u_int find_parent(u_int node);
  bool is_joint(u_int node_a, u_int node_b);
  inline bool exists(u_int node);
  u_int n_groups();

protected:
  std::vector<size_t> weights;
  // std::unordered_map<_Tp, u_int, _Hash, > map_nodes;
};

int main()
{
  DisjointSet<u_int> dsu(10U);

  std::cout << std::equal_to<int>()(1, 1) << std::endl;
  // std::cout << "hello world" << std::endl;

  return 0;
}