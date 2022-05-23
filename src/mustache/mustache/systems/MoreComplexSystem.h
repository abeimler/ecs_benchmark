#ifndef ECS_BENCHMARKS_MUSTACHE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_MORECOMPLEXSYSTEM_H_

#include <mustache/ecs/ecs.hpp>

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::mustache::systems {

    class MoreComplexSystem final : public ::mustache::System<MoreComplexSystem>, ecs::benchmarks::base::systems::MoreComplexSystem<::mustache::World, float> {
    public:
        using Entity = ::mustache::Entity;

        void update(::mustache::World& world, TimeDelta dt) override;
        void onUpdate(::mustache::World& world) override;
    };

}

#endif