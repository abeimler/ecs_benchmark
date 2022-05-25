#include "OpenECSBenchmark.h"

static ecs::benchmarks::openecs::OpenECSBenchmark openecs_benchmark({
                                                                            .add_more_complex_system = true,
                                                                            .version{},
                                                                    });

static void BM_openecs_CreateEntities(benchmark::State &state) {
    openecs_benchmark.BM_CreateEntities(state);
}

BENCHMARK(BM_openecs_CreateEntities)
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


static void BM_openecs_DestroyEntities(benchmark::State &state) {
    openecs_benchmark.BM_DestroyEntities(state);
}

BENCHMARK(BM_openecs_DestroyEntities)
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


static void BM_openecs_UnpackOneComponent(benchmark::State &state) {
    openecs_benchmark.BM_UnpackOneComponent(state);
}

BENCHMARK(BM_openecs_UnpackOneComponent)
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


static void BM_openecs_UnpackTwoComponents(benchmark::State &state) {
    openecs_benchmark.BM_UnpackTwoComponents(state);
}

BENCHMARK(BM_openecs_UnpackTwoComponents)
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


static void BM_openecs_UnpackTwoComponentsFromMixedEntities(benchmark::State &state) {
    openecs_benchmark.BM_UnpackTwoComponentsFromMixedEntities(state);
}

BENCHMARK(BM_openecs_UnpackTwoComponentsFromMixedEntities)
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


static void BM_openecs_UnpackThreeComponentsFromMixedEntities(benchmark::State &state) {
    openecs_benchmark.BM_UnpackThreeComponentsFromMixedEntities(state);
}

BENCHMARK(BM_openecs_UnpackThreeComponentsFromMixedEntities)
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


static void BM_openecs_SystemsUpdate(benchmark::State &state) {
    openecs_benchmark.BM_SystemsUpdate(state);
}

BENCHMARK(BM_openecs_SystemsUpdate)
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