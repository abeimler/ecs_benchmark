#include "GroupDamageSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::entt::systems {

void GroupDamageSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry
      .group<const ecs::benchmarks::base::components::DamageComponent>(
          ::entt::get<ecs::benchmarks::base::components::HealthComponent>)
      .each([&](const auto& damage, auto& health) {
        updateDamage(health, damage);
      });
}

} // namespace ecs::benchmarks::entt::systems