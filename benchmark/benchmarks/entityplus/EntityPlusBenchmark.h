#ifndef ECS_BENCHMARKS_ENTITYPLUSBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITYPLUSBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "entityplus/systems/DataSystem.h"
#include "entityplus/systems/MoreComplexSystem.h"
#include "entityplus/systems/MovementSystem.h"
#include "entityplus/entities/EntityFactory.h"
#include "entityplus/EntityPlusApplication.h"

namespace ecs::benchmarks::entityplus {

    class EntityPlusBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"entityplus", EntityPlusApplication, entities::EntityFactory> {
    public:
        EntityPlusBenchmark() = default;

        explicit EntityPlusBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTITYPLUSBENCHMARK_H_
