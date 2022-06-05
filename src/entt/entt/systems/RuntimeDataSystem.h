#ifndef ECS_BENCHMARKS_ENTT_RUNTIMEDATASYSTEM_H_
#define ECS_BENCHMARKS_ENTT_RUNTIMEDATASYSTEM_H_

#include "entt/entt.h"

#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::entt::systems {

    class RuntimeDataSystem final : public ecs::benchmarks::base::systems::DataSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif