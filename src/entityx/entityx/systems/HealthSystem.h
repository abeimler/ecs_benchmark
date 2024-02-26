#ifndef ECS_BENCHMARKS_ENTITYX_HEALTH_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_HEALTH_MORECOMPLEXSYSTEM_H_

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class HealthSystem final : public ::entityx::System<HealthSystem>,
                           base::systems::HealthSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  HealthSystem() = default;

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif