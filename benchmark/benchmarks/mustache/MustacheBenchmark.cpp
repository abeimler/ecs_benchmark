#include "MustacheBenchmark.h"

static ecs::benchmarks::mustache::MustacheBenchmark mustache_benchmark;

static void BM_mustache_CreateEntities(benchmark::State &state) {
    mustache_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_mustache_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_DestroyEntities(benchmark::State &state) {
    mustache_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_mustache_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_UnpackOneComponent(benchmark::State &state) {
    mustache_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_mustache_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_UnpackOneComponentConst(benchmark::State &state) {
    mustache_benchmark.BM_UnpackOneComponentConst(state);
}
BENCHMARK(BM_mustache_UnpackOneComponentConst)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_UnpackTwoComponents(benchmark::State &state) {
    mustache_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_mustache_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    mustache_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_mustache_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    mustache_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_mustache_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_SystemsUpdate(benchmark::State &state) {
    mustache_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_mustache_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_RemoveAddComponent(benchmark::State& state) {
    mustache_benchmark.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_mustache_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_mustache_SystemsUpdateMixedEntities(benchmark::State &state) {
    mustache_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_mustache_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);
