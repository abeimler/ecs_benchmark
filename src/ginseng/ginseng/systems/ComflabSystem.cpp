#include "ComflabSystem.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::ginseng::systems {

    void ComflabSystem::update(EntityManager &registry, TimeDelta dt) {
        registry.visit([dt](ecs::benchmarks::base::components::ComflabulationComponent &comflab) {
            updateComflabulation(comflab, dt);
        });
    }

}