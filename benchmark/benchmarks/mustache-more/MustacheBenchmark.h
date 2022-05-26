#ifndef ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
#define ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "mustache/systems/DataSystem.h"
#include "mustache/systems/MoreComplexSystem.h"
#include "mustache/systems/MovementSystem.h"
#include "mustache/entities/EntityFactory.h"
#include "mustache/MustacheApplication.h"

namespace ecs::benchmarks::mustache {

    class MustacheBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"mustache", MustacheApplication, entities::EntityFactory> {
    public:
        MustacheBenchmark() = default;

        explicit MustacheBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(
                std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
