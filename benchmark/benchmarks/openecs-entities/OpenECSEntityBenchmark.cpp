#include "OpenECSEntityBenchmark.h"

static ecs::benchmarks::openecs::OpenECSEntityBenchmarkSuite benchmark_suite;

static void BM_CreateEntities(benchmark::State &state) {
    benchmark_suite.BM_CreateEntities(state);
}
BENCHMARK(BM_CreateEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_CreateEmptyEntities(benchmark::State &state) {
    benchmark_suite.BM_CreateEmptyEntities(state);
}
BENCHMARK(BM_CreateEmptyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

/// @FIXME: can't remove_all_components
//static void BM_DestroyEntities(benchmark::State &state) {
//    benchmark_suite.BM_DestroyEntities(state);
//}
//BENCHMARK(BM_DestroyEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

/// @FIXME: can't get_component
//static void BM_UnpackOneComponent(benchmark::State &state) {
//    benchmark_suite.BM_UnpackOneComponent(state);
//}
//BENCHMARK(BM_UnpackOneComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);

//static void BM_UnpackOneConstComponent(benchmark::State &state) {
//    benchmark_suite.BM_UnpackOneConstComponent(state);
//}
//BENCHMARK(BM_UnpackOneConstComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);

//static void BM_UnpackTwoComponents(benchmark::State &state) {
//    benchmark_suite.BM_UnpackTwoComponents(state);
//}
//BENCHMARK(BM_UnpackTwoComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);

//static void BM_UnpackThreeComponents(benchmark::State &state) {
//    benchmark_suite.BM_UnpackThreeComponents(state);
//}
//BENCHMARK(BM_UnpackThreeComponents)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_RemoveAddComponent(benchmark::State& state) {
    benchmark_suite.BM_RemoveAddComponent(state);
}
BENCHMARK(BM_RemoveAddComponent)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_CreateEntitiesInBulk(benchmark::State &state) {
    benchmark_suite.BM_CreateEntitiesInBulk(state);
}
BENCHMARK(BM_CreateEntitiesInBulk)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_CreateEmptyEntitiesInBulk(benchmark::State &state) {
    benchmark_suite.BM_CreateEmptyEntitiesInBulk(state);
}
BENCHMARK(BM_CreateEmptyEntitiesInBulk)->Apply(ecs::benchmarks::base::BEDefaultArguments);