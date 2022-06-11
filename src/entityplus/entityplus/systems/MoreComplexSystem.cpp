#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityplus::systems {

    void MoreComplexSystem::update(EntityManager &entityManager, TimeDelta dt) {
        //auto groupComplex = entityManager.create_grouping<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>();
        entityManager.for_each<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>([this, dt](auto /*entity*/, auto &position, auto &direction, auto &data) {
            updateComponents(position, direction, data, dt);
        });
    }

}