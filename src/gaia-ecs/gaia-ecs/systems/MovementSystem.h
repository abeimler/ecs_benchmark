#ifndef ECS_BENCHMARKS_GAIA_ECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_MOVEMENTSYSTEM_H_

#include "base/systems/MovementSystem.h"
#include <gaia.h>
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::gaia_ecs::systems {

class MovementSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::PositionComponent&,
                   ecs::benchmarks::base::components::VelocityComponent>();
  }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](ecs::benchmarks::base::components::PositionComponent& position,
                 const ecs::benchmarks::base::components::VelocityComponent& direction) {
      position.x += direction.x * dt;
      position.y += direction.y * dt;
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
