#ifndef ECS_BENCHMARKS_BASE_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_BASE_MOVEMENTSYSTEM_H_

#include "System.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta>
class MovementSystem : public System<EntityManager, TimeDelta> {
public:
  MovementSystem() = default;
  virtual ~MovementSystem() = default;
  MovementSystem(const MovementSystem&) = delete;
  MovementSystem& operator=(const MovementSystem&) = delete;
  MovementSystem(MovementSystem&&) noexcept = default;
  MovementSystem& operator=(MovementSystem&&) noexcept = default;

  static void updatePosition(ecs::benchmarks::base::components::PositionComponent& position,
                             const ecs::benchmarks::base::components::VelocityComponent& direction,
                             TimeDelta dt) {
    position.x += direction.x * dt;
    position.y += direction.y * dt;
  }
};

} // namespace ecs::benchmarks::base::systems

#endif