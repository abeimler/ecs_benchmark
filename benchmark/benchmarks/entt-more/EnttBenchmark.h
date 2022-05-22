#ifndef ECS_BENCHMARKS_ENTTBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTBENCHMARK_H_

#include "ECSBenchmark.h"

#include "entt/systems/ComflabSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/MovementSystem.h"
#include "entt/entities/EntityFactory.h"
#include "entt/EnttApplication.h"

namespace ecs::benchmarks::entt {

    class EnttBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entt", EnttApplication, entities::EntityFactory> {
    public:
        constexpr EnttBenchmark() = default;
        explicit EnttBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(options) {}
    };

}

#endif //ECS_BENCHMARKS_ENTTBENCHMARK_H_
