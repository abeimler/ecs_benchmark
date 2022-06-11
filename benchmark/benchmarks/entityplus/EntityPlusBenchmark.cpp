#include "EntityPlusBenchmark.h"

static ecs::benchmarks::entityplus::EntityPlusBenchmark entityplus_benchmark;

static void BM_entityplus_CreateEntities(benchmark::State &state) {
    entityplus_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_entityplus_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_DestroyEntities(benchmark::State &state) {
    entityplus_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_entityplus_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_UnpackOneComponent(benchmark::State &state) {
    entityplus_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_entityplus_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_UnpackOneComponentConst(benchmark::State &state) {
    entityplus_benchmark.BM_UnpackOneComponentConst(state);
}
BENCHMARK(BM_entityplus_UnpackOneComponentConst)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_UnpackTwoComponents(benchmark::State &state) {
    entityplus_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_entityplus_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    entityplus_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entityplus_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    entityplus_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entityplus_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_SystemsUpdate(benchmark::State &state) {
    entityplus_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entityplus_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_RemoveAddComponent(benchmark::State& state) {
    entityplus_benchmark.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_entityplus_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityplus_SystemsUpdateMixedEntities(benchmark::State &state) {
    entityplus_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_entityplus_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);