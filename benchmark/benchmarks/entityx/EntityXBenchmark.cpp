#include "EntityXBenchmark.h"

#define STR(arg) #arg
#define XSTR(arg) STR(arg)

static ecs::benchmarks::entityx::EnttBenchmark entityx_benchmark({
                                                                         .version = XSTR(ENTITYX_VERSION)
                                                                 });

static void BM_entityx_CreateEntities(benchmark::State &state) {
    entityx_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_entityx_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_entityx_DestroyEntities(benchmark::State &state) {
    entityx_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_entityx_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_UnpackOneComponent(benchmark::State &state) {
    entityx_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_entityx_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_UnpackOneComponentConst(benchmark::State &state) {
    entityx_benchmark.BM_UnpackOneComponentConst(state);
}
BENCHMARK(BM_entityx_UnpackOneComponentConst)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_UnpackTwoComponents(benchmark::State &state) {
    entityx_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_entityx_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    entityx_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entityx_UnpackTwoComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    entityx_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_entityx_UnpackThreeComponentsFromMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_SystemsUpdate(benchmark::State &state) {
    entityx_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entityx_SystemsUpdate)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_RemoveAddComponent(benchmark::State& state) {
    entityx_benchmark.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_entityx_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);


static void BM_entityx_SystemsUpdateMixedEntities(benchmark::State &state) {
    entityx_benchmark.BM_SystemsUpdateMixedEntities(state);
}
BENCHMARK(BM_entityx_SystemsUpdateMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);