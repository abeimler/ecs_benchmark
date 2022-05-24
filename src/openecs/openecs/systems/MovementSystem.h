#ifndef ECS_BENCHMARKS_OPENECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_OPENECS_MOVEMENTSYSTEM_H_

#include <ecs.h>

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::openecs::systems {

    class MovementSystem final
            : public ::ecs::System, ecs::benchmarks::base::systems::MovementSystem<::ecs::EntityManager, float> {
    public:
        using Entity = ::ecs::Entity;
        using TimeDelta = float;

        void update(TimeDelta dt) override;

        void update(EntityManager &entities, TimeDelta dt) override;
    };

}

#endif