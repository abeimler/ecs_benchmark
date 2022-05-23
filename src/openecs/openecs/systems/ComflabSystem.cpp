#include "ComflabSystem.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::openecs::systems {

    void ComflabSystem::update(EntityManager& entities, TimeDelta dt) {
        for(auto entity : entities.with<ecs::benchmarks::base::components::ComflabulationComponent>()){
            auto &comflab = entity.get<ecs::benchmarks::base::components::ComflabulationComponent>();
            updateComflabulation(comflab, dt);
        }
    }

    void ComflabSystem::update(TimeDelta dt) {
        for(auto entity : entities().with<ecs::benchmarks::base::components::ComflabulationComponent>()){
            auto &comflab = entity.get<ecs::benchmarks::base::components::ComflabulationComponent>();
            updateComflabulation(comflab, dt);
        }
    }

}