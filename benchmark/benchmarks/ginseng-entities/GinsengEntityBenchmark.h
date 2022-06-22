#ifndef ECS_BENCHMARKS_GINSENGENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_GINSENGENTITYBENCHMARK_H_

#include <utility>

#include "EntityBenchmark.h"

#include "ginseng/entities/EntityFactory.h"

namespace ecs::benchmarks::ginseng {

    class GinsengEntityBenchmark final
            : public ecs::benchmarks::base::EntityBenchmark<"ginseng", entities::EntityFactory> {
    public:
        GinsengEntityBenchmark() = default;

        explicit GinsengEntityBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : EntityBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_GINSENGENTITYBENCHMARK_H_
