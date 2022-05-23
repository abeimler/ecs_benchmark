#ifndef ECS_BENCHMARKS_GINSENG_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_COMFLABSYSTEM_H_

#include <ginseng/ginseng.hpp>

#include "base/systems/ComflabSystem.h"

namespace ecs::benchmarks::ginseng::systems {

    class ComflabSystem final : public ecs::benchmarks::base::systems::ComflabSystem<::ginseng::database, float> {
    public:
        void update(EntityManager &registry, TimeDelta dt) override;
    };

}

#endif