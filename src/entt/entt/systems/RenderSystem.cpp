#include "RenderSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

void RenderSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry
      .view<const ecs::benchmarks::base::components::PositionComponent,
            const ecs::benchmarks::base::components::SpriteComponent>()
      .each([&](const auto& position, const auto& spr) {
        renderSprite(position, spr);
      });
}

} // namespace ecs::benchmarks::entt::systems