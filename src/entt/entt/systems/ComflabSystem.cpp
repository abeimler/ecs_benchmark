#include "ComflabSystem.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::entt::systems {

    void ComflabSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.view<ecs::benchmarks::base::components::ComflabulationComponent>()
                .each([this, dt](auto /*entity*/, auto &comflab) {
                    updateComflabulation(comflab, dt);
                });
    }

}