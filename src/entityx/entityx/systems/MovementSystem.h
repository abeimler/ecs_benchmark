#ifndef ECS_BENCHMARKS_ENTITYX_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_MOVEMENTSYSTEM_H_

#include <entityx/entityx.h>

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::entityx::systems {

    class MovementSystem final : public ::entityx::System<MovementSystem>, ecs::benchmarks::base::systems::MovementSystem<::entityx::EntityManager, float> {
    public:
        using EventManager = ::entityx::EventManager;

        void update(EntityManager &entities, EventManager &events, TimeDelta dt) override;
        void update(EntityManager &entities, TimeDelta dt) override;
    };

}

#endif