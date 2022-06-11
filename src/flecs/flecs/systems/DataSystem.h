#ifndef ECS_BENCHMARKS_FLECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_FLECS_DATASYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::flecs::systems {

    class DataSystem {
    public:
        using Entity = ::flecs::entity;

        using TimeDelta = float;
        inline static auto update = [](::flecs::iter &it, size_t /*index*/,
                                       ecs::benchmarks::base::components::DataComponent &data) {
            const TimeDelta dt = it.delta_time();

            data.thingy += 0.0001F * dt;
            data.mingy = !data.mingy;
            data.dingy++;
            data.stringy = std::to_string(data.dingy);
        };
    };

}

#endif