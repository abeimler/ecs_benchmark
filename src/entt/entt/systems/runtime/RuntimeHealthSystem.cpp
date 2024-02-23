#include "RuntimeHealthSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

void RuntimeHealthSystem::init(EntityManager& registry) {
  m_view.iterate(registry.storage<ecs::benchmarks::base::components::HealthComponent>());
}
void RuntimeHealthSystem::update(EntityManager& registry, TimeDelta dt) {
  m_view.each([this, &registry, dt](auto entity) {
    auto& health = registry.get<ecs::benchmarks::base::components::HealthComponent>(entity);
    updateHealth(health);
  });
}

} // namespace ecs::benchmarks::entt::systems