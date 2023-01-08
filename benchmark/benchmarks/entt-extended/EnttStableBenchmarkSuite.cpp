#include "EnttStableBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttStableBenchmarkSuite benchmark_suite({.add_more_complex_system = true,
                                                                        .version = ENTT_VERSION});


ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)
