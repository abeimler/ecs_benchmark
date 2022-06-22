#ifndef ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_

#include <utility>

#include "entt/entities/EntityFactory.h"

#include "EntityBenchmark.h"


namespace ecs::benchmarks::entt {

    class EnttEntityBenchmarkSuite final
            : public ecs::benchmarks::base::EntityBenchmark<"entt", entities::EntityFactory> {
    public:
        EnttEntityBenchmarkSuite() = default;

        explicit EnttEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : EntityBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_
