#ifndef ECS_BENCHMARKS_ENTITYXBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITYXBENCHMARK_H_

#include "ECSBenchmark.h"

#include "entityx/systems/ComflabSystem.h"
#include "entityx/systems/MoreComplexSystem.h"
#include "entityx/systems/MovementSystem.h"
#include "entityx/entities/EntityFactory.h"
#include "entityx/EntityXApplication.h"

namespace ecs::benchmarks::entityx {

    class EnttBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entityx", EntityXApplication, entities::EntityFactory> {
    public:
        constexpr EnttBenchmark() = default;
        explicit EnttBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(options) {}
    };

}

#endif //ECS_BENCHMARKS_ENTITYXBENCHMARK_H_
