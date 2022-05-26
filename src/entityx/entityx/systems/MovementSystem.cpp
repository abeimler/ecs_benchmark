#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::entityx::systems {

    void MovementSystem::update(EntityManager &entities, EventManager & /*events*/, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::PositionComponent, const ecs::benchmarks::base::components::DirectionComponent>(
                [dt](auto /*entity*/, auto &position, const auto &direction) {
                    updatePosition(position, direction, dt);
                });
    }

    void MovementSystem::update(EntityManager &entities, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::PositionComponent, const ecs::benchmarks::base::components::DirectionComponent>(
                [dt](auto /*entity*/, auto &position, const auto &direction) {
                    updatePosition(position, direction, dt);
                });
    }

}