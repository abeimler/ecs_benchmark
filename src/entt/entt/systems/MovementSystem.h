#ifndef ECS_BENCHMARKS_ENTT_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_MOVEMENTSYSTEM_H_

#include <entt/entt.hpp>

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::entt::systems {

    class MovementSystem final : public ecs::benchmarks::base::systems::MovementSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt);
    };

}

#endif