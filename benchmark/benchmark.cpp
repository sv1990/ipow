#include "ipow.hh"

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cmath>
#include <random>

const std::vector<double>& get_bases() {
  static std::mt19937_64 gen(std::random_device{}());
  static const std::vector<double> bases = [] {
    std::vector<double> bases;
    std::generate_n(std::back_inserter(bases), 10000, [&]() mutable {
      return std::uniform_real_distribution<double>{0, 10}(gen);
    });
    return bases;
  }();
  return bases;
}

static void STD_POW(benchmark::State& state) {
  auto bases = get_bases();
  auto it    = begin(bases);
  for (auto _ : state) {
    auto x = std::pow(*it, state.range(0));
    ++it;
    if (it == end(bases)) {
      it = begin(bases);
    }
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(STD_POW)->RangeMultiplier(2)->Range(0, 256);

static void IPOW(benchmark::State& state) {
  auto bases = get_bases();
  auto it    = begin(bases);
  for (auto _ : state) {
    auto x = ipow::ipow(*it, state.range(0));
    ++it;
    if (it == end(bases)) {
      it = begin(bases);
    }
    benchmark::DoNotOptimize(x);
  }
}
BENCHMARK(IPOW)->RangeMultiplier(2)->Range(0, 256);

BENCHMARK_MAIN();