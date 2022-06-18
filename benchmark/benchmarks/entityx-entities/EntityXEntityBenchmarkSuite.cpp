#include "EntityXEntityBenchmarkSuite.h"

static ecs::benchmarks::entityx::EntityXEntityBenchmarkSuite benchmark_suite({.version = ENTITYX_VERSION});

ECS_ENTITY_BENCHMARKS(benchmark_suite)
