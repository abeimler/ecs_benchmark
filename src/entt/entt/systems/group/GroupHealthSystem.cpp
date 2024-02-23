#include "GroupHealthSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

void GroupHealthSystem::update(EntityManager& registry, TimeDelta /*dt*/) {
  registry.group<ecs::benchmarks::base::components::HealthComponent>().each([&](auto& health) {
    updateHealth(health);
  });
}

} // namespace ecs::benchmarks::entt::systems