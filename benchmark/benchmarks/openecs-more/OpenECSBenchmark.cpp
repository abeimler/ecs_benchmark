#include "OpenECSBenchmark.h"

static ecs::benchmarks::openecs::OpenECSBenchmark openecs_benchmark({
                                                                            .add_more_complex_system = true,
                                                                            .version{},
                                                                    });


static void BM_openecs_ComplexSystemsUpdate(benchmark::State &state) {
    openecs_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_openecs_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);