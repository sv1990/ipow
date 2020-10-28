#ifndef IPOW_IPOW_HH_1601928545
#define IPOW_IPOW_HH_1601928545

#include <type_traits>

#ifdef __cpp_concepts
#  define IPOW_TEMPLATE(...) template <__VA_ARGS__>
#  define IPOW_REQUIRES(...) requires(__VA_ARGS__)
#  define IPOW_CONCEPT       concept
#else
#  define IPOW_TEMPLATE(...) template <__VA_ARGS__
#  define IPOW_REQUIRES(...) , std::enable_if_t<__VA_ARGS__>* = nullptr >
#  define IPOW_CONCEPT       inline constexpr bool
#endif

namespace ipow {

template <typename T>
IPOW_CONCEPT integral = std::is_integral_v<T>;

template <typename T>
IPOW_CONCEPT arithmetic = std::is_arithmetic_v<T>;

IPOW_TEMPLATE(typename F, typename I)
IPOW_REQUIRES(arithmetic<F> && integral<I>)
[[nodiscard]] constexpr F ipow(F x, I n) noexcept {
  if (n == 0) {
    return 1;
  }
  if (n < 0) {
    x = F(1) / x;
    n = -n;
  }

  F z = 1;
  while (n != 1) {
    F arr[] = {1, x};
    z *= arr[n & 1];
    x *= x;
    n >>= 1;
  }
  return x * z;
}

IPOW_TEMPLATE(auto n, typename F)
IPOW_REQUIRES(integral<decltype(n)> && arithmetic<F>)
[[nodiscard, gnu::always_inline]] constexpr F ipow(F x) noexcept {
  if constexpr (n == 0) {
    return 1;
  }
  else if constexpr (n == 1) {
    return x;
  }
  else if constexpr (n < 0) {
    return ipow<-n>(F(1.) / x);
  }
  else if constexpr (n % 2 == 0) {
    F y = ipow<n / 2>(x);
    return y * y;
  }
  else {
    F y = ipow<n / 2>(x);
    return y * y * x;
  }
}
} // namespace ipow

#undef IPOW_TEMPLATE
#undef IPOW_REQUIRES
#undef IPOW_CONCEPT

#endif // IPOW_IPOW_HH_1601928545