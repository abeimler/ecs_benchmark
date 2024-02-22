#ifndef ECS_BENCHMARKS_SOAGAIABENCHMARK_H_
#define ECS_BENCHMARKS_SOAGAIABENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "gaia-ecs/SoAGaiaEcsApplication.h"
#include "gaia-ecs/entities/HeroMonsterEntityFactory.h"
#include "gaia-ecs/entities/SoAEntityFactory.h"
#include "gaia-ecs/systems/DataSystem.h"
#include "gaia-ecs/systems/MoreComplexSystem.h"
#include "gaia-ecs/systems/SoAMoreComplexSystem.h"
#include "gaia-ecs/systems/SoAMovementSystem.h"
#include <utility>

namespace ecs::benchmarks::gaia_ecs {

class GaiaEcsSoABenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<
          "gaia-ecs (SoA)", SoAGaiaEcsApplication, entities::SoAEntityFactory, entities::HeroMonsterEntityFactory> {
public:
  GaiaEcsSoABenchmarkSuite() = default;

  explicit GaiaEcsSoABenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  /*
  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = components::SoAPositionComponent;

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
    using ComponentOne = components::SoAPositionComponent;
    using ComponentTwo = components::SoAVelocityComponent;

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
    using ComponentOne = components::SoAPositionComponent;
    using ComponentTwo = components::SoAVelocityComponent;
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
  */
};

} // namespace ecs::benchmarks::gaia_ecs

#endif
