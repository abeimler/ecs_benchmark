#ifndef ECS_BENCHMARKS_ENTT_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_COMFLABSYSTEM_H_

#include <entt/entt.hpp>

#include "base/systems/ComflabSystem.h"

namespace ecs::benchmarks::entt::systems {

    class ComflabSystem final : public ecs::benchmarks::base::systems::ComflabSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt);
    };

}

#endif