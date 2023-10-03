#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::mustache::systems {

void MoreComplexSystem::update(::mustache::World& world, TimeDelta dt) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [this, dt](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent& position,
                 ecs::benchmarks::base::components::VelocityComponent& direction,
                 ecs::benchmarks::base::components::DataComponent& data) {
        updateComponents(position, direction, data);
      },
      run_mode);
}
void MoreComplexSystem::onUpdate(::mustache::World& world) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [this](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent& position,
             ecs::benchmarks::base::components::VelocityComponent& direction,
             ecs::benchmarks::base::components::DataComponent& data) {
        // constexpr float dt = 1.0F / 60.0F;
        updateComponents(position, direction, data);
      },
      run_mode);
}

void HealthSystem::update(::mustache::World& world, TimeDelta dt) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [this, dt](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health) {
        updateHealth(health);
      },
      run_mode);
}
void HealthSystem::onUpdate(::mustache::World& world) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [this](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health) {
        // constexpr float dt = 1.0F / 60.0F;
        updateHealth(health);
      },
      run_mode);
}

void DamageSystem::update(::mustache::World& world, TimeDelta dt) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [this, dt](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health,
                 const ecs::benchmarks::base::components::DamageComponent& damage) {
        updateDamage(health, damage);
      },
      run_mode);
}
void DamageSystem::onUpdate(::mustache::World& world) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [this](Entity /*entity*/, ecs::benchmarks::base::components::HealthComponent& health,
             const ecs::benchmarks::base::components::DamageComponent& damage) {
        // constexpr float dt = 1.0F / 60.0F;
        updateDamage(health, damage);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems