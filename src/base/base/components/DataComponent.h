#ifndef ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_
#define ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_

#include <string>

namespace ecs::benchmarks::base::components {

    struct DataComponent {
        float thingy{0.0F};
        int dingy{0};
        bool mingy{false};
        std::string stringy;
    };


}

#endif