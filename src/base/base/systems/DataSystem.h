#ifndef ECS_BENCHMARKS_BASE_DATASYSTEM_H_
#define ECS_BENCHMARKS_BASE_DATASYSTEM_H_

#include <string>
#include <fmt/core.h>
#include <fmt/format.h>
#include <gsl-lite/gsl-lite.hpp>

#include "System.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::base::systems {

    template<class EntityManager, typename TimeDelta, class DataComponent = ecs::benchmarks::base::components::DataComponent>
    class DataSystem : public System<EntityManager, TimeDelta> {
    public:
        // virtual dtor and the rule of 6
        DataSystem() = default;

        virtual ~DataSystem() = default;

        DataSystem(const DataSystem &) = delete;

        DataSystem &operator=(const DataSystem &) = delete;

        DataSystem(DataSystem &&) noexcept = default;

        DataSystem &operator=(DataSystem &&) noexcept = default;

        static void updateData(DataComponent& data, TimeDelta dt) {
            data.thingy++;
            data.dingy += 0.0001 * gsl::narrow_cast<double>(dt);
            data.mingy = !data.mingy;
            /// @FIXME(pico_ecs): SIGSEGV (Segmentation fault), can't copy string ... support for components with dynamic memory (std::string) ?
            //data.stringy = fmt::format(FMT_STRING("{:4.2f}"), data.dingy);
            std::string stringy = fmt::format(FMT_STRING("{:4.2f}"), data.dingy);
            std::char_traits<char>::copy(data.stringy, stringy.data(), std::min(stringy.length(), DataComponent::StringyMaxLength));
        }
    };

}

#endif