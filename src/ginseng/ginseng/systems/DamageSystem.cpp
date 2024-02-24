#include "DamageSystem.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::ginseng::systems {

void DamageSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.visit([&](ecs::benchmarks::base::components::HealthComponent& health,
                     const ecs::benchmarks::base::components::DamageComponent& damage) {
    updateDamage(health, damage);
  });
}

} // namespace ecs::benchmarks::ginseng::systems