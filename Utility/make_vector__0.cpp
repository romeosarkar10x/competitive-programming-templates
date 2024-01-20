#include <iostream>
#include <vector>


#ifdef _GLIBCXX_VECTOR
template<typename _Tp, size_t _Dim>
  struct __vector_type
  {
    using type = std::vector<typename __vector_type<_Tp, _Dim - 1U>::type>;
  };
template<typename _Tp> struct __vector_type<_Tp, 1U> { using type = std::vector<_Tp>; };


#if __cplusplus < 201703L
template<typename _Tp, typename _Val, typename _Dim1>
  [[nodiscard]] auto make_vector(_Val&& value, _Dim1 dim1)
  {
    return std::vector<_Tp>(dim1, std::forward<_Val>(value));
  }
#endif

template<typename _Tp, typename _Val, typename _Dim1, typename ... _Dims>
  [[nodiscard]] auto make_vector(_Val&& value, _Dim1 dim1, _Dims ... dims)
  {
  #if __cplusplus >= 201703L
    if constexpr(sizeof...(dims) == 0U)
    {
      return std::vector<_Tp>(dim1, std::forward<_Val>(value));
    }
    else
    {
  #endif
      return typename __vector_type<_Tp, sizeof...(_Dims) + 1U>::type(
        dim1,
        make_vector<_Tp>(std::forward<_Val>(value), dims...)
      );
  #if __cplusplus >= 201703L
    }
  #endif
  }
#endif



int main()
{
  [[maybe_unused]] size_t n_levels = 4, n_rows = 2, n_columns = 2;
  auto my_vector = make_vector<std::string>(std::string(), n_levels, n_rows);

  return 0;
}