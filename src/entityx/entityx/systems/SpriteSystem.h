#ifndef ECS_BENCHMARKS_ENTITYX_SPRITE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_SPRITE_MORECOMPLEXSYSTEM_H_

#include "base/systems/SpriteSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class SpriteSystem final : public ::entityx::System<SpriteSystem>,
                           ecs::benchmarks::base::systems::SpriteSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  SpriteSystem() = default;

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif