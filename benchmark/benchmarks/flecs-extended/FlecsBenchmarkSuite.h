#ifndef ECS_BENCHMARKS_FLECSBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "flecs/FlecsApplication.h"
#include "flecs/entities/EntityFactory.h"
#include "flecs/systems/DataSystem.h"
#include "flecs/systems/MoreComplexSystem.h"
#include "flecs/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::flecs {

class FlecsBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"flecs", FlecsApplication, entities::EntityFactory> {
public:
  FlecsBenchmarkSuite() = default;

  explicit FlecsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentWithPreCreatedView(
        state,
        [](auto& world) {
          return world.template query<ComponentOne>();
        },
        [&](ComponentOne& comp) {
          dummy_each(comp);
        });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsWithPreCreatedView(
        state,
        [](auto& world) {
          return world.template query<ComponentOne, ComponentTwo>();
        },
        [&](ComponentOne& comp, ComponentTwo& comp2) {
          dummy_each(comp, comp2);
        });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesAndPreCreatedView(
        state,
        [](auto& world) {
          return world.template query<ComponentOne, ComponentTwo, ComponentThree>();
        },
        [&](ComponentOne& comp, ComponentTwo& comp2, ComponentThree& comp3) {
          dummy_each(comp, comp2, comp3);
        });
  }
};

} // namespace ecs::benchmarks::flecs

#endif // ECS_BENCHMARKS_FLECSBENCHMARK_H_
