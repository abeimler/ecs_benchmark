#include "GaiaEcsSoABenchmarkSuite.h"

static ecs::benchmarks::gaia_ecs::GaiaEcsSoABenchmarkSuite soa_benchmark_suite({
    .add_more_complex_system = true,
    .version = std::nullopt,
});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(soa_benchmark_suite)
//ECS_ITERATE_COMPONENTS_BENCHMARKS(soa_benchmark_suite)
