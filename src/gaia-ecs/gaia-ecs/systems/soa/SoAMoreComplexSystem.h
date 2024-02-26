#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAMORECOMPLEXSYSTEM_H_

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include "gaia-ecs/components/SoAVelocityComponent.h"
#include <gaia.h>
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::gaia_ecs::systems {

class SoAMoreComplexSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::MoreComplexSystem<EntityManager, TimeDelta>;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<components::SoAPositionComponent, components::SoAVelocityComponent&,
                   ecs::benchmarks::base::components::DataComponent&>();
  }

  void OnUpdate() override {
    // constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](::gaia::ecs::Iter iter) {
      // Position
      auto vp = iter.view<components::SoAPositionComponent>(); // read-only access to PositionSoA
      auto px = vp.get<0>();                                   // continuous block of "x" from PositionSoA
      auto py = vp.get<1>();                                   // continuous block of "y" from PositionSoA

      // Velocity
      auto vv = iter.view_mut<components::SoAVelocityComponent>(); // read-write access to VelocitySoA
      auto vx = vv.set<0>();                                       // continuous block of "x" from VelocitySoA
      auto vy = vv.set<1>();                                       // continuous block of "y" from VelocitySoA

      // Data
      auto vd = iter.view_mut<ecs::benchmarks::base::components::DataComponent>();

      GAIA_EACH(iter) {
        /// @Note: code copied from MoreComplexSystem::updateComponents
        if ((vd[i].thingy % 10) == 0) {
          if (px[i] > py[i]) {
            vx[i] = gsl::narrow_cast<float>(vd[i].rng.range(3, 19)) - 10.0F;
            vy[i] = gsl::narrow_cast<float>(vd[i].rng.range(0, 5));
          } else {
            vx[i] = gsl::narrow_cast<float>(vd[i].rng.range(0, 5));
            vy[i] = gsl::narrow_cast<float>(vd[i].rng.range(3, 19)) - 10.0F;
          }
        }
      }
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
