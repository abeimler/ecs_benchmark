#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::ginseng::systems {

    void MoreComplexSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.visit([this, dt](ecs::benchmarks::base::components::PositionComponent &position,
                                  ecs::benchmarks::base::components::DirectionComponent &direction,
                                  ecs::benchmarks::base::components::DataComponent &data) {
            updateComponents(position, direction, data, dt);
        });
    }

}