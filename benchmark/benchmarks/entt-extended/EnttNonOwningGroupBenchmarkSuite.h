#ifndef ECS_BENCHMARKS_ENTTNONOWNINGGROUPBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTNONOWNINGGROUPBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/EnttGroupApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

class EnttNonOwningGroupBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (group, non-owning)", EnttGroupApplication,
                                                         entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  EnttNonOwningGroupBenchmarkSuite() = default;

  explicit EnttNonOwningGroupBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsWithPreCreatedView(state, [](auto& registry) {
      return registry.template group<>(::entt::get<ComponentOne, ComponentTwo>);
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, [](auto& registry) {
      return registry.template group<>(::entt::get<ComponentOne, ComponentTwo, ComponentThree>);
    });
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTNONOWNINGGROUPBENCHMARK_H_
