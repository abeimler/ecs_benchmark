#ifndef ECS_BENCHMARKS_FLECS_DAMAGE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_DAMAGE_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/DamageSystem.h"

namespace ecs::benchmarks::flecs::systems {

class DamageSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::DamageSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](ecs::benchmarks::base::components::HealthComponent& health,
                                       const ecs::benchmarks::base::components::DamageComponent& damage) {
    BaseSystem::updateDamage(health, damage);
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
