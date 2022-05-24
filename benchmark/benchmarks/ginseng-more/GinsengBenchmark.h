#ifndef ECS_BENCHMARKS_GINSENGBENCHMARK_H_
#define ECS_BENCHMARKS_GINSENGBENCHMARK_H_

#include "ECSBenchmark.h"

#include "ginseng/systems/ComflabSystem.h"
#include "ginseng/systems/MoreComplexSystem.h"
#include "ginseng/systems/MovementSystem.h"
#include "ginseng/entities/EntityFactory.h"
#include "ginseng/GinsengApplication.h"

namespace ecs::benchmarks::ginseng {

    class GinsengBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"ginseng", GinsengApplication, entities::EntityFactory> {
    public:
        GinsengBenchmark() = default;

        explicit GinsengBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(options) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTBENCHMARK_H_
