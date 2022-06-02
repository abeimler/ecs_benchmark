#include "EntitasPPBenchmark.h"

#define STR(arg) #arg
#define XSTR(arg) STR(arg)

static ecs::benchmarks::EntitasPP::EntitasPPBenchmark entitaspp_benchmark({
                                                                         .add_more_complex_system = true,
                                                                         .version{},
                                                                 });

static void BM_entitaspp_ComplexSystemsUpdate(benchmark::State &state) {
    entitaspp_benchmark.BM_SystemsUpdate(state);
}

BENCHMARK(BM_entitaspp_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);