#ifndef ECS_BENCHMARKS_FLECSBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSBENCHMARK_H_

#include <utility>

#include "flecs/systems/DataSystem.h"
#include "flecs/systems/MoreComplexSystem.h"
#include "flecs/systems/MovementSystem.h"
#include "flecs/entities/EntityFactory.h"
#include "flecs/FlecsApplication.h"

#include "ECSBenchmark.h"


namespace ecs::benchmarks::flecs {

    class FlecsBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"flecs", FlecsApplication, entities::EntityFactory> {
    public:
        FlecsBenchmarkSuite() = default;

        explicit FlecsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_OPENECSBENCHMARK_H_
