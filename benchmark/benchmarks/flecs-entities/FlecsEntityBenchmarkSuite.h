#ifndef ECS_BENCHMARKS_FLECSENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSENTITYBENCHMARK_H_

#include <utility>

#include "flecs/entities/EntityFactory.h"

#include "EntityBenchmark.h"


namespace ecs::benchmarks::flecs {

    class FlecsEntityBenchmarkSuite final
            : public ecs::benchmarks::base::EntityBenchmark<"flecs", entities::EntityFactory> {
    public:
        FlecsEntityBenchmarkSuite() = default;

        explicit FlecsEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : EntityBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_FLECSENTITYBENCHMARK_H_
