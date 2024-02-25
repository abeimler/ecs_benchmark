#include "SpriteSystem.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::systems {

void SpriteSystem::update(::mustache::World& world, TimeDelta /*dt*/) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::SpriteComponent& spr,
          const ecs::benchmarks::base::components::PlayerComponent& player,
          const ecs::benchmarks::base::components::HealthComponent& health) {
        updateSprite(spr, player, health);
      },
      run_mode);
}

void SpriteSystem::onUpdate(::mustache::World& world) {
  //constexpr float dt = 1.0F / 60.0F;
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::SpriteComponent& spr,
          const ecs::benchmarks::base::components::PlayerComponent& player,
          const ecs::benchmarks::base::components::HealthComponent& health) {
        updateSprite(spr, player, health);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems