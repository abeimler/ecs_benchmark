#ifndef ECS_BENCHMARKS_ENTITYPLUS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYPLUS_MOVEMENTSYSTEM_H_

#include <entityplus/entity.h>

#include "base/systems/MovementSystem.h"
#include "entityplus/entities/EntityFactory.h"

namespace ecs::benchmarks::entityplus::systems {

    class MovementSystem final : public ecs::benchmarks::base::systems::MovementSystem<entityplus::entities::EntityFactory::EntityManager, float> {
    public:
        void update(EntityManager &entityManager, TimeDelta dt) override;
    };

}

#endif