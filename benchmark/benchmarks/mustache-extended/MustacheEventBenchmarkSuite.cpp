#include "MustacheEventBenchmarkSuite.h"

static ecs::benchmarks::mustache::MustacheEventBenchmarkSuite benchmark_suite({
    .add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
    .version = std::nullopt,
});

static void BM_PostAndUpdateEventsViaReceiverWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_PostAndUpdateEventsViaReceiverWithMixedEntities(state);
}
BENCHMARK(BM_PostAndUpdateEventsViaReceiverWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);