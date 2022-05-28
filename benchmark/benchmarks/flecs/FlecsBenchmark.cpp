#include "FlecsBenchmark.h"

static ecs::benchmarks::flecs::FlecsBenchmark flecs_benchmark;

static void BM_flecs_CreateEntities(benchmark::State &state) {
    flecs_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_flecs_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_DestroyEntities(benchmark::State &state) {
    flecs_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_flecs_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_UnpackOneComponent(benchmark::State &state) {
    flecs_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_flecs_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_UnpackTwoComponents(benchmark::State &state) {
    flecs_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_flecs_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    flecs_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_flecs_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    flecs_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_flecs_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_flecs_SystemsUpdate(benchmark::State &state) {
    flecs_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_flecs_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);