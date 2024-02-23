#include "HealthSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::ginseng::systems {

void HealthSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.visit([&](ecs::benchmarks::base::components::HealthComponent& health) {
    updateHealth(health);
  });
}

} // namespace ecs::benchmarks::ginseng::systems