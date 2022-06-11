#include "EntityPlusBenchmark.h"

static ecs::benchmarks::entityplus::EntityPlusBenchmark entityplus_benchmark({
                                                                   .add_more_complex_system = true,
                                                                   .version = std::nullopt
                                                           });


static void BM_entityplus_ComplexSystemsUpdate(benchmark::State &state) {
    entityplus_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entityplus_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_ComplexSystemsUpdateMixedEntities(benchmark::State &state) {
    entityplus_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_entityplus_ComplexSystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
