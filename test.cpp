#include "ipow.hh"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

template <typename T>
using uniform_arithmetic_distribution =
    std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>,
                       std::uniform_real_distribution<T>>;

template <typename T>
concept floating_point = std::is_floating_point_v<T>;

[[nodiscard]] bool test(auto x, auto y) noexcept {
  return x == y;
}

[[nodiscard]] bool test(floating_point auto x, floating_point auto y) noexcept {
  return std::abs(x - y) / std::abs(y) < 1e-7;
}

int main(int, char**) {
  using base_t     = double;
  using exponent_t = long;

  std::mt19937_64 gen(std::random_device{}());
  std::vector<base_t> bases;
  std::generate_n(std::back_inserter(bases), 10000, [&]() mutable {
    return uniform_arithmetic_distribution<base_t>{0, 10}(gen);
  });

  std::vector<exponent_t> exponents;
  const exponent_t max_exponent = 20;
  const exponent_t min_exponent = std::is_signed_v<exponent_t> ? -20 : 0;
  exponents.resize(max_exponent - min_exponent);
  std::iota(begin(exponents), end(exponents), min_exponent);
  
  std::generate_n(std::back_inserter(exponents), 10000, [&]() mutable {
    return std::uniform_int_distribution<exponent_t>{
        std::is_signed_v<exponent_t> ? -20 : 0, 20}(gen);
  });

  std::size_t failed = 0;
  for (auto x : bases) {
    for (auto n : exponents) {
      auto result   = ipow::ipow(x, n);
      auto expected = std::pow(x, n);
      if (!test(result, expected)) {
        std::cerr << "Failed for pow(" << x << ", " << n << ")\n";
        if (++failed == 10) {
          break;
        }
      }
    }
  }
}
