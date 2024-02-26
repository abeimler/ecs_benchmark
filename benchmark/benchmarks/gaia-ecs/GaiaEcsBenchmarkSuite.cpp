#include "GaiaEcsBenchmarkSuite.h"

static ecs::benchmarks::gaia_ecs::GaiaEcsBenchmarkSuite benchmark_suite({.version = GAIA_VERSION});

ECS_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
