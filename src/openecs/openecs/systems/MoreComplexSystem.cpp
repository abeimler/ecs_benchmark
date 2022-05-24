#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::openecs::systems {

    void MoreComplexSystem::update(EntityManager &entities, TimeDelta dt) {
        for (auto entity: entities.with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>()) {
            auto &position = entity.get<ecs::benchmarks::base::components::PositionComponent>();
            auto &direction = entity.get<ecs::benchmarks::base::components::DirectionComponent>();
            auto &comflab = entity.get<ecs::benchmarks::base::components::ComflabulationComponent>();
            updateComponents(position, direction, comflab, dt);
        }
    }

    void MoreComplexSystem::update(TimeDelta dt) {
        for (auto entity: entities().with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>()) {
            auto &position = entity.get<ecs::benchmarks::base::components::PositionComponent>();
            auto &direction = entity.get<ecs::benchmarks::base::components::DirectionComponent>();
            auto &comflab = entity.get<ecs::benchmarks::base::components::ComflabulationComponent>();
            updateComponents(position, direction, comflab, dt);
        }
    }
}