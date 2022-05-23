#include "GinsengBenchmark.h"

static ecs::benchmarks::ginseng::GinsengBenchmark ginseng_benchmark ({
    .add_more_complex_system = true,
});

static void BM_ginseng_CreateEntities(benchmark::State& state) {
    ginseng_benchmark.BM_CreateEntities(state);
}
BENCHMARK(BM_ginseng_CreateEntities)
    ->Arg(10)
    ->Arg(25)
    ->Arg(50)
    ->Arg(100)
    ->Arg(200)
    ->Arg(400)
    ->Arg(800)
    ->Arg(1600)
    ->Arg(3200)
    ->Arg(5000)
    ->Arg(10'000)
    ->Arg(30'000)
    ->Arg(50'000)
    ->Arg(100'000)
    ->Arg(300'000)
    ->Arg(500'000)
    ->Arg(700'000)
    ->Arg(1'000'000);


static void BM_ginseng_DestroyEntities(benchmark::State& state) {
    ginseng_benchmark.BM_DestroyEntities(state);
}
BENCHMARK(BM_ginseng_DestroyEntities)
        ->Arg(10)
        ->Arg(25)
        ->Arg(50)
        ->Arg(100)
        ->Arg(200)
        ->Arg(400)
        ->Arg(800)
        ->Arg(1600)
        ->Arg(3200)
        ->Arg(5000)
        ->Arg(10'000)
        ->Arg(30'000)
        ->Arg(50'000)
        ->Arg(100'000)
        ->Arg(300'000)
        ->Arg(500'000);



static void BM_ginseng_UnpackOneComponent(benchmark::State& state) {
    ginseng_benchmark.BM_UnpackOneComponent(state);
}
BENCHMARK(BM_ginseng_UnpackOneComponent)
        ->Arg(10)
        ->Arg(25)
        ->Arg(50)
        ->Arg(100)
        ->Arg(200)
        ->Arg(400)
        ->Arg(800)
        ->Arg(1600)
        ->Arg(3200)
        ->Arg(5000)
        ->Arg(10'000)
        ->Arg(30'000)
        ->Arg(50'000)
        ->Arg(100'000)
        ->Arg(300'000)
        ->Arg(500'000)
        ->Arg(700'000)
        ->Arg(1'000'000);


static void BM_ginseng_UnpackTwoComponents(benchmark::State& state) {
    ginseng_benchmark.BM_UnpackTwoComponents(state);
}
BENCHMARK(BM_ginseng_UnpackTwoComponents)
        ->Arg(10)
        ->Arg(25)
        ->Arg(50)
        ->Arg(100)
        ->Arg(200)
        ->Arg(400)
        ->Arg(800)
        ->Arg(1600)
        ->Arg(3200)
        ->Arg(5000)
        ->Arg(10'000)
        ->Arg(30'000)
        ->Arg(50'000)
        ->Arg(100'000)
        ->Arg(300'000)
        ->Arg(500'000)
        ->Arg(700'000)
        ->Arg(1'000'000);


static void BM_ginseng_UnpackTwoComponentsFromMixedEntities(benchmark::State& state) {
    ginseng_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}
BENCHMARK(BM_ginseng_UnpackTwoComponentsFromMixedEntities)
        ->Arg(10)
        ->Arg(25)
        ->Arg(50)
        ->Arg(100)
        ->Arg(200)
        ->Arg(400)
        ->Arg(800)
        ->Arg(1600)
        ->Arg(3200)
        ->Arg(5000)
        ->Arg(10'000)
        ->Arg(30'000)
        ->Arg(50'000)
        ->Arg(100'000)
        ->Arg(300'000)
        ->Arg(500'000)
        ->Arg(700'000)
        ->Arg(1'000'000);


static void BM_ginseng_UnpackThreeComponentsFromMixedEntities(benchmark::State& state) {
    ginseng_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}
BENCHMARK(BM_ginseng_UnpackThreeComponentsFromMixedEntities)
        ->Arg(10)
        ->Arg(25)
        ->Arg(50)
        ->Arg(100)
        ->Arg(200)
        ->Arg(400)
        ->Arg(800)
        ->Arg(1600)
        ->Arg(3200)
        ->Arg(5000)
        ->Arg(10'000)
        ->Arg(30'000)
        ->Arg(50'000)
        ->Arg(100'000)
        ->Arg(300'000)
        ->Arg(500'000)
        ->Arg(700'000)
        ->Arg(1'000'000);


static void BM_ginseng_SystemsUpdate(benchmark::State& state) {
    ginseng_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_ginseng_SystemsUpdate)
        ->Arg(10)
        ->Arg(25)
        ->Arg(50)
        ->Arg(100)
        ->Arg(200)
        ->Arg(400)
        ->Arg(800)
        ->Arg(1600)
        ->Arg(3200)
        ->Arg(5000)
        ->Arg(10'000)
        ->Arg(30'000)
        ->Arg(50'000)
        ->Arg(100'000)
        ->Arg(300'000)
        ->Arg(500'000)
        ->Arg(700'000)
        ->Arg(1'000'000);