#ifndef ECS_BENCHMARKS_FLECS_RENDER_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_RENDER_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/systems/RenderSystem.h"

namespace ecs::benchmarks::flecs::systems {

class RenderSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::RenderSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](auto& frameBuffer,
                                       const ecs::benchmarks::base::components::PositionComponent& position,
                                       const ecs::benchmarks::base::components::SpriteComponent& spr) {
    BaseSystem::renderSprite(frameBuffer, position, spr);
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
