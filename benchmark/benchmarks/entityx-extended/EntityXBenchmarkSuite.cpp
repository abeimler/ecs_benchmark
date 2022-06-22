#include "EntityXBenchmarkSuite.h"

static ecs::benchmarks::entityx::EntityXBenchmarkSuite benchmark_suite({
                                                                         .add_more_complex_system = true,
                                                                         .version = ENTITYX_VERSION
                                                                 });

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)

