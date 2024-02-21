#include "GaiaEcsBenchmarkSuite.h"

static ecs::benchmarks::gaia_ecs::GaiaEcsBenchmarkSuite benchmark_suite({
    .add_more_complex_system = true,
    .version = std::nullopt,
});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)
