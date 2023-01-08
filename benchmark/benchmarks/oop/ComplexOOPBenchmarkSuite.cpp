#include "OOPBenchmarkSuite.h"

static ecs::benchmarks::oop::OOPBenchmarkSuite benchmark_suite({
    .add_more_complex_system = true,
    .version{},
});

static void BM_ComplexSystemsUpdate(benchmark::State& state) {
  benchmark_suite.BM_SystemsUpdate(state);
}
BENCHMARK(BM_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);
