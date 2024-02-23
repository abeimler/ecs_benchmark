#include "StableRuntimeMovementSystem.h"
#include "base/components/VelocityComponent.h"
#include "entt/components/StablePositionComponent.h"

namespace ecs::benchmarks::entt::systems {

void StableRuntimeMovementSystem::init(EntityManager& registry) {
  m_view.iterate(registry.storage<ecs::benchmarks::entt::components::StablePositionComponent>())
      .iterate(registry.storage<ecs::benchmarks::base::components::VelocityComponent>());
}

void StableRuntimeMovementSystem::update(EntityManager& registry, TimeDelta dt) {
  m_view.each([&registry, dt](auto entity) {
    auto& position = registry.get<ecs::benchmarks::entt::components::StablePositionComponent>(entity);
    auto& direction = registry.get<ecs::benchmarks::base::components::VelocityComponent>(entity);
    updatePosition(position, direction, dt);
  });
}

} // namespace ecs::benchmarks::entt::systems