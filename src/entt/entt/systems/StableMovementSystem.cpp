#include "StableMovementSystem.h"
#include "entt/components/StablePositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

    void StableMovementSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.view<ecs::benchmarks::entt::components::StablePositionComponent, const ecs::benchmarks::base::components::VelocityComponent>()
                .each([dt](auto &position, const auto &direction) {
                    updatePosition(position, direction, dt);
                });
    }

}