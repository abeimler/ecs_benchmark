#include "OpenECSBenchmarkSuite.h"

static ecs::benchmarks::openecs::OpenECSBenchmarkSuite benchmark_suite;

/// @FIXME: SIGSEGV (Segmentation fault), can remove component(s) when createEntitiesWithMixedComponents
//ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
