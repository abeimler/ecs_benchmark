#include "EnttBenchmark.h"
#include "EnttRuntimeBenchmark.h"
#include "EnttGroupBenchmark.h"

static ecs::benchmarks::entt::EnttBenchmark entt_benchmark({
                                                                   .add_more_complex_system = true,
                                                                   .version = ENTT_VERSION
                                                           });
static ecs::benchmarks::entt::EnttRuntimeBenchmark entt_runtime_benchmark({
                                                                   .add_more_complex_system = true,
                                                                   .version = ENTT_VERSION
                                                           });
static ecs::benchmarks::entt::EnttGroupBenchmark entt_group_benchmark({
                                                                   .add_more_complex_system = true,
                                                                   .version = ENTT_VERSION
                                                           });

static void BM_entt_ComplexSystemsUpdate(benchmark::State &state) {
    entt_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_ComplexSystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_ComplexSystemsUpdateRuntime(benchmark::State &state) {
    entt_runtime_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_ComplexSystemsUpdateRuntime)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_ComplexSystemsUpdateGroup(benchmark::State &state) {
    entt_group_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_ComplexSystemsUpdateGroup)->Apply(ecs::benchmarks::base::BEDefaultArguments);