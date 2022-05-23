#ifndef ECS_BENCHMARKS_MUSTACHE_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_MOVEMENTSYSTEM_H_

#include <mustache/ecs/ecs.hpp>

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::mustache::systems {

    class MovementSystem final : public ::mustache::System<MovementSystem>, ecs::benchmarks::base::systems::MovementSystem<::mustache::World, float> {
    public:
        using Entity = ::mustache::Entity;

        void update(::mustache::World& world, TimeDelta dt) override;
        void onUpdate(::mustache::World& world) override;
    };

}

#endif