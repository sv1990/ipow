#include "ipow.hh"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

template <typename T>
using uniform_arithmetic_distribution =
    std::conditional_t<std::is_integral_v<T>, std::uniform_int_distribution<T>,
                       std::uniform_real_distribution<T>>;

int main(int, char**) {
  using base_t     = double;
  using exponent_t = long;

  std::mt19937_64 gen(std::random_device{}());
  std::vector<base_t> bases;
  std::generate_n(std::back_inserter(bases), 10000, [&]() mutable {
    return uniform_arithmetic_distribution<base_t>{0, 10}(gen);
  });

  std::vector<exponent_t> exponents;
  std::generate_n(std::back_inserter(exponents), 10000, [&]() mutable {
    return std::uniform_int_distribution<exponent_t>{-20, 20}(gen);
  });

  auto t1 = std::chrono::high_resolution_clock::now();

  base_t x1 = 0;
  for (auto x : bases) {
    for (auto n : exponents) {
      x1 += std::pow(x, n);
    }
  }
  auto t2 = std::chrono::high_resolution_clock::now();

  base_t x2 = 0;
  for (auto x : bases) {
    for (auto n : exponents) {
      x2 += ipow(x, n);
    }
  }

  auto t3 = std::chrono::high_resolution_clock::now();
  std::cout
      << x1 << ' '
      << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
      << "ms\n";
  std::cout
      << x2 << ' '
      << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count()
      << "ms\n";
}
