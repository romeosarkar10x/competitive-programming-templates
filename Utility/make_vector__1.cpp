#include <iostream>
#include <vector>

namespace cp
{
  #ifdef _GLIBCXX_VECTOR
  template<typename _Tp, size_t _Dim>
    struct __vector_type
    {
      using type = std::vector<typename __vector_type<_Tp, _Dim - 1U>::type>;
    };
  template<typename _Tp> struct __vector_type<_Tp, 1U> { using type = std::vector<_Tp>; };


  template<typename _Tp, typename _Val, typename _Dim1>
    [[nodiscard]] auto make_vector(_Val&& value, _Dim1 dim1)
    {
      return std::vector<_Tp>(dim1, std::forward<_Val>(value));
    }

  template<typename _Tp, typename _Val, typename _Dim1, typename ... _Dims>
    [[nodiscard]] auto make_vector(_Val&& value, _Dim1 dim1, _Dims ... dims)
    {
      return typename __vector_type<_Tp, sizeof...(_Dims) + 1U>::type(
        dim1,
        make_vector<_Tp>(std::forward<_Val>(value), dims...)
      );
    }
  #endif
}

int main()
{
  auto my_vector = cp::make_vector<int> (-2, 3, 4, 4, 2, 8, 5);
  std::cout << my_vector[2][3][0][1][7][1] << "\n";
  
  return 0;
}