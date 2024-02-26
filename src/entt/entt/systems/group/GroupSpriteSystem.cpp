#include "GroupSpriteSystem.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::entt::systems {

void GroupSpriteSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry
      .group<ecs::benchmarks::base::components::SpriteComponent>(
          ::entt::get<const ecs::benchmarks::base::components::PlayerComponent,
                      const ecs::benchmarks::base::components::HealthComponent>)
      .each([&](auto& spr, const auto& player, const auto& health) {
        updateSprite(spr, player, health);
      });
}

} // namespace ecs::benchmarks::entt::systems