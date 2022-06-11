#include "EntityXBenchmark.h"

#define STR(arg) #arg
#define XSTR(arg) STR(arg)

static ecs::benchmarks::entityx::EnttBenchmark entityx_benchmark({
                                                                         .add_more_complex_system = true,
                                                                         .version = XSTR(ENTITYX_VERSION)
                                                                 });

static void BM_entityx_ComplexSystemsUpdate(benchmark::State &state) {
    entityx_benchmark.BM_SystemsUpdate(state);
}

BENCHMARK(BM_entityx_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_ComplexSystemsUpdateMixedEntities(benchmark::State &state) {
    entityx_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_entityx_ComplexSystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);