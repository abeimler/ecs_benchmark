#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityx::systems {

    void DataSystem::update(EntityManager &entities, EventManager & /*events*/, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::DataComponent>([dt](auto /*entity*/, auto &data) {
            updateData(data, dt);
        });
    }

    void DataSystem::update(EntityManager &entities, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::DataComponent>([dt](auto /*entity*/, auto &data) {
            updateData(data, dt);
        });
    }

}