#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include <utility>

#include "entt/systems/DataSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/MovementSystem.h"
#include "entt/entities/EntityFactory.h"
#include "entt/EnttApplication.h"

#include "ECSBenchmark.h"


namespace ecs::benchmarks::entt {

    class EnttBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"entt", EnttApplication, entities::EntityFactory> {
    public:
        EnttBenchmarkSuite() = default;

        explicit EnttBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTBENCHMARK_H_
