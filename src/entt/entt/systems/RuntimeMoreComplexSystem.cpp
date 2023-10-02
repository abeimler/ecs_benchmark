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

void RuntimeHealthSystem::init(EntityManager& registry) {
  m_view.iterate(registry.storage<ecs::benchmarks::base::components::HealthComponent>());
}
void RuntimeHealthSystem::update(EntityManager& registry, TimeDelta dt) {
  m_view.each([this, &registry, dt](auto entity) {
    auto& health = registry.get<ecs::benchmarks::base::components::HealthComponent>(entity);
    updateHealth(health);
  });
}

void RuntimeDamageSystem::init(EntityManager& registry) {
  m_view.iterate(registry.storage<ecs::benchmarks::base::components::DamageComponent>())
      .iterate(registry.storage<ecs::benchmarks::base::components::HealthComponent>());
}
void RuntimeDamageSystem::update(EntityManager& registry, TimeDelta dt) {
  m_view.each([this, &registry, dt](auto entity) {
    auto& health = registry.get<ecs::benchmarks::base::components::HealthComponent>(entity);
    const auto& damage = registry.get<const ecs::benchmarks::base::components::DamageComponent>(entity);
    updateDamage(health, damage);
  });
}

} // namespace ecs::benchmarks::entt::systems