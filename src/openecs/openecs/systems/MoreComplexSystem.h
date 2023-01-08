#ifndef ECS_BENCHMARKS_OPENECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_OPENECS_MORECOMPLEXSYSTEM_H_

#include "base/systems/MoreComplexSystem.h"
#include <ecs.h>

namespace ecs::benchmarks::openecs::systems {

class MoreComplexSystem final : public ::ecs::System,
                                ecs::benchmarks::base::systems::MoreComplexSystem<::ecs::EntityManager, float> {
public:
  using Entity = ::ecs::Entity;
  using TimeDelta = float;

  void update(TimeDelta dt) override;

  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::openecs::systems

#endif