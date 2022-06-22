#include "EntityXBenchmarkSuite.h"

static ecs::benchmarks::entityx::EntityXBenchmarkSuite benchmark_suite({.version = ENTITYX_VERSION});

ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)