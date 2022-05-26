#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::openecs::systems {

    void DataSystem::update(EntityManager &entities, TimeDelta dt) {
        for (auto entity: entities.with<ecs::benchmarks::base::components::DataComponent>()) {
            auto &data = entity.get<ecs::benchmarks::base::components::DataComponent>();
            updateData(data, dt);
        }
    }

    void DataSystem::update(TimeDelta dt) {
        for (auto entity: entities().with<ecs::benchmarks::base::components::DataComponent>()) {
            auto &data = entity.get<ecs::benchmarks::base::components::DataComponent>();
            updateData(data, dt);
        }
    }

}