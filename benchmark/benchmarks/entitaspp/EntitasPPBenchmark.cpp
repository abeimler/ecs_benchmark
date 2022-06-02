#include "EntitasPPBenchmark.h"

static ecs::benchmarks::EntitasPP::EntitasPPBenchmark entitaspp_benchmark;

static void BM_entitaspp_CreateEntities(benchmark::State &state) {
    entitaspp_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_entitaspp_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_DestroyEntities(benchmark::State &state) {
    entitaspp_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_entitaspp_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_UnpackOneComponent(benchmark::State &state) {
    entitaspp_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_entitaspp_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_UnpackTwoComponents(benchmark::State &state) {
    entitaspp_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_entitaspp_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    entitaspp_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entitaspp_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    entitaspp_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entitaspp_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_SystemsUpdate(benchmark::State &state) {
    entitaspp_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entitaspp_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entitaspp_RemoveAddComponent(benchmark::State& state) {
    entitaspp_benchmark.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_entitaspp_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);