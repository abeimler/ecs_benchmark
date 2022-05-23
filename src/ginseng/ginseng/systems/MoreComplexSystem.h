#ifndef ECS_BENCHMARKS_GINSENG_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_MORECOMPLEXSYSTEM_H_

#include <ginseng/ginseng.hpp>

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::ginseng::systems {

    class MoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<::ginseng::database, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif