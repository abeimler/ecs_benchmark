#include "MustacheBenchmarkSuite.h"

static ecs::benchmarks::mustache::MustacheBenchmarkSuite benchmark_suite({
    .add_more_complex_system = true,
    .version = std::nullopt,
});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)