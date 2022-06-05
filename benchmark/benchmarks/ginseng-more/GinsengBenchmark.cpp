#include "GinsengBenchmark.h"

static ecs::benchmarks::ginseng::GinsengBenchmark ginseng_benchmark({
                                                                            .add_more_complex_system = true,
                                                                            .version = std::nullopt,
                                                                    });

static void BM_ginseng_ComplexSystemsUpdate(benchmark::State &state) {
    ginseng_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_ginseng_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);