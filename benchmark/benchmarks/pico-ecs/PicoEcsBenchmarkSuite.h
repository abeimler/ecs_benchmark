#ifndef ECS_BENCHMARKS_PICOECSBENCHMARK_H_
#define ECS_BENCHMARKS_PICOECSBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "pico_ecs/systems/DataSystem.h"
#include "pico_ecs/systems/MoreComplexSystem.h"
#include "pico_ecs/systems/MovementSystem.h"
#include "pico_ecs/entities/EntityFactory.h"
#include "pico_ecs/PicoEcsApplication.h"

namespace ecs::benchmarks::pico_ecs {

    class PicoEcsBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"pico_ecs", PicoEcsApplication, entities::EntityFactory> {
    public:
      PicoEcsBenchmarkSuite() = default;

        explicit PicoEcsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_PICOECSBENCHMARK_H_
