#ifndef ECS_BENCHMARKS_GAIABENCHMARK_H_
#define ECS_BENCHMARKS_GAIABENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "gaia-ecs/GaiaEcsApplication.h"
#include "gaia-ecs/entities/EntityFactory.h"
#include "gaia-ecs/entities/HeroMonsterEntityFactory.h"
#include "gaia-ecs/systems/DataSystem.h"
#include "gaia-ecs/systems/MoreComplexSystem.h"
#include "gaia-ecs/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::gaia_ecs {

class GaiaEcsBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"gaia-ecs", GaiaEcsApplication, entities::EntityFactory,
                                                         entities::HeroMonsterEntityFactory> {
public:
  GaiaEcsBenchmarkSuite() = default;

  explicit GaiaEcsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentWithPreCreatedView(
        state,
        [](auto& world) {
          return world.query().template all<ComponentOne&>();
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
          return world.query().template all<ComponentOne&, ComponentTwo&>();
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
          return world.query().template all<ComponentOne&, ComponentTwo&, ComponentThree&>();
        },
        [&](ComponentOne& comp, ComponentTwo& comp2, ComponentThree& comp3) {
          dummy_each(comp, comp2, comp3);
        });
  }
};

} // namespace ecs::benchmarks::gaia_ecs

#endif
