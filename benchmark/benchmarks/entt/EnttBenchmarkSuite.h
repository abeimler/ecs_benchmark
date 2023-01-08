#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include "ECSBenchmark.h"
#include "entt/EnttApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/systems/DataSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/MovementSystem.h"
#include <utility>


namespace ecs::benchmarks::entt {

class EnttBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"entt", EnttApplication, entities::EntityFactory> {
public:
  EnttBenchmarkSuite() = default;

  explicit EnttBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTBENCHMARK_H_
