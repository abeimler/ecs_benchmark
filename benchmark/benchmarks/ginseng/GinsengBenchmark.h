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

    class GinsengBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"ginseng", GinsengApplication, entities::EntityFactory> {
    public:
        GinsengBenchmarkSuite() = default;

        explicit GinsengBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_GINSENGBENCHMARK_H_
