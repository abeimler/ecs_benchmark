#include "SpriteSystem.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::entityx::systems {

void SpriteSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::SpriteComponent,
                const ecs::benchmarks::base::components::PlayerComponent,
                const ecs::benchmarks::base::components::HealthComponent>(
      [&](auto /*entity*/, auto& spr, const auto& player, const auto& health) {
        updateSprite(spr, player, health);
      });
}
void SpriteSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::SpriteComponent,
                const ecs::benchmarks::base::components::PlayerComponent,
                const ecs::benchmarks::base::components::HealthComponent>(
      [&](auto /*entity*/, auto& spr, const auto& player, const auto& health) {
        updateSprite(spr, player, health);
      });
}

} // namespace ecs::benchmarks::entityx::systems