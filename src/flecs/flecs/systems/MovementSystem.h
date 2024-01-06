#ifndef ECS_BENCHMARKS_FLECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MOVEMENTSYSTEM_H_

#include "flecs/custom_flecs.h"
#include <gsl/gsl-lite.hpp>

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::flecs::systems {

class MovementSystem {
public:
  using TimeDelta = double;
  using Entity = ::flecs::entity;

  inline static const auto update = [](::flecs::iter& it,
                                       ecs::benchmarks::base::components::PositionComponent* position,
                                       const ecs::benchmarks::base::components::VelocityComponent* direction) {
    const auto dt = gsl::narrow_cast<TimeDelta>(it.delta_time());
    for (auto i : it) {
      position[i].x += direction[i].x * dt;
      position[i].y += direction[i].y * dt;
    }
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
