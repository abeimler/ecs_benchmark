#ifndef ECS_BENCHMARKS_ENTITASPP_COMPONENTS_POSITIONCOMPONENT_H_
#define ECS_BENCHMARKS_ENTITASPP_COMPONENTS_POSITIONCOMPONENT_H_

#include <EntitasPP/IComponent.hpp>

#include "base/components/PositionComponent.h"

namespace ecs::benchmarks::EntitasPP::components {

    class PositionComponent : public ecs::benchmarks::base::components::PositionComponent, public ::EntitasPP::IComponent {
    public:
        float x{0.0F};
        float y{0.0F};

        void Reset() {
            x = 0.0F;
            y = 0.0F;
        }
    };

}

#endif