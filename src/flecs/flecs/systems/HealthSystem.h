#ifndef ECS_BENCHMARKS_FLECS_HEALTH_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_HEALTH_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/components/HeroMonsterComponents.h"
#include "base/systems/HealthSystem.h"

namespace ecs::benchmarks::flecs::systems {

class HealthSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::HealthSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](ecs::benchmarks::base::components::HealthComponent& health) {
    BaseSystem::updateHealth(health);
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
