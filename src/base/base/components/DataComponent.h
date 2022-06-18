#ifndef ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_
#define ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_

#include <string>

namespace ecs::benchmarks::base::components {

    struct DataComponent {
        int thingy{0};
        double dingy{0.0F};
        bool mingy{false};
        std::string stringy;
    };


}

#endif