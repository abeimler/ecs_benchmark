#ifndef ECS_BENCHMARKS_OOP_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_OOP_COMFLABSYSTEM_H_

#include "oop/entities/EntityFactory.h"
#include "base/systems/ComflabSystem.h"

namespace ecs::benchmarks::oop::systems {

    class ComflabSystem final
            : public ecs::benchmarks::base::systems::ComflabSystem<oop::entities::EntityFactory::EntityManagerMDO, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif