#include "DamageSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

void DamageSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry
      .view<ecs::benchmarks::base::components::HealthComponent,
            const ecs::benchmarks::base::components::DamageComponent>()
      .each([&](auto& health, const auto& damage) {
        updateDamage(health, damage);
      });
}

} // namespace ecs::benchmarks::entt::systems