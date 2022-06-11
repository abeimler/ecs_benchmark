#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entityplus::systems {

    void MovementSystem::update(EntityManager &entityManager, TimeDelta dt) {
        //auto groupMovement = entityManager.create_grouping<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent>();
        entityManager.for_each<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent>([this, dt](auto /*entity*/, auto &position, auto &direction) {
            updatePosition(position, direction, dt);
        });
    }

}