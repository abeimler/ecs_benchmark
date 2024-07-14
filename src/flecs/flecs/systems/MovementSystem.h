#ifndef ECS_BENCHMARKS_FLECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MOVEMENTSYSTEM_H_

#include "flecs/custom_flecs.h"
#include <gsl/gsl-lite.hpp>

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::flecs::systems {

class MovementSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::MovementSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](::flecs::iter& it) {
    const auto dt = gsl::narrow_cast<TimeDelta>(it.delta_time());

    while (it.next()) {
      auto position = it.field<ecs::benchmarks::base::components::PositionComponent>(0);
      const auto direction = it.field<const ecs::benchmarks::base::components::VelocityComponent>(1);
      for (auto i : it) {
        BaseSystem::updatePosition(position[i], direction[i], dt);
      }
    }
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
