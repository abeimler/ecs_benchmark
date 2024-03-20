#include "EnttEventComponentBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttEventComponentBenchmarkSuite
    benchmark_suite({.add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
                     .version = ENTT_VERSION});

static void BM_PublishAndUpdateEventsViaComponentWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_PublishAndUpdateEventsViaComponentWithMixedEntities(state);
}
BENCHMARK(BM_PublishAndUpdateEventsViaComponentWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_PublishEventsViaComponentWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_PublishEventsViaComponentWithMixedEntities(state);
}
BENCHMARK(BM_PublishEventsViaComponentWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
