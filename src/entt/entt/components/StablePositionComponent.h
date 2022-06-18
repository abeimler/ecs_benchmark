#ifndef ECS_BENCHMARKS_ENTT_COMPONENTS_STABLEPOSITIONCOMPONENT_H_
#define ECS_BENCHMARKS_ENTT_COMPONENTS_STABLEPOSITIONCOMPONENT_H_

#include "base/components/PositionComponent.h"

namespace ecs::benchmarks::entt::components {

    struct StablePositionComponent : ecs::benchmarks::base::components::PositionComponent {
        static constexpr auto in_place_delete = true;
    };

}

#endif