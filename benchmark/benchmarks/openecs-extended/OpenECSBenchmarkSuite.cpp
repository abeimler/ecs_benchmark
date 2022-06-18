#include "OpenECSBenchmarkSuite.h"

static ecs::benchmarks::openecs::OpenECSBenchmarkSuite benchmark_suite({
                                                                            .add_more_complex_system = true,
                                                                            .version = std::nullopt,
                                                                    });
/// @FIXME: SIGSEGV (Segmentation fault), can remove component(s) when createEntitiesWithMixedComponents
//ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
//ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)

static void BM_IterateSingleComponent(benchmark::State &state) {
    benchmark_suite.BM_IterateSingleComponent(state);
}
BENCHMARK(BM_IterateSingleComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_IterateTwoComponents(benchmark::State &state) {
    benchmark_suite.BM_IterateTwoComponents(state);
}
BENCHMARK(BM_IterateTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);
