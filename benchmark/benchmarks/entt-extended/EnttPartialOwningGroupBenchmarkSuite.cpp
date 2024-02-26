#include "EnttPartialOwningGroupBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttPartialOwningGroupBenchmarkSuite
    benchmark_suite({.add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
                     .version = ENTT_VERSION});

static void BM_IterateTwoComponents(benchmark::State& state) {
  benchmark_suite.BM_IterateTwoComponents(state);
}
BENCHMARK(BM_IterateTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_IterateThreeComponentsWithMixedEntities(state);
}
BENCHMARK(BM_IterateThreeComponentsWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
