#ifndef ECS_BENCHMARKS_ENTTRUNTIMEBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTRUNTIMEBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "entt/entities/EntityFactory.h"
#include "entt/EnttRuntimeApplication.h"

namespace ecs::benchmarks::entt {

    class EnttRuntimeBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entt", EnttRuntimeApplication, entities::EntityFactory> {
    public:
        EnttRuntimeBenchmark() = default;

        explicit EnttRuntimeBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTRUNTIMEBENCHMARK_H_
