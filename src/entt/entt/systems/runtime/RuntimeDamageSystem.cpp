#include "RuntimeDamageSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

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