#ifndef ECS_BENCHMARKS_ENTT_RUNTIMEMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_RUNTIMEMORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::entt::systems {

    class RuntimeMoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<::entt::registry, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif