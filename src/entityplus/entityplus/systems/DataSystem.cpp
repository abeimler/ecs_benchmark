#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityplus::systems {

    void DataSystem::update(EntityManager &entityManager, TimeDelta dt) {
        //auto groupData = entityManager.create_grouping<ecs::benchmarks::base::components::DataComponent>();
        entityManager.for_each<ecs::benchmarks::base::components::DataComponent>([dt](auto /*entity*/, auto &data) {
            updateData(data, dt);
        });
    }

}