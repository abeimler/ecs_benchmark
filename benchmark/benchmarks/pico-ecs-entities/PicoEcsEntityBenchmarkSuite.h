#ifndef ECS_BENCHMARKS_PICOECSENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_PICOECSENTITYBENCHMARK_H_

#include "ECSBenchmark.h"
#include "pico_ecs/PicoEcsApplication.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <utility>

namespace ecs::benchmarks::pico_ecs {

class PicoEcsEntityBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"pico_ecs", PicoEcsApplication, entities::EntityFactory,
                                                 /*include_entity_benchmarks= */ true // application is needed to get
                                                                                      // entity manager
                                                 > {
public:
  PicoEcsEntityBenchmarkSuite() = default;

  explicit PicoEcsEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::pico_ecs

#endif // ECS_BENCHMARKS_PICOECSENTITYBENCHMARK_H_
