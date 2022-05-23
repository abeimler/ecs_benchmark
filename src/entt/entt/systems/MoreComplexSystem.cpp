#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::entt::systems {

    void MoreComplexSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.view<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::ComflabulationComponent>()
                .each([this, dt](auto /*entity*/, auto &position, auto &direction, auto &comflab) {
                    updateComponents(position, direction, comflab, dt);
                });
    }

}