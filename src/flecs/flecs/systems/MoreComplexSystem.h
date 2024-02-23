#ifndef ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::flecs::systems {

class MoreComplexSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;
  using EntityManager = ::flecs::world;
  using BaseSystem = ecs::benchmarks::base::systems::MoreComplexSystem<EntityManager, TimeDelta>;

  inline static const auto update = [](::flecs::iter& /*it*/, size_t /*index*/,
                                       const ecs::benchmarks::base::components::PositionComponent& position,
                                       ecs::benchmarks::base::components::VelocityComponent& direction,
                                       ecs::benchmarks::base::components::DataComponent& data) {
    BaseSystem::updateComponents(position, direction, data);
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
