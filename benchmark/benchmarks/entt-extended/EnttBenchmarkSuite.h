#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/EnttApplication.h"
#include "entt/entities/EntityFactory.h"
#include "entt/entities/HeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

class EnttBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt", EnttApplication, entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  EnttBenchmarkSuite() = default;

  explicit EnttBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentCustom(state, [](auto& registry) {
      auto& storage = registry.template storage<ComponentOne>();
      std::for_each(storage.begin(), storage.end(), [](auto& comp) {
        dummy_each(comp);
      });
    });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsWithPreCreatedView(state, [](auto& registry) {
      return registry.template view<ComponentOne, ComponentTwo>();
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, [](auto& registry) {
      return registry.template view<ComponentOne, ComponentTwo, ComponentThree>();
    });
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTBENCHMARK_H_
