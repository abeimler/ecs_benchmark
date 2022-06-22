#ifndef ECS_BENCHMARKS_FLECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_FLECS_DATASYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::flecs::systems {

    class DataSystem {
    public:
        using Entity = ::flecs::entity;

        using TimeDelta = float;
        inline static const auto update = [](::flecs::iter &it, size_t /*index*/,
                                       ecs::benchmarks::base::components::DataComponent &data) {
            const TimeDelta dt = it.delta_time();

            data.dingy += 0.0001 * static_cast<double>(dt);
            data.mingy = !data.mingy;
            data.thingy++;
            data.stringy = std::to_string(data.dingy);
        };
    };

}

#endif