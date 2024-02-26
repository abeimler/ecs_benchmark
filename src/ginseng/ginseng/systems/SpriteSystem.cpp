#include "SpriteSystem.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::ginseng::systems {

void SpriteSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.visit([&](ecs::benchmarks::base::components::SpriteComponent& spr,
                     const ecs::benchmarks::base::components::PlayerComponent& player,
                     const ecs::benchmarks::base::components::HealthComponent& health) {
    updateSprite(spr, player, health);
  });
}

} // namespace ecs::benchmarks::ginseng::systems