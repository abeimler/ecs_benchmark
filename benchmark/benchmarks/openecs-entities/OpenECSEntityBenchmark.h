#ifndef ECS_BENCHMARKS_OPENECSENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_OPENECSENTITYBENCHMARK_H_

#include <utility>

#include "EntityBenchmark.h"

#include "openecs/entities/EntityFactory.h"

namespace ecs::benchmarks::openecs {

    class OpenECSEntityBenchmarkSuite final
            : public ecs::benchmarks::base::EntityBenchmark<"openecs", entities::EntityFactory> {
    public:
        OpenECSEntityBenchmarkSuite() = default;

        explicit OpenECSEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
            : EntityBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_OPENECSENTITYBENCHMARK_H_
