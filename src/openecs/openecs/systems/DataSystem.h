#ifndef ECS_BENCHMARKS_OPENECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_OPENECS_DATASYSTEM_H_

#include "base/systems/DataSystem.h"
#include <ecs.h>

namespace ecs::benchmarks::openecs::systems {

class DataSystem final : public ::ecs::System, ecs::benchmarks::base::systems::DataSystem<::ecs::EntityManager, float> {
public:
  using Entity = ::ecs::Entity;
  using TimeDelta = float;

  void update(TimeDelta dt) override;

  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::openecs::systems

#endif