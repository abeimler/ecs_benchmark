#ifndef ECS_BENCHMARKS_OOP_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_OOP_MORECOMPLEXSYSTEM_H_

#include "oop/entities/EntityFactory.h"
#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::oop::systems {

    class MoreComplexSystem final
            : public ecs::benchmarks::base::systems::MoreComplexSystem<oop::entities::EntityFactory::EntityManagerMDO, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif