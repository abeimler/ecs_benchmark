#include "FlecsEventEmitBenchmarkSuite.h"

static ecs::benchmarks::flecs::FlecsEventBenchmarkSuite benchmark_suite({
    .add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
    .version = std::nullopt,
});

static void BM_EmitAndUpdateEventsViaObserverWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_EmitAndUpdateEventsViaObserverWithMixedEntities(state);
}
BENCHMARK(BM_EmitAndUpdateEventsViaObserverWithMixedEntities)->Apply(ecs::benchmarks::base::BESmallArguments);
/// @NOTE: BEDefaultArguments takes to long