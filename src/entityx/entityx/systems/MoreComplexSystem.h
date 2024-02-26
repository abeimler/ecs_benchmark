#ifndef ECS_BENCHMARKS_ENTITYX_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_MORECOMPLEXSYSTEM_H_

#include "base/systems/MoreComplexSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class MoreComplexSystem final : public ::entityx::System<MoreComplexSystem>,
                                base::systems::MoreComplexSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  MoreComplexSystem() = default;

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif