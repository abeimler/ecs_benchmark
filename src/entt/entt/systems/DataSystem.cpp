#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::systems {

    void DataSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.view<ecs::benchmarks::base::components::DataComponent>()
                .each([dt](auto /*entity*/, auto &data) {
                    updateData(data, dt);
                });
    }

}