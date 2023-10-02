#ifndef ECS_BENCHMARKS_ENTTPARTIALOWNINGGROUPBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTPARTIALOWNINGGROUPBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/EnttGroupApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

class EnttPartialOwningGroupBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (group, partial-owning)", EnttGroupApplication,
                                                         entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  EnttPartialOwningGroupBenchmarkSuite() = default;

  explicit EnttPartialOwningGroupBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsWithPreCreatedView(state, [](auto& registry) {
      return registry.template group<ComponentOne>(::entt::get<ComponentTwo>);
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, [](auto& registry) {
      return registry.template group<ComponentOne, ComponentTwo>(::entt::get<ComponentThree>);
    });
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTFULLOWNINGGROUPBENCHMARK_H_
