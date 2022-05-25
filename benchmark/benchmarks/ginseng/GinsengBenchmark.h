#ifndef ECS_BENCHMARKS_GINSENGBENCHMARK_H_
#define ECS_BENCHMARKS_GINSENGBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "ginseng/systems/DataSystem.h"
#include "ginseng/systems/MoreComplexSystem.h"
#include "ginseng/systems/MovementSystem.h"
#include "ginseng/entities/EntityFactory.h"
#include "ginseng/GinsengApplication.h"

namespace ecs::benchmarks::ginseng {

    class GinsengBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"ginseng", GinsengApplication, entities::EntityFactory> {
    public:
        GinsengBenchmark() = default;

        explicit GinsengBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTBENCHMARK_H_
