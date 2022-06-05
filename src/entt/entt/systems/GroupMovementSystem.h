#ifndef ECS_BENCHMARKS_ENTT_GROUPMOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_GROUPMOVEMENTSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::entt::systems {

    class GroupMovementSystem final : public ecs::benchmarks::base::systems::MovementSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif