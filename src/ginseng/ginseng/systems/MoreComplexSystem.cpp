#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::ginseng::systems {

    void MoreComplexSystem::update(EntityManager &registry, TimeDelta /*dt*/) {
        registry.visit([this](ecs::benchmarks::base::components::PositionComponent &position,
                                  ecs::benchmarks::base::components::VelocityComponent &direction,
                                  ecs::benchmarks::base::components::DataComponent &data) {
            updateComponents(position, direction, data);
        });
    }

}