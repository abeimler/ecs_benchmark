#ifndef ECS_BENCHMARKS_PICOECSENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_PICOECSENTITYBENCHMARK_H_

#include <utility>

#include "ECSBenchmark.h"

#include "pico_ecs/entities/EntityFactory.h"
#include "pico_ecs/PicoEcsApplication.h"

namespace ecs::benchmarks::pico_ecs {

    class PicoEcsEntityBenchmarkSuite final
            : public ecs::benchmarks::base::ECSBenchmark<"pico_ecs",
                                                 PicoEcsApplication, entities::EntityFactory,
                    /*include_entity_benchmarks= */true // application is needed to get entity manager
            > {
    public:
      PicoEcsEntityBenchmarkSuite() = default;

        explicit PicoEcsEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
            : ECSBenchmark(std::move(options)) {}
    };

}

#endif //ECS_BENCHMARKS_PICOECSENTITYBENCHMARK_H_
