#include "GroupMovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

void GroupMovementSystem::update(EntityManager& registry, TimeDelta dt) {
  registry
      .group<ecs::benchmarks::base::components::PositionComponent>(
          ::entt::get<const ecs::benchmarks::base::components::VelocityComponent>)
      .each([&](auto& position, const auto& direction) {
        updatePosition(position, direction, dt);
      });
}

} // namespace ecs::benchmarks::entt::systems