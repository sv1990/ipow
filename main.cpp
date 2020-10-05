#include "ipow.hh"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

int main(int, char**) {
  std::mt19937_64 gen(std::random_device{}());
  std::vector<double> bases;
  std::generate_n(std::back_inserter(bases), 10000, [&]() mutable {
    return std::uniform_real_distribution<double>{0, 10}(gen);
  });

  std::vector<long> exponents;
  std::generate_n(std::back_inserter(exponents), 10000, [&]() mutable {
    return std::uniform_int_distribution<long>{-20, 20}(gen);
  });

  auto t1 = std::chrono::high_resolution_clock::now();

  double x1 = 0;
  for (auto x : bases) {
    for (auto n : exponents) {
      x1 += std::pow(x, n);
    }
  }
  auto t2 = std::chrono::high_resolution_clock::now();

  double x2 = 0;
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
