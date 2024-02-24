#ifndef ECS_BENCHMARKS_BASICBENCHMARK_H_
#define ECS_BENCHMARKS_BASICBENCHMARK_H_

#include "base/Application.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace ecs::benchmarks::base {

template <size_t N>
struct StringLiteral {
  /*implicit*/ constexpr StringLiteral(const char (&str)[N]) {
    std::copy_n(str, N, value);
    value[N] = '\0';
  }

  char value[N + 1];
};

struct ESCBenchmarkOptions {
  add_more_complex_system_t add_more_complex_system{add_more_complex_system_t::UseBasicSystems};
  std::optional<std::string> version;
};

struct ComponentsCounter {
  size_t component_one_count{0};
  size_t component_two_count{0};
  size_t component_three_count{0};

  size_t hero_count{0};
  size_t monster_count{0};
};

inline static constexpr auto MIN_ENTITIES_RANGE = 8L;
inline static constexpr auto MAX_ENTITIES_RANGE = 2'097'152L;

void BEDefaultArguments(benchmark::internal::Benchmark* b);
} // namespace ecs::benchmarks::base

#endif // ECS_BENCHMARKS_BASICBENCHMARK_H_
