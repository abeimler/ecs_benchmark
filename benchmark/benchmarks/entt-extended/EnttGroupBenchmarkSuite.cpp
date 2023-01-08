#include "EnttGroupBenchmarkSuite.h"

static ecs::benchmarks::entt::EnttGroupBenchmarkSuite entt_group_benchmark({.add_more_complex_system = true,
                                                                            .version = ENTT_VERSION});

ECS_COMPLEX_UPDATE_SYSTEMS_BENCHMARKS(entt_group_benchmark)
