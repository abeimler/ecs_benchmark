#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

    void MovementSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.view<ecs::benchmarks::base::components::PositionComponent, const ecs::benchmarks::base::components::VelocityComponent>()
                .each([dt](auto /*entity*/, auto &position, const auto &direction) {
                    updatePosition(position, direction, dt);
                });
    }

}