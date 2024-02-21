#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAMOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAMOVEMENTSYSTEM_H_

#include "base/systems/MovementSystem.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include "gaia-ecs/components/SoAVelocityComponent.h"
#include <gaia.h>
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::gaia_ecs::systems {

class SoAMovementSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<components::SoAPositionComponent&,
                   components::SoAVelocityComponent>();
  }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](::gaia::ecs::Iter iter) {
      // Position
      auto vp = iter.view_mut<components::SoAPositionComponent>(); // read-write access to PositionSoA
      auto px = vp.set<0>(); // continuous block of "x" from PositionSoA
      auto py = vp.set<1>(); // continuous block of "y" from PositionSoA

      // Velocity
      auto vv = iter.view<components::SoAVelocityComponent>(); // read-only access to VelocitySoA
      auto vx = vv.get<0>(); // continuous block of "x" from VelocitySoA
      auto vy = vv.get<1>(); // continuous block of "y" from VelocitySoA

      // Handle x coordinates
      GAIA_EACH(iter) px[i] += vx[i] * dt;
      // Handle y coordinates
      GAIA_EACH(iter) py[i] += vy[i] * dt;
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
