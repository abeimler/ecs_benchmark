#include "DataSystem.h"
#include "oop/entities/MovableWithDataObject.h"
#include <algorithm>

namespace ecs::benchmarks::oop::systems {

    void DataSystem::update(EntityManager &registry, TimeDelta dt) {
        std::for_each(registry.begin(), registry.end(), [dt](auto &entity) {
            entity.updateData(dt);
        });
    }

}