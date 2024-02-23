#include "SpriteSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

void SpriteSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry
      .view<ecs::benchmarks::base::components::SpriteComponent,
            const ecs::benchmarks::base::components::PlayerComponent,
            const ecs::benchmarks::base::components::HealthComponent>()
      .each([&](auto& spr, const auto& player, const auto& health) {
        updateSprite(spr, player, health);
      });
}

} // namespace ecs::benchmarks::entt::systems