#include "EnttGroupBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttGroupBenchmarkSuite entt_group_benchmark(
    {.add_more_complex_system = ecs::benchmarks::base::add_more_complex_system_t::UseMoreComplexSystems,
     .version = ENTT_VERSION});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(entt_group_benchmark)
