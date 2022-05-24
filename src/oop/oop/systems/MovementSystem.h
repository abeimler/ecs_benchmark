#ifndef ECS_BENCHMARKS_OOP_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_OOP_MOVEMENTSYSTEM_H_

#include "oop/entities/EntityFactory.h"
#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::oop::systems {

    class MovementMOSystem final
            : public ecs::benchmarks::base::systems::MovementSystem<oop::entities::EntityFactory::EntityManagerMO, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

    class MovementMDOSystem final
            : public ecs::benchmarks::base::systems::MovementSystem<oop::entities::EntityFactory::EntityManagerMDO, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif