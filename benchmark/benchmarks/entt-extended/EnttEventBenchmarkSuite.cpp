#include "EnttEventBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttEventBenchmarkSuite
    benchmark_suite({.add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
                     .version = ENTT_VERSION});

static void BM_EnqueueAndUpdateEventsViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_EnqueueAndUpdateEventsViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_EnqueueAndUpdateEventsViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_EnqueueEventsViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_EnqueueEventsViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_EnqueueEventsViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_UpdateEventsViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_UpdateEventsViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_UpdateEventsViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
