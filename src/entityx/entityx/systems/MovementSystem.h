#ifndef ECS_BENCHMARKS_ENTITYX_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_MOVEMENTSYSTEM_H_

#include "base/systems/MovementSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class MovementSystem final : public ::entityx::System<MovementSystem>,
                             base::systems::MovementSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  MovementSystem() = default;

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif