#include "GroupMoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::systems {

    void GroupMoreComplexSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.group<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>()
                .each([this, dt](auto /*entity*/, auto &position, auto &direction, auto &data) {
                    updateComponents(position, direction, data, dt);
                });
    }

}