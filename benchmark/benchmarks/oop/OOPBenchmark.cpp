#include "OOPBenchmark.h"

static ecs::benchmarks::oop::OOPBenchmark oop_benchmark;

static void BM_oop_CreateEntities(benchmark::State &state) {
    oop_benchmark.BM_CreateEntities(state);
}

BENCHMARK(BM_oop_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_oop_DestroyEntities(benchmark::State &state) {
    oop_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_oop_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_oop_UnpackOneComponent(benchmark::State &state) {
    oop_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_oop_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_oop_UnpackTwoComponents(benchmark::State &state) {
    oop_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_oop_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_oop_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    oop_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_oop_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_oop_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    oop_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_oop_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_oop_SystemsUpdate(benchmark::State &state) {
    oop_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_oop_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);