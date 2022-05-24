#ifndef ECS_BENCHMARKS_OPENECS_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_OPENECS_COMFLABSYSTEM_H_

#include <ecs.h>

#include "base/systems/ComflabSystem.h"

namespace ecs::benchmarks::openecs::systems {

    class ComflabSystem final
            : public ::ecs::System, ecs::benchmarks::base::systems::ComflabSystem<::ecs::EntityManager, float> {
    public:
        using Entity = ::ecs::Entity;
        using TimeDelta = float;

        void update(TimeDelta dt) override;

        void update(EntityManager &entities, TimeDelta dt) override;
    };

}

#endif