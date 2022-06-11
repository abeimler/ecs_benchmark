#include "FlecsBenchmark.h"

static ecs::benchmarks::flecs::FlecsBenchmark flecs_benchmark ({
                                                                       .add_more_complex_system = true,
                                                                       .version = std::nullopt,
                                                               });

static void BM_flecs_ComplexSystemsUpdate(benchmark::State &state) {
    flecs_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_flecs_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_ComplexSystemsUpdateMixedEntities(benchmark::State &state) {
    flecs_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_flecs_ComplexSystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);