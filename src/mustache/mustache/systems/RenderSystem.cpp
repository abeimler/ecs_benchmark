#include "RenderSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::mustache::systems {

void RenderSystem::update(::mustache::World& world, TimeDelta /*dt*/) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, const ecs::benchmarks::base::components::PositionComponent& position,
          const ecs::benchmarks::base::components::SpriteComponent& spr) {
        renderSprite(position, spr);
      },
      run_mode);
}

void RenderSystem::onUpdate(::mustache::World& world) {
  // constexpr float dt = 1.0F / 60.0F;
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, const ecs::benchmarks::base::components::PositionComponent& position,
          const ecs::benchmarks::base::components::SpriteComponent& spr) {
        renderSprite(position, spr);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems