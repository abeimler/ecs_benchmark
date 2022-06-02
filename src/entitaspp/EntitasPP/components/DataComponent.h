#ifndef ECS_BENCHMARKS_ENTITASPP_COMPONENTS_DATACOMPONENT_H_
#define ECS_BENCHMARKS_ENTITASPP_COMPONENTS_DATACOMPONENT_H_

#include <EntitasPP/IComponent.hpp>

#include "base/components/DataComponent.h"

namespace ecs::benchmarks::EntitasPP::components {

    class DataComponent : public ecs::benchmarks::base::components::DataComponent, public ::EntitasPP::IComponent {
    public:
        float thingy{0.0F};
        int dingy{0};
        bool mingy{false};
        std::string stringy;

        void Reset() {
            thingy = 0.0F;
            dingy = 0;
            mingy = false;
            stringy.clear();
        }
    };

}

#endif