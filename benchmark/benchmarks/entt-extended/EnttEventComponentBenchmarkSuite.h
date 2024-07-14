#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_EVENTCOMP_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_EVENTCOMP_H_

#include "ExtendedECSBenchmark.h"
#include "entt/EnttApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

class EnttEventComponentBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (component)", EnttApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  EnttEventComponentBenchmarkSuite() = default;

  explicit EnttEventComponentBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_PublishEventsViaComponentWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    //using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    BM_PublishEventsViaComponentWithMixedEntitiesViews(
        state,
        [](auto& registry) {
          return registry.template view<ComponentOne, ComponentTwo>();
        });
  }
  void BM_PublishAndUpdateEventsViaComponentWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using EventComponent = ecs::benchmarks::base::components::EmptyComponent;

    BM_PublishAndUpdateEventsViaComponentWithMixedEntitiesViews(
      state,
      [](auto& registry) {
        return registry.template view<ComponentOne, ComponentTwo>();
      },
      [](auto& registry) {
        return registry.template view<ComponentOne, ComponentTwo, EventComponent>();
      });
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTBENCHMARK_H_
