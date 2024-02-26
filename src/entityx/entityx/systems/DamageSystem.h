#ifndef ECS_BENCHMARKS_ENTITYX_DAMAGE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_DAMAGE_MORECOMPLEXSYSTEM_H_

#include "base/systems/DamageSystem.h"
#include "base/systems/MoreComplexSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class DamageSystem final : public ::entityx::System<DamageSystem>,
                           base::systems::DamageSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  DamageSystem() = default;

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif