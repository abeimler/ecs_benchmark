#ifndef ECS_BENCHMARKS_ENTTSTABLEBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTSTABLEBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "entt/StableEnttApplication.h"
#include "entt/entities/StableEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::entt {

class EnttStableBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (stable)", StableEnttApplication,
                                                         entities::StableEntityFactory> {
public:
  EnttStableBenchmarkSuite() = default;

  explicit EnttStableBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::entt::components::StablePositionComponent;

    BM_IterateSingleComponentCustom(state, [](auto& registry) {
      auto& storage = registry.template storage<ComponentOne>();
      std::for_each(storage.begin(), storage.end(), [](auto& comp) {
        dummy_each(comp);
      });
    });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::entt::components::StablePositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsWithPreCreatedView(state, [](auto& registry) {
      return registry.template view<ComponentOne, ComponentTwo>();
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::entt::components::StablePositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(state, [](auto& registry) {
      return registry.template view<ComponentOne, ComponentTwo, ComponentThree>();
    });
  }
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTSTABLEBENCHMARK_H_
