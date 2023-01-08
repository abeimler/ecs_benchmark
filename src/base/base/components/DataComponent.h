#ifndef ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_
#define ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_

#include <string>

namespace ecs::benchmarks::base::components {

    struct DataComponent {
        inline static constexpr size_t StringyMaxLength = 23;

        int thingy{0};
        double dingy{0.0};
        bool mingy{false};
        /// @FIXME(pico_ecs): SIGSEGV (Segmentation fault), can't copy string ... support for components with dynamic memory (std::string) ?
        //std::string stringy;
        char stringy[StringyMaxLength+1] = {0};
    };

}

#endif