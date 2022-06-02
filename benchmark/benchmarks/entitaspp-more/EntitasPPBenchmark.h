#ifndef ECS_BENCHMARKS_ENTITASPPBENCHMARK_H_
#define ECS_BENCHMARKS_ENTITASPPBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "EntitasPP/systems/DataSystem.h"
#include "EntitasPP/systems/MoreComplexSystem.h"
#include "EntitasPP/systems/MovementSystem.h"
#include "EntitasPP/entities/EntityFactory.h"
#include "EntitasPP/EntitasPPApplication.h"

namespace ecs::benchmarks::EntitasPP {

    class EntitasPPBenchmark final
            : public ecs::benchmarks::base::ESCBenchmark<"EntitasPP", EntitasPPApplication, entities::EntityFactory> {
    public:
        EntitasPPBenchmark() = default;

        explicit EntitasPPBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options) : ESCBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_ENTITASPPBENCHMARK_H_
