#include "RenderSystem.h"
#include "base/components/SpriteComponent.h"
#include "base/components/PositionComponent.h"

namespace ecs::benchmarks::entityx::systems {

void RenderSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<const ecs::benchmarks::base::components::PositionComponent,
                const ecs::benchmarks::base::components::SpriteComponent>(
      [&](auto /*entity*/, const auto& position, const auto& spr) {
        renderSprite(position, spr);
      });
}
void RenderSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<const ecs::benchmarks::base::components::PositionComponent,
                const ecs::benchmarks::base::components::SpriteComponent>(
      [&](auto /*entity*/, const auto& position, const auto& spr) {
        renderSprite(position, spr);
      });
}

} // namespace ecs::benchmarks::entityx::systems