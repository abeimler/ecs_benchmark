#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::entityx::systems {

    void MovementSystem::update(EntityManager &entities, EventManager &events, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent>([this, dt](auto /*entity*/, auto &position, auto &direction) {
            updatePosition(position, direction, dt);
        });
    }

    void MovementSystem::update(EntityManager &entities, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent>([this, dt](auto /*entity*/, auto &position, auto &direction) {
            updatePosition(position, direction, dt);
        });
    }

}