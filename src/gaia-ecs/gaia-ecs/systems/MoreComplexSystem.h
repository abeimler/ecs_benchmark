#ifndef ECS_BENCHMARKS_GAIA_ECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_MORECOMPLEXSYSTEM_H_

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class MoreComplexSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::MoreComplexSystem<EntityManager, TimeDelta>;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::PositionComponent,
                   ecs::benchmarks::base::components::VelocityComponent&,
                   ecs::benchmarks::base::components::DataComponent&>();
  }

  void OnUpdate() override {
    //constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](const ecs::benchmarks::base::components::PositionComponent& position,
                 ecs::benchmarks::base::components::VelocityComponent& direction,
                 ecs::benchmarks::base::components::DataComponent& data) {
      BaseSystem::updateComponents(position, direction, data);
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
