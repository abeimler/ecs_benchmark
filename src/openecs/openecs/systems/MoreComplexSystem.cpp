#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::openecs::systems {

    void MoreComplexSystem::update(EntityManager &entities, TimeDelta /*dt*/) {
        for (auto entity: entities.with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>()) {
            auto &position = entity.get<ecs::benchmarks::base::components::PositionComponent>();
            auto &direction = entity.get<ecs::benchmarks::base::components::VelocityComponent>();
            auto &data = entity.get<ecs::benchmarks::base::components::DataComponent>();
            updateComponents(position, direction, data);
        }
    }

    void MoreComplexSystem::update(TimeDelta /*dt*/) {
        for (auto entity: entities().with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>()) {
            auto &position = entity.get<ecs::benchmarks::base::components::PositionComponent>();
            auto &direction = entity.get<ecs::benchmarks::base::components::VelocityComponent>();
            auto &data = entity.get<ecs::benchmarks::base::components::DataComponent>();
            updateComponents(position, direction, data);
        }
    }
}