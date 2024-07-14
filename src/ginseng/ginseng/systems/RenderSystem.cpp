#include "RenderSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"

namespace ecs::benchmarks::ginseng::systems {

void RenderSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.visit([&](const ecs::benchmarks::base::components::PositionComponent& position,
                     const ecs::benchmarks::base::components::SpriteComponent& spr) {
    renderSprite(position, spr);
  });
}

} // namespace ecs::benchmarks::ginseng::systems