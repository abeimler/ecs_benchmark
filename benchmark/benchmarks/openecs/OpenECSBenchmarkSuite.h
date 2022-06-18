#ifndef ECS_BENCHMARKS_OPENECSBENCHMARK_H_
#define ECS_BENCHMARKS_OPENECSBENCHMARK_H_

#include "ECSBenchmark.h"

#include <utility>

#include "openecs/systems/DataSystem.h"
#include "openecs/systems/MoreComplexSystem.h"
#include "openecs/systems/MovementSystem.h"
#include "openecs/entities/EntityFactory.h"
#include "openecs/OpenECSApplication.h"

namespace ecs::benchmarks::openecs {

    class OpenECSBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"openecs", OpenECSApplication, entities::EntityFactory> {
    public:
        OpenECSBenchmarkSuite() = default;

        explicit OpenECSBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_OPENECSBENCHMARK_H_
