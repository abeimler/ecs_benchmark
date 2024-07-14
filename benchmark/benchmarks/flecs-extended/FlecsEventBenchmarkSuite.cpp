#include "FlecsEventBenchmarkSuite.h"

static ecs::benchmarks::flecs::FlecsEventBenchmarkSuite benchmark_suite({
    .add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
    .version = std::nullopt,
});

static void BM_EnqueueAndUpdateEventsViaObserverWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_EnqueueAndUpdateEventsViaObserverWithMixedEntities(state);
}
BENCHMARK(BM_EnqueueAndUpdateEventsViaObserverWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);