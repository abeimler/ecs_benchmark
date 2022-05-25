#ifndef ECS_BENCHMARKS_GINSENG_DATASYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_DATASYSTEM_H_

#include <ginseng/ginseng.hpp>

#include "base/systems/DataSystem.h"

namespace ecs::benchmarks::ginseng::systems {

    class DataSystem final : public ecs::benchmarks::base::systems::DataSystem<::ginseng::database, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif