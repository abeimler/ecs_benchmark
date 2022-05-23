#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::ginseng::systems {

    void MovementSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.visit([dt](ecs::benchmarks::base::components::PositionComponent &position, ecs::benchmarks::base::components::DirectionComponent &direction) {
            updatePosition(position, direction, dt);
        });
    }

}