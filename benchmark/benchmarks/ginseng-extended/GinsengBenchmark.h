#ifndef ECS_BENCHMARKS_GINSENGBENCHMARK_H_
#define ECS_BENCHMARKS_GINSENGBENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "ginseng/GinsengApplication.h"
#include "ginseng/entities/EntityFactory.h"
#include "ginseng/entities/HeroMonsterEntityFactory.h"
#include "ginseng/systems/DataSystem.h"
#include "ginseng/systems/MoreComplexSystem.h"
#include "ginseng/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::ginseng {

class GinsengBenchmark final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"ginseng", GinsengApplication,
                                                         entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  GinsengBenchmark() = default;

  explicit GinsengBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentCustom(state, [](auto& ent_db) {
      ent_db.visit([](ComponentOne& comp) {
        dummy_each(comp);
      });
    });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsCustom(state, [](auto& ent_db) {
      ent_db.visit([](ComponentOne& comp, ComponentTwo& comp2) {
        dummy_each(comp, comp2);
      });
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [](auto& ent_db) {
      ent_db.visit([](ComponentOne& comp, ComponentTwo& comp2, ComponentThree& comp3) {
        dummy_each(comp, comp2, comp3);
      });
    });
  }
};

} // namespace ecs::benchmarks::ginseng

#endif // ECS_BENCHMARKS_ENTTBENCHMARK_H_
