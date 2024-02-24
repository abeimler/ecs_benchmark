#include "DamageSystem.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::mustache::systems {

void DamageSystem::update(::mustache::World& world, TimeDelta dt) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health,
          const ecs::benchmarks::base::components::DamageComponent& damage) {
        updateDamage(health, damage);
      },
      run_mode);
}
void DamageSystem::onUpdate(::mustache::World& world) {
  constexpr TimeDelta dt = 1.0F / 60.0F;
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health,
          const ecs::benchmarks::base::components::DamageComponent& damage) {
        updateDamage(health, damage);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems