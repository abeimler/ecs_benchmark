#include "HealthSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::ginseng::systems {

void HealthSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.visit([&](ecs::benchmarks::base::components::HealthComponent& health) {
    updateHealth(health);
  });
}

} // namespace ecs::benchmarks::ginseng::systems