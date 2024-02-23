#ifndef ECS_BENCHMARKS_FLECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_FLECS_DATASYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/DataSystem.h"
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::flecs::systems {

class DataSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::DataSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](::flecs::iter& it, ecs::benchmarks::base::components::DataComponent* data) {
    using DataComponent = ecs::benchmarks::base::components::DataComponent;
    const auto dt = gsl::narrow_cast<TimeDelta>(it.delta_time());

    for (auto i : it) {
      BaseSystem::updateData(data[i], dt);
    }
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
