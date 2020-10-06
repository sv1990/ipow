#ifndef IPOW_IPOW_HH_1601928545
#define IPOW_IPOW_HH_1601928545

#include <type_traits>

template <typename T>
concept integral = std::is_integral_v<T>;

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <arithmetic F>
[[nodiscard]] constexpr F ipow(F x, integral auto n) noexcept {
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
    z *= arr[n % 2];
    x *= x;
    n /= 2;
  }
  return x * z;
}

template <integral auto n, arithmetic F>
[[nodiscard]] constexpr F ipow(F x) noexcept {
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

#endif // IPOW_IPOW_HH_1601928545