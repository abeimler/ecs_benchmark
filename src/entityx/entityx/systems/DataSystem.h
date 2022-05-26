#ifndef ECS_BENCHMARKS_ENTITYX_DATASYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_DATASYSTEM_H_

#include <entityx/entityx.h>

#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::entityx::systems {

    class DataSystem final
            : public ::entityx::System<DataSystem>, base::systems::DataSystem<::entityx::EntityManager, float> {
    public:
        using EventManager = ::entityx::EventManager;

        void update(EntityManager &entities, EventManager &events, TimeDelta dt) override;

        void update(EntityManager &entities, TimeDelta dt) override;
    };

}

#endif