#include "GroupMovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::entt::systems {

    void GroupMovementSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.group<ecs::benchmarks::base::components::PositionComponent>(::entt::get<const ecs::benchmarks::base::components::DirectionComponent>)
                .each([dt](auto /*entity*/, auto &position, const auto &direction) {
                    updatePosition(position, direction, dt);
                });
    }

}