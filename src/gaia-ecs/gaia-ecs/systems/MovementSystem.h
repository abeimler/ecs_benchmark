#ifndef ECS_BENCHMARKS_GAIA_ECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_MOVEMENTSYSTEM_H_

#include "base/systems/MovementSystem.h"
#include <gaia.h>
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::gaia_ecs::systems {

class MovementSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::MovementSystem<EntityManager, TimeDelta>;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::PositionComponent&,
                   ecs::benchmarks::base::components::VelocityComponent>();
  }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](ecs::benchmarks::base::components::PositionComponent& position,
                 const ecs::benchmarks::base::components::VelocityComponent& direction) {
      BaseSystem::updatePosition(position, direction, dt);
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
