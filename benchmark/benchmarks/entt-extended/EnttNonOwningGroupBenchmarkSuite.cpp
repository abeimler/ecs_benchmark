#include "EnttNonOwningGroupBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttNonOwningGroupBenchmarkSuite benchmark_suite({.add_more_complex_system = true,
                                                                                .version = ENTT_VERSION});

static void BM_IterateTwoComponents(benchmark::State& state) {
  benchmark_suite.BM_IterateTwoComponents(state);
}
BENCHMARK(BM_IterateTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_IterateThreeComponentsWithMixedEntities(state);
}
BENCHMARK(BM_IterateThreeComponentsWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
