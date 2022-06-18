#ifndef ECS_BENCHMARKS_BASE_DATASYSTEM_H_
#define ECS_BENCHMARKS_BASE_DATASYSTEM_H_

#include <string>

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
            data.dingy += 0.0001 * dt;
            data.mingy = !data.mingy;
            data.stringy = std::to_string(data.dingy);
        }
    };

}

#endif