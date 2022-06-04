#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "entt/systems/DataSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/MovementSystem.h"
#include "entt/entities/EntityFactory.h"
#include "entt/EnttApplication.h"

namespace ecs::benchmarks::entt {

    class EnttBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entt", EnttApplication, entities::EntityFactory> {
    public:
        EnttBenchmark() = default;

        explicit EnttBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTBENCHMARK_H_