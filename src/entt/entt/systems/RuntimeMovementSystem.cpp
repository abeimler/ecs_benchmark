#include "RuntimeMovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::entt::systems {

    void RuntimeMovementSystem::update(EntityManager &registry, TimeDelta dt) {
        ::entt::runtime_view view{};
        view.iterate(registry.storage<ecs::benchmarks::base::components::PositionComponent>())
                .iterate(registry.storage<ecs::benchmarks::base::components::DirectionComponent>());

        view.each([&registry, dt](auto entity) {
            auto& position = registry.get<ecs::benchmarks::base::components::PositionComponent>(entity);
            auto& direction = registry.get<ecs::benchmarks::base::components::DirectionComponent>(entity);
            updatePosition(position, direction, dt);
        });
    }

}