#ifndef ECS_BENCHMARKS_ENTTGROUPBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTGROUPBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "entt/entities/EntityFactory.h"
#include "entt/EnttGroupApplication.h"

namespace ecs::benchmarks::entt {

    class EnttGroupBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entt", EnttGroupApplication, entities::EntityFactory> {
    public:
        EnttGroupBenchmark() = default;

        explicit EnttGroupBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTGROUPBENCHMARK_H_
