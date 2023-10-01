#include "MustacheEntityBenchmarkSuite.h"

static ecs::benchmarks::mustache::MustacheEntityBenchmarkSuite benchmark_suite;

/// @FIXME: BM_RemoveAddComponent: Moving from archetype [[ecs::benchmarks::base::components::PositionComponent],
/// [ecs::benchmarks::base::components::VelocityComponent]] to itself
MINIMAL_ECS_ENTITY_BENCHMARKS(benchmark_suite)
// ECS_REMOVE_ENTITY_BENCHMARKS(benchmark_suite)
