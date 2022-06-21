#include "OpenECSBenchmarkSuite.h"

static ecs::benchmarks::openecs::OpenECSBenchmarkSuite benchmark_suite;

/// @FIXME: SIGSEGV (Segmentation fault), can remove component(s) when createEntitiesWithMixedComponents
static void BM_SystemsUpdate(benchmark::State &state) {
    benchmark_suite.BM_SystemsUpdate(state);
}
BENCHMARK(BM_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_SystemsUpdateMixedEntities(benchmark::State &state) {
    benchmark_suite.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
