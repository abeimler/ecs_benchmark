#include "ComflabSystem.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::entityx::systems {

    void ComflabSystem::update(EntityManager& entities, EventManager& /*events*/, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::ComflabulationComponent>([dt](auto /*entity*/, auto& comflab){
            updateComflabulation(comflab, dt);
        });
    }

    void ComflabSystem::update(EntityManager &entities, TimeDelta dt) {
        entities.each<ecs::benchmarks::base::components::ComflabulationComponent>([dt](auto /*entity*/, auto& comflab){
            updateComflabulation(comflab, dt);
        });
    }

}