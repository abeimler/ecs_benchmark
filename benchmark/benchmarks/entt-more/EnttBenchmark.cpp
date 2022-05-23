#include "EnttBenchmark.h"

static ecs::benchmarks::entt::EnttBenchmark entt_benchmark ({
    .add_more_complex_system = true,
    .version = ENTT_VERSION
});

static void BM_entt_ComplexSystemsUpdate(benchmark::State& state) {
    entt_benchmark.BM_SystemsUpdate(state);
}
BENCHMARK(BM_entt_ComplexSystemsUpdate)
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
        ->Arg(50'000);