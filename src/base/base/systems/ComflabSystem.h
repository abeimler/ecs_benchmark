#ifndef ECS_BENCHMARKS_BASE_COMFLABSYSTEM_H_
#define ECS_BENCHMARKS_BASE_COMFLABSYSTEM_H_

#include <string>

#include "System.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::base::systems {

    template<class EntityManager, typename TimeDelta, class ComflabulationComponent = ecs::benchmarks::base::components::ComflabulationComponent>
    class ComflabSystem : public System<EntityManager, TimeDelta> {
    public:
        // virtual dtor and the rule of 6
        ComflabSystem() = default;

        virtual ~ComflabSystem() = default;

        ComflabSystem(const ComflabSystem &) = delete;

        ComflabSystem &operator=(const ComflabSystem &) = delete;

        ComflabSystem(ComflabSystem &&) = default;

        ComflabSystem &operator=(ComflabSystem &&) = default;

        static void updateComflabulation(ComflabulationComponent &comflab, TimeDelta dt) {
            comflab.thingy += 0.0001F * dt;
            comflab.mingy = !comflab.mingy;
            comflab.dingy++;
            comflab.stringy = std::to_string(comflab.dingy);
        }
    };

}

#endif