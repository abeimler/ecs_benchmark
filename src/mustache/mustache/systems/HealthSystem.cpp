#include "HealthSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::mustache::systems {

void HealthSystem::update(::mustache::World& world, TimeDelta dt) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health) {
        updateHealth(health);
      },
      run_mode);
}
void HealthSystem::onUpdate(::mustache::World& world) {
  constexpr float dt = 1.0F / 60.0F;
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health) {
        updateHealth(health);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems