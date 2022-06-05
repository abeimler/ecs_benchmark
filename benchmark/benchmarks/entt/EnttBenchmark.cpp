#include "EnttBenchmark.h"

static ecs::benchmarks::entt::EnttBenchmark entt_benchmark({
                                                                   .version = ENTT_VERSION
                                                           });

static void BM_entt_CreateEntities(benchmark::State &state) {
    entt_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_entt_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_DestroyEntities(benchmark::State &state) {
    entt_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_entt_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_UnpackOneComponent(benchmark::State &state) {
    entt_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_entt_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_UnpackOneComponentConst(benchmark::State &state) {
    entt_benchmark.BM_UnpackOneComponentConst(state);
}
BENCHMARK(BM_entt_UnpackOneComponentConst)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_UnpackTwoComponents(benchmark::State &state) {
    entt_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_entt_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    entt_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entt_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    entt_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entt_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_SystemsUpdate(benchmark::State &state) {
    entt_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entt_RemoveAddComponent(benchmark::State& state) {
    entt_benchmark.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_entt_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);