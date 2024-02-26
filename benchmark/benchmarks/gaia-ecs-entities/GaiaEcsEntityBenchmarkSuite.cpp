#include "GaiaEcsEntityBenchmarkSuite.h"

static ecs::benchmarks::gaia_ecs::GaiaEcsEntityBenchmarkSuite benchmark_suite({.version = GAIA_VERSION});

ECS_ENTITY_BENCHMARKS(benchmark_suite)

/*
static void BM_CreateEntitiesInBulk(benchmark::State& state) {
  benchmark_suite.BM_CreateEntitiesInBulk(state);
}
BENCHMARK(BM_CreateEntitiesInBulk)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_CreateEmptyEntitiesInBulk(benchmark::State& state) {
  benchmark_suite.BM_CreateEmptyEntitiesInBulk(state);
}
BENCHMARK(BM_CreateEmptyEntitiesInBulk)->Apply(ecs::benchmarks::base::BEDefaultArguments);
*/