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

    class MustacheBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"mustache", MustacheApplication, entities::EntityFactory> {
    public:
        MustacheBenchmarkSuite() = default;

        explicit MustacheBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
