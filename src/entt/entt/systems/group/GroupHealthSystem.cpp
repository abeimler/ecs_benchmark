#include "GroupHealthSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

void GroupHealthSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.group<ecs::benchmarks::base::components::HealthComponent>().each([&](auto& health) {
    updateHealth(health);
  });
}

} // namespace ecs::benchmarks::entt::systems