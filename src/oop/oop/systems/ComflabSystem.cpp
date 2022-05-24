#include "ComflabSystem.h"
#include "oop/entities/MovableWithDataObject.h"
#include <algorithm>

namespace ecs::benchmarks::oop::systems {

    void ComflabSystem::update(EntityManager &registry, TimeDelta dt) {
        std::for_each(registry.begin(), registry.end(), [dt](auto &entity) {
            entity.updateComflab(dt);
        });
    }

}