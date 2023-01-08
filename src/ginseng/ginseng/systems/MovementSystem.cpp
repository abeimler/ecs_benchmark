#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::ginseng::systems {

void MovementSystem::update(EntityManager& registry, TimeDelta dt) {
  registry.visit([dt](ecs::benchmarks::base::components::PositionComponent& position,
                      const ecs::benchmarks::base::components::VelocityComponent& direction) {
    updatePosition(position, direction, dt);
  });
}

} // namespace ecs::benchmarks::ginseng::systems