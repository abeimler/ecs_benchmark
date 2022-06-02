#ifndef ECS_BENCHMARKS_ENTITYXBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITYXBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "entityx/systems/DataSystem.h"
#include "entityx/systems/MoreComplexSystem.h"
#include "entityx/systems/MovementSystem.h"
#include "entityx/entities/EntityFactory.h"
#include "entityx/EntityXApplication.h"

namespace ecs::benchmarks::entityx {

    class EntityXBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entityx", EntityXApplication, entities::EntityFactory> {
    public:
        EntityXBenchmark() = default;

        explicit EntityXBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTITYXBENCHMARK_H_
