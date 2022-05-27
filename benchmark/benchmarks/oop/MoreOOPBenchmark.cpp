#include "OOPBenchmark.h"

static ecs::benchmarks::oop::OOPBenchmark oop_benchmark({
                                                                .add_more_complex_system = true,
                                                                .version{},
                                                        });

static void BM_oop_ComplexSystemsUpdate(benchmark::State &state) {
    oop_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_oop_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);