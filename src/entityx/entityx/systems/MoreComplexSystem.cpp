#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entityx::systems {

void MoreComplexSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::PositionComponent,
                ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>(
      [this](auto /*entity*/, auto& position, auto& direction, auto& data) {
        updateComponents(position, direction, data);
      });
}
void MoreComplexSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::PositionComponent,
                ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>(
      [this](auto /*entity*/, auto& position, auto& direction, auto& data) {
        updateComponents(position, direction, data);
      });
}


void HealthSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent>(
      [this](auto /*entity*/, auto& health) {
        updateHealth(health);
      });
}
void HealthSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent>(
      [this](auto /*entity*/, auto& health) {
        updateHealth(health);
      });
}

void DamageSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent, const ecs::benchmarks::base::components::DamageComponent>(
      [this](auto /*entity*/, auto& health, const auto& damage) {
        updateDamage(health, damage);
      });
}
void DamageSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent, const ecs::benchmarks::base::components::DamageComponent>(
      [this](auto /*entity*/, auto& health, const auto& damage) {
        updateDamage(health, damage);
      });
}

} // namespace ecs::benchmarks::entityx::systems