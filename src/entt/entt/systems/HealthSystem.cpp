#include "HealthSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

void HealthSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.view<ecs::benchmarks::base::components::HealthComponent>().each([&](auto& position) {
    updateHealth(position);
  });
}

} // namespace ecs::benchmarks::entt::systems