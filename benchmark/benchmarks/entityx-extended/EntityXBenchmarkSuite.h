#ifndef ECS_BENCHMARKS_ENTITYXBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITYXBENCHMARK_H_

#include "entityx/EntityXApplication.h"
#include "entityx/entities/EntityFactory.h"
#include "entityx/entities/HeroMonsterEntityFactory.h"
#include "entityx/systems/DataSystem.h"
#include "entityx/systems/MoreComplexSystem.h"
#include "entityx/systems/MovementSystem.h"
#include <utility>

#include "ExtendedECSBenchmark.h"


#define STR(arg) #arg
#define XSTR(arg) STR(arg)
#define ENTITYX_VERSION XSTR(ENTITYX_MAJOR_VERSION) "." XSTR(ENTITYX_MINOR_VERSION) "." XSTR(ENTITYX_PATCH_VERSION)

namespace ecs::benchmarks::entityx {

class EntityXBenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<"entityx", EntityXApplication,
                                                         entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  EntityXBenchmarkSuite() = default;

  explicit EntityXBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}


  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;

    BM_IterateSingleComponentCustom(state, [](auto& es) {
      es.template each<ComponentOne>([](::entityx::Entity /*entity*/, ComponentOne& comp) {
        dummy_each(comp);
      });
    });
  }

  void BM_IterateTwoComponents(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;

    BM_IterateTwoComponentsCustom(state, [](auto& es) {
      es.template each<ComponentOne, ComponentTwo>(
          [](::entityx::Entity /*entity*/, ComponentOne& comp, ComponentTwo& comp2) {
            dummy_each(comp, comp2);
          });
    });
  }

  void BM_IterateThreeComponentsWithMixedEntities(benchmark::State& state) {
    using ComponentOne = ecs::benchmarks::base::components::PositionComponent;
    using ComponentTwo = ecs::benchmarks::base::components::VelocityComponent;
    using ComponentThree = ecs::benchmarks::base::components::DataComponent;

    BM_IterateThreeComponentsWithMixedEntitiesCustom(state, [](auto& es) {
      es.template each<ComponentOne, ComponentTwo, ComponentThree>(
          [](::entityx::Entity /*entity*/, ComponentOne& comp, ComponentTwo& comp2, ComponentThree& comp3) {
            dummy_each(comp, comp2, comp3);
          });
    });
  }
};

} // namespace ecs::benchmarks::entityx

#endif // ECS_BENCHMARKS_ENTITYXBENCHMARK_H_
