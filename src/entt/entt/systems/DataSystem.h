#ifndef ECS_BENCHMARKS_ENTT_DATASYSTEM_H_
#define ECS_BENCHMARKS_ENTT_DATASYSTEM_H_

#include "entt/entt.h"

#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::entt::systems {

    class DataSystem final : public ecs::benchmarks::base::systems::DataSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif