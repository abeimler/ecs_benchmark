#include "RuntimeDataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::systems {

    void RuntimeDataSystem::update(EntityManager &registry, TimeDelta dt) {
        ::entt::runtime_view view{};
        view.iterate(registry.storage<ecs::benchmarks::base::components::DataComponent>());

        view.each([&registry, dt](auto entity) {
            auto &data = registry.get<ecs::benchmarks::base::components::DataComponent>(entity);
            updateData(data, dt);
        });
    }

}