#ifndef ECS_BENCHMARKS_OPENECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_OPENECS_MORECOMPLEXSYSTEM_H_

#include <ecs.h>

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::openecs::systems {

    class MoreComplexSystem final : public ::ecs::System, ecs::benchmarks::base::systems::MoreComplexSystem<::ecs::EntityManager, float> {
    public:
        using Entity = ::ecs::Entity;
        using TimeDelta = float;

        void update(TimeDelta dt) override;
        void update(EntityManager& entities, TimeDelta dt) override;
    };

}

#endif