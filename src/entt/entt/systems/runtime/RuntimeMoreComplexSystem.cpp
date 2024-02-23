#include "RuntimeMoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

void RuntimeMoreComplexSystem::init(EntityManager& registry) {
  m_view.iterate(registry.storage<ecs::benchmarks::base::components::PositionComponent>())
      .iterate(registry.storage<ecs::benchmarks::base::components::VelocityComponent>())
      .iterate(registry.storage<ecs::benchmarks::base::components::DataComponent>());
}
void RuntimeMoreComplexSystem::update(EntityManager& registry, TimeDelta dt) {
  m_view.each([this, &registry, dt](auto entity) {
    auto& position = registry.get<ecs::benchmarks::base::components::PositionComponent>(entity);
    auto& direction = registry.get<ecs::benchmarks::base::components::VelocityComponent>(entity);
    auto& data = registry.get<ecs::benchmarks::base::components::DataComponent>(entity);
    updateComponents(position, direction, data);
  });
}

} // namespace ecs::benchmarks::entt::systems