#include "EnttGroupBenchmark.h"

static ecs::benchmarks::entt::EnttGroupBenchmark entt_group_benchmark({
                                                                   .add_more_complex_system = true,
                                                                   .version = ENTT_VERSION
                                                           });

static void BM_entt_ComplexSystemsUpdate(benchmark::State &state) {
    entt_group_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);
