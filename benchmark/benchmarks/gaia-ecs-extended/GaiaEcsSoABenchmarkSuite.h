#ifndef ECS_BENCHMARKS_SOAGAIABENCHMARK_H_
#define ECS_BENCHMARKS_SOAGAIABENCHMARK_H_

#include "ExtendedECSBenchmark.h"
#include "base/components/DataComponent.h"
#include "gaia-ecs/SoAGaiaEcsApplication.h"
#include "gaia-ecs/entities/SoAEntityFactory.h"
#include "gaia-ecs/entities/SoAHeroMonsterEntityFactory.h"
#include <utility>

namespace ecs::benchmarks::gaia_ecs {

class GaiaEcsSoABenchmarkSuite final
    : public ecs::benchmarks::base::ExtendedECSBenchmark<
          "gaia-ecs (SoA)", SoAGaiaEcsApplication, entities::SoAEntityFactory, entities::SoAHeroMonsterEntityFactory> {
public:
  GaiaEcsSoABenchmarkSuite() = default;

  explicit GaiaEcsSoABenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ExtendedECSBenchmark(std::move(options)) {}

  void BM_IterateSingleComponent(benchmark::State& state) {
    using ComponentOne = components::SoAPositionComponent;

    BM_IterateSingleComponentWithPreCreatedView(
        state,
        [](auto& world) {
          return world.query().template all<ComponentOne&>();
        },
        [&](::gaia::ecs::Iter iter) {
          // Position
          auto vp = iter.view_mut<ComponentOne>();
          auto px = vp.set<0>();
          auto py = vp.set<1>();

          GAIA_EACH(iter) dummy_each(px[i], py[i]);
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
        [&](::gaia::ecs::Iter iter) {
          auto vp = iter.view_mut<ComponentOne>();
          auto px = vp.set<0>();
          auto py = vp.set<1>();

          auto vv = iter.view_mut<ComponentTwo>();
          auto vx = vv.set<0>();
          auto vy = vv.set<1>();

          GAIA_EACH(iter) dummy_each(px[i], vx[i]);
          GAIA_EACH(iter) dummy_each(py[i], vy[i]);
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
        [&](::gaia::ecs::Iter iter) {
          auto vp = iter.view_mut<ComponentOne>();
          auto px = vp.set<0>();
          auto py = vp.set<1>();

          auto vv = iter.view_mut<ComponentTwo>();
          auto vx = vv.set<0>();
          auto vy = vv.set<1>();

          auto vd = iter.view_mut<ComponentThree>();

          GAIA_EACH(iter) dummy_each(px[i], py[i], vx[i], vy[i], vd[i]);
        });
  }
};

} // namespace ecs::benchmarks::gaia_ecs

#endif
