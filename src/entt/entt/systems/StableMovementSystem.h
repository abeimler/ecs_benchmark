#ifndef ECS_BENCHMARKS_ENTT_STABLEMOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_STABLEMOVEMENTSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::entt::systems {

    class StableMovementSystem final : public ecs::benchmarks::base::systems::MovementSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif