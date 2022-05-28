#ifndef ECS_BENCHMARKS_FLECSBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSBENCHMARK_H_

#include "ECSBenchmark.h"

#include <utility>

#include "flecs/systems/DataSystem.h"
#include "flecs/systems/MoreComplexSystem.h"
#include "flecs/systems/MovementSystem.h"
#include "flecs/entities/EntityFactory.h"
#include "flecs/FlecsApplication.h"

namespace ecs::benchmarks::flecs {

    class FlecsBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"flecs", FlecsApplication, entities::EntityFactory> {
    public:
        FlecsBenchmark() = default;

        explicit FlecsBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(
                std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_OPENECSBENCHMARK_H_
