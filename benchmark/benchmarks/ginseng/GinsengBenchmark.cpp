#include "GinsengBenchmark.h"

static ecs::benchmarks::ginseng::GinsengBenchmark ginseng_benchmark;

static void BM_ginseng_CreateEntities(benchmark::State &state) {
    ginseng_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_ginseng_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_ginseng_DestroyEntities(benchmark::State &state) {
    ginseng_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_ginseng_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_ginseng_UnpackOneComponent(benchmark::State &state) {
    ginseng_benchmark.BM_UnpackOneComponent(state);
}

BENCHMARK(BM_ginseng_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_ginseng_UnpackTwoComponents(benchmark::State &state) {
    ginseng_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_ginseng_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_ginseng_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    ginseng_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_ginseng_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_ginseng_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    ginseng_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_ginseng_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_ginseng_SystemsUpdate(benchmark::State &state) {
    ginseng_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_ginseng_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);