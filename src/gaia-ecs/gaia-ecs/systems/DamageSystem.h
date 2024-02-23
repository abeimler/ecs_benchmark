#ifndef ECS_BENCHMARKS_GAIA_ECS_DAMAGE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_DAMAGE_MORECOMPLEXSYSTEM_H_

#include "base/systems/DamageSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class DamageSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::DamageSystem<EntityManager, TimeDelta>;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::HealthComponent&,
                   ecs::benchmarks::base::components::DamageComponent>();
  }
  void OnUpdate() override {
    // constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](ecs::benchmarks::base::components::HealthComponent& health,
                 const ecs::benchmarks::base::components::DamageComponent& damage) {
      BaseSystem::updateDamage(health, damage);
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
