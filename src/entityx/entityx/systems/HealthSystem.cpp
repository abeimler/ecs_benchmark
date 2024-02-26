#include "HealthSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entityx::systems {

void HealthSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent>([&](auto /*entity*/, auto& health) {
    updateHealth(health);
  });
}
void HealthSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::HealthComponent>([&](auto /*entity*/, auto& health) {
    updateHealth(health);
  });
}

} // namespace ecs::benchmarks::entityx::systems