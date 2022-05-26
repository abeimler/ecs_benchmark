#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::entt::systems {

    void MovementSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.view<ecs::benchmarks::base::components::PositionComponent, const ecs::benchmarks::base::components::DirectionComponent>()
                .each([dt](auto /*entity*/, auto &position, const auto &direction) {
                    updatePosition(position, direction, dt);
                });
    }

}