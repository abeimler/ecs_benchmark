#include "OpenECSBenchmark.h"

static ecs::benchmarks::openecs::OpenECSBenchmark openecs_benchmark;

static void BM_openecs_CreateEntities(benchmark::State &state) {
    openecs_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_openecs_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_DestroyEntities(benchmark::State &state) {
    openecs_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_openecs_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_UnpackOneComponent(benchmark::State &state) {
    openecs_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_openecs_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_UnpackOneComponentConst(benchmark::State &state) {
    openecs_benchmark.BM_UnpackOneComponentConst(state);
}
BENCHMARK(BM_openecs_UnpackOneComponentConst)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_UnpackTwoComponents(benchmark::State &state) {
    openecs_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_openecs_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    openecs_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_openecs_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    openecs_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_openecs_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_SystemsUpdate(benchmark::State &state) {
    openecs_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_openecs_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_RemoveAddComponent(benchmark::State& state) {
    openecs_benchmark.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_openecs_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_openecs_SystemsUpdateMixedEntities(benchmark::State &state) {
    openecs_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_openecs_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);