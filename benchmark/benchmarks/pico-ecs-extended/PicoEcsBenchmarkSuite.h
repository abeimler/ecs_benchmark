#ifndef ECS_BENCHMARKS_PICOECSBENCHMARK_H_
#define ECS_BENCHMARKS_PICOECSBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "pico_ecs/PicoEcsApplication.h"
#include "pico_ecs/entities/EntityFactory.h"
#include "pico_ecs/systems/DataSystem.h"
#include "pico_ecs/systems/MoreComplexSystem.h"
#include "pico_ecs/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::pico_ecs {

class PicoEcsBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"pico_ecs", PicoEcsApplication, entities::EntityFactory> {
public:
  PicoEcsBenchmarkSuite() = default;

  explicit PicoEcsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  /// @TODO: foreach stand-alone components
  /*
  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentCustom(state, [](auto& entities) {
    });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsCustom(state, [](auto& entities) {
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [](auto& entities) {
    });
  }
  */
};

} // namespace ecs::benchmarks::pico_ecs

#endif // ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
