#include "MustacheBenchmark.h"

static ecs::benchmarks::mustache::MustacheBenchmark mustache_benchmark({
                                                                               .add_more_complex_system = true,
                                                                               .version = std::nullopt,
                                                                       });

static void BM_mustache_ComplexSystemsUpdate(benchmark::State &state) {
    mustache_benchmark.BM_SystemsUpdate(state);
}

BENCHMARK(BM_mustache_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);