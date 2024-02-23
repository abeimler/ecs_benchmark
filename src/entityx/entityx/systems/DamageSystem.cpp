#include "DamageSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entityx::systems {

void DamageSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent,
                const ecs::benchmarks::base::components::DamageComponent>(
      [&](auto /*entity*/, auto& health, const auto& damage) {
        updateDamage(health, damage);
      });
}
void DamageSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent,
                const ecs::benchmarks::base::components::DamageComponent>(
      [&](auto /*entity*/, auto& health, const auto& damage) {
        updateDamage(health, damage);
      });
}

} // namespace ecs::benchmarks::entityx::systems