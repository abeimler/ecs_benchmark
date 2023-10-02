#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

void MoreComplexSystem::update(EntityManager& registry, TimeDelta dt) {
  registry
      .view<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent,
            ecs::benchmarks::base::components::DataComponent>()
      .each([this, dt](auto& position, auto& direction, auto& data) {
        updateComponents(position, direction, data);
      });
}

void HealthSystem::update(EntityManager& registry, TimeDelta dt) {
  registry
      .view<ecs::benchmarks::base::components::HealthComponent>()
      .each([this, dt](auto& position) {
        updateHealth(position);
      });
}
void DamageSystem::update(EntityManager& registry, TimeDelta dt) {
  registry
      .view<ecs::benchmarks::base::components::HealthComponent,
            const ecs::benchmarks::base::components::DamageComponent>()
      .each([this, dt](auto& health, const auto& damage) {
        updateDamage(health, damage);
      });
}
} // namespace ecs::benchmarks::entt::systems