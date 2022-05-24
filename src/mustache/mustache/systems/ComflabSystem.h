#ifndef ECS_BENCHMARKS_MUSTACHE_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_COMFLABSYSTEM_H_

#include <mustache/ecs/ecs.hpp>

#include "base/systems/ComflabSystem.h"

namespace ecs::benchmarks::mustache::systems {

    class ComflabSystem final
            : public ::mustache::System<ComflabSystem>,
              ecs::benchmarks::base::systems::ComflabSystem<::mustache::World, float> {
    public:
        using Entity = ::mustache::Entity;

        void update(::mustache::World &world, TimeDelta dt) override;

        void onUpdate(::mustache::World &world) override;
    };

}

#endif