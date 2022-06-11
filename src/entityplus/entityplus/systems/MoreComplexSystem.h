#ifndef ECS_BENCHMARKS_ENTITYPLUS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYPLUS_MORECOMPLEXSYSTEM_H_

#include <entityplus/entity.h>

#include "base/systems/MoreComplexSystem.h"
#include "entityplus/entities/EntityFactory.h"

namespace ecs::benchmarks::entityplus::systems {

    class MoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<entityplus::entities::EntityFactory::EntityManager, float> {
    public:
        void update(EntityManager &entityManager, TimeDelta dt) override;
    };

}

#endif