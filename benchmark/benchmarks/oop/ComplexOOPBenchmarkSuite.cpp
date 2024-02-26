#include "OOPBenchmarkSuite.h"

static ecs::benchmarks::oop::OOPBenchmarkSuite benchmark_suite({
    .add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
    .version = std::nullopt,
});

static void BM_ComplexSystemsUpdate(benchmark::State& state) {
  benchmark_suite.BM_SystemsUpdate(state);
}
BENCHMARK(BM_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);
