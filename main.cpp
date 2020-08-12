#include <iostream>

#if __has_include(<concepts>)
#  include <concepts>
#else
#  include <type_traits>
namespace std {
template <typename T>
concept integral = std::is_integral_v<T>;
template <typename T>
concept floating_point = is_floating_point_v<T>;
} // namespace std
#endif

template <typename F, typename I>
requires((std::integral<F> || std::floating_point<F>)&&std::integral<I>) //
    constexpr F ipow(F x, I n) noexcept {
  if (n == 0) {
    return 1;
  }
  if (n < 0) {
    x = F(1) / x;
    n = -n;
  }
  F z = 1;
  while (true) {
    if (n == 1) {
      return x * z;
    }
    F arr[] = {1, x};
    z *= arr[n % 2];
    x *= x;
    n /= 2;
  }
}

template <auto n, typename F>
requires((std::integral<F> ||
          std::floating_point<F>)&&std::integral<std::decay_t<decltype(n)>>) //
    constexpr F ipow(F x) noexcept {
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

int main(int, char**) {
  std::cout << ipow<3>(2) << '\n';
  for (int n = -10; n < 10; ++n) {
    std::cout << "2 ** " << n << " = " << ipow(2., n) << '\n';
  }
}
