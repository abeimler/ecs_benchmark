#ifndef ECS_BENCHMARKS_ENTITYPLUS_DATASYSTEM_H_
#define ECS_BENCHMARKS_ENTITYPLUS_DATASYSTEM_H_

#include <entityplus/entity.h>

#include "base/systems/DataSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "entityplus/entities/EntityFactory.h"

namespace ecs::benchmarks::entityplus::systems {

class DataSystem final : public ecs::benchmarks::base::systems::DataSystem<entityplus::entities::EntityFactory::EntityManager, float> {
    public:
        void update(EntityManager &entityManager, TimeDelta dt) override;
    };

}

#endif