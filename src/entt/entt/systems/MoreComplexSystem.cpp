#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

void MoreComplexSystem::update(EntityManager& registry, TimeDelta dt) {
  registry
      .view<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent,
            ecs::benchmarks::base::components::DataComponent>()
      .each([this, dt](auto& position, auto& direction, auto& data) {
        updateComponents(position, direction, data);
      });
}

} // namespace ecs::benchmarks::entt::systems