#include "OOPBenchmarkSuite.h"

static ecs::benchmarks::oop::OOPBenchmarkSuite benchmark_suite({
                                                                .add_more_complex_system = false,
                                                                .version{},
                                                        });

static void BM_SystemsUpdate(benchmark::State &state) {
    benchmark_suite.BM_SystemsUpdate(state);
}
BENCHMARK(BM_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);
