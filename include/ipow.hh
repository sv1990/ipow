#ifndef IPOW_IPOW_HH_1601928545
#define IPOW_IPOW_HH_1601928545

#include <type_traits>

namespace ipow {
#ifdef __cpp_concepts
template <typename T>
concept integral = std::is_integral_v<T>;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;
#endif

#ifdef __cpp_concepts
template <arithmetic F, integral I>
#else
template <typename F, typename I>
#endif
[[nodiscard]] constexpr F ipow(F x, I n) noexcept {
#ifndef __cpp_concepts
  static_assert(std::is_arithmetic_v<F>,
                "The base should be an arithmetic type");
  static_assert(std::is_integral_v<I>,
                "The exponent should be an integral type. Use std::pow for "
                "floating point exponents");
#endif
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

#ifdef __cpp_concepts
template <integral auto n, arithmetic F>
#else
template <auto n, typename F>
#endif
[[nodiscard, gnu::always_inline]] constexpr F ipow(F x) noexcept {
#ifndef __cpp_concepts
  static_assert(std::is_arithmetic_v<F>,
                "The base should be an arithmetic type");
  static_assert(std::is_integral_v<decltype(n)>,
                "The exponent should be an integral type. Use std::pow for "
                "floating point exponents");
#endif
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

#endif // IPOW_IPOW_HH_1601928545