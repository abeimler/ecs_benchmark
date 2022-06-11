#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::openecs::systems {

    void MovementSystem::update(EntityManager &entities, TimeDelta dt) {
        for (auto entity: entities.with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent>()) {
            auto &position = entity.get<ecs::benchmarks::base::components::PositionComponent>();
            auto &direction = entity.get<ecs::benchmarks::base::components::VelocityComponent>();
            updatePosition(position, direction, dt);
        }
    }

    void MovementSystem::update(TimeDelta dt) {
        for (auto entity: entities().with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent>()) {
            auto &position = entity.get<ecs::benchmarks::base::components::PositionComponent>();
            auto &direction = entity.get<ecs::benchmarks::base::components::VelocityComponent>();
            updatePosition(position, direction, dt);
        }
    }
}