#ifndef ECS_BENCHMARKS_OOP_DATASYSTEM_H_
#define ECS_BENCHMARKS_OOP_DATASYSTEM_H_

#include "oop/entities/EntityFactory.h"
#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::oop::systems {

    class DataSystem final
            : public ecs::benchmarks::base::systems::DataSystem<oop::entities::EntityFactory::EntityManagerMDO, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif