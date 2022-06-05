#include "EnttRuntimeBenchmark.h"

static ecs::benchmarks::entt::EnttRuntimeBenchmark entt_runtime_benchmark({
                                                                   .add_more_complex_system = true,
                                                                   .version = ENTT_VERSION
                                                           });

static void BM_entt_ComplexSystemsUpdate(benchmark::State &state) {
    entt_runtime_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);