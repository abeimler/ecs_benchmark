#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entityx::systems {

void MoreComplexSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::PositionComponent,
                ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>(
      [&](auto /*entity*/, auto& position, auto& direction, auto& data) {
        updateComponents(position, direction, data);
      });
}
void MoreComplexSystem::update(EntityManager& entities, TimeDelta /*dt*/) {
  entities.each<ecs::benchmarks::base::components::PositionComponent,
                ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>(
      [&](auto /*entity*/, auto& position, auto& direction, auto& data) {
        updateComponents(position, direction, data);
      });
}

} // namespace ecs::benchmarks::entityx::systems