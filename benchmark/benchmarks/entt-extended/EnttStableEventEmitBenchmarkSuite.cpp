#include "EnttStableEventEmitBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttStableEventEmitBenchmarkSuite
    benchmark_suite({.add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
                     .version = ENTT_VERSION});

static void BM_TriggerAndUpdateEventsViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_TriggerAndUpdateEventsViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_TriggerAndUpdateEventsViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
