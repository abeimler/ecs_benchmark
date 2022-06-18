#ifndef ECS_BENCHMARKS_FLECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MOVEMENTSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::flecs::systems {

    class MovementSystem {
    public:
        using TimeDelta = float;
        using Entity = ::flecs::entity;

        inline static const auto update = [](::flecs::iter &it, size_t /*index*/,
                                       ecs::benchmarks::base::components::PositionComponent &position,
                                       const ecs::benchmarks::base::components::VelocityComponent &direction) {
            const TimeDelta dt = it.delta_time();
            position.x += direction.x * dt;
            position.y += direction.y * dt;
        };
    };

}

#endif