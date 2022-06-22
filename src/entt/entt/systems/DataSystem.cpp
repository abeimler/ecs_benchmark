#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::systems {

    void DataSystem::update(EntityManager &registry, TimeDelta dt) {
        auto& storage = registry.storage<ecs::benchmarks::base::components::DataComponent>();
        std::for_each(storage.begin(), storage.end(), [dt](auto& data) {
            updateData(data, dt);
        });
    }

}