#include "MovementSystem.h"
#include "oop/entities/MovableObject.h"
#include "oop/entities/MovableWithDataObject.h"
#include <algorithm>

namespace ecs::benchmarks::oop::systems {

    void MovementMOSystem::update(EntityManager& registry, TimeDelta dt) {
        std::for_each(registry.begin(), registry.end(), [dt](auto& entity) {
            entity.update(dt);
        });
    }

    void MovementMDOSystem::update(EntityManager& registry, TimeDelta dt) {
        std::for_each(registry.begin(), registry.end(), [dt](auto& entity) {
            entity.updatePosition(dt);
        });
    }

}