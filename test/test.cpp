#include "ipow.hh"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>

TEST_CASE("testing the factorial function") {
  std::mt19937_64 gen(std::random_device{}());
  std::vector<double> bases;
  std::generate_n(std::back_inserter(bases), 10000, [&]() mutable {
    return std::uniform_real_distribution<double>{0, 10}(gen);
  });

  std::vector<int> exponents;
  const int max_exponent = 100;
  const int min_exponent = -100;
  exponents.resize(max_exponent - min_exponent + 1);
  std::iota(begin(exponents), end(exponents), min_exponent);

  for (auto base : bases) {
    for (auto exponent : exponents) {
      const auto result   = ipow::ipow(base, exponent);
      const auto expected = std::pow(base, exponent);
      if (std::isinf(expected)) {
        CHECK(isinf(result));
      }
      else {
        CHECK(doctest::Approx(result) == expected);
      }
    }
  }
}
