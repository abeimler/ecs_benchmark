#ifndef ECS_BENCHMARKS_ENTITYX_DATASYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_DATASYSTEM_H_

#include "base/systems/DataSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class DataSystem final : public ::entityx::System<DataSystem>,
                         base::systems::DataSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  DataSystem() = default;

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif