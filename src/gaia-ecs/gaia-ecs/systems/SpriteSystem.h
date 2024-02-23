#ifndef ECS_BENCHMARKS_GAIA_ECS_SPRITESYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_SPRITESYSTEM_H_

#include "base/systems/SpriteSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class SpriteSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::SpriteSystem<EntityManager, TimeDelta>;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::SpriteComponent&,
                   ecs::benchmarks::base::components::PlayerComponent,
                   ecs::benchmarks::base::components::HealthComponent>();
  }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](ecs::benchmarks::base::components::SpriteComponent& spr,
                 const ecs::benchmarks::base::components::PlayerComponent& player,
                 const ecs::benchmarks::base::components::HealthComponent& health) {
      BaseSystem::updateSprite(spr, player, health);
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
