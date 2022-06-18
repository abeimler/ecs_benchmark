#ifndef ECS_BENCHMARKS_ENTTGROUPBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTGROUPBENCHMARK_H_

#include <utility>

#include "entt/entities/EntityFactory.h"
#include "entt/EnttGroupApplication.h"

#include "ExtendedECSBenchmark.h"

namespace ecs::benchmarks::entt {

    class EnttGroupBenchmarkSuite final
            : public ecs::benchmarks::base::ExtendedECSBenchmark<"entt (group)", EnttGroupApplication, entities::EntityFactory> {
    public:
        EnttGroupBenchmarkSuite() = default;

        explicit EnttGroupBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ExtendedECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTGROUPBENCHMARK_H_
