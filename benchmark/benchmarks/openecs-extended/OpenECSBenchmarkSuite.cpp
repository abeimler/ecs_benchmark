#include "OpenECSBenchmarkSuite.h"

static ecs::benchmarks::openecs::OpenECSBenchmarkSuite benchmark_suite({
    .add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
    .version = std::nullopt,
});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)
