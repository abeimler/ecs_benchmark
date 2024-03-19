#include "EnttBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttBenchmarkSuite
    benchmark_suite({.add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
                     .version = ENTT_VERSION});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(benchmark_suite)
ECS_ITERATE_COMPONENTS_BENCHMARKS(benchmark_suite)

static void BM_PublishEventAndProgressEventViaComponentWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_PublishEventAndProgressEventViaComponentWithMixedEntities(state);
}
BENCHMARK(BM_PublishEventAndProgressEventViaComponentWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_PublishEventAndProgressEventViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_PublishEventAndProgressEventViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_PublishEventAndProgressEventViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_PublishEventViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_PublishEventAndProgressEventViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_PublishEventViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);

static void BM_EnqueueEventViaDispatcherWithMixedEntities(benchmark::State& state) {
  benchmark_suite.BM_EnqueueEventViaDispatcherWithMixedEntities(state);
}
BENCHMARK(BM_EnqueueEventViaDispatcherWithMixedEntities)->Apply(ecs::benchmarks::base::BEDefaultArguments);