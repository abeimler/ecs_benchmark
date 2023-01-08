#include "EnttBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttBenchmarkSuite benchmark_suite({.version = ENTT_VERSION});

ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
