#ifndef ECS_BENCHMARKS_ENTITYX_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_COMFLABSYSTEM_H_

#include <entityx/entityx.h>

#include "base/systems/ComflabSystem.h"

namespace ecs::benchmarks::entityx::systems {

    class ComflabSystem final
            : public ::entityx::System<ComflabSystem>, base::systems::ComflabSystem<::entityx::EntityManager, float> {
    public:
        using EventManager = ::entityx::EventManager;

        void update(EntityManager &entities, EventManager &events, TimeDelta dt) override;

        void update(EntityManager &entities, TimeDelta dt) override;
    };

}

#endif