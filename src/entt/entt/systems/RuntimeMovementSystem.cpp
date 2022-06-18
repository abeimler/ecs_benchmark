#include "RuntimeMovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::entt::systems {

    void RuntimeMovementSystem::init(EntityManager &registry) {
        m_view.iterate(registry.storage<ecs::benchmarks::base::components::PositionComponent>())
                .iterate(registry.storage<ecs::benchmarks::base::components::VelocityComponent>());
    }

    void RuntimeMovementSystem::update(EntityManager &registry, TimeDelta dt) {
        m_view.each([&registry, dt](auto entity) {
            auto &position = registry.get<ecs::benchmarks::base::components::PositionComponent>(entity);
            auto &direction = registry.get<ecs::benchmarks::base::components::VelocityComponent>(entity);
            updatePosition(position, direction, dt);
        });
    }

}