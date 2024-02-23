#ifndef ECS_BENCHMARKS_FLECS_SPRITE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_SPRITE_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"
#include "base/systems/SpriteSystem.h"

namespace ecs::benchmarks::flecs::systems {

class SpriteSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::SpriteSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](ecs::benchmarks::base::components::SpriteComponent& spr,
                                       const ecs::benchmarks::base::components::PlayerComponent& player,
                                       const ecs::benchmarks::base::components::HealthComponent& health) {
    BaseSystem::updateSprite(spr, player, health);
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
