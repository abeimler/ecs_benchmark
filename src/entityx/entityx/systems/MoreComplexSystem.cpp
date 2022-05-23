#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::entityx::systems {

    void MoreComplexSystem::update(EntityManager &entities, EventManager &events, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>([this, dt](auto /*entity*/, auto &position, auto &direction, auto &comflab) {
            updateComponents(position, direction, comflab, dt);
        });
    }

    void MoreComplexSystem::update(EntityManager &entities, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>([this, dt](auto /*entity*/, auto &position, auto &direction, auto &comflab) {
            updateComponents(position, direction, comflab, dt);
        });
    }

}