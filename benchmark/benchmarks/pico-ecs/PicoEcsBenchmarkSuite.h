#ifndef ECS_BENCHMARKS_PICOECSBENCHMARK_H_
#define ECS_BENCHMARKS_PICOECSBENCHMARK_H_

#include "ECSBenchmark.h"
#include "pico_ecs/PicoEcsApplication.h"
#include "pico_ecs/entities/EntityFactory.h"
#include "pico_ecs/entities/HeroMonsterEntityFactory.h"
#include "pico_ecs/systems/DataSystem.h"
#include "pico_ecs/systems/MoreComplexSystem.h"
#include "pico_ecs/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::pico_ecs {

class PicoEcsBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"pico_ecs", PicoEcsApplication,
                                                 entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  PicoEcsBenchmarkSuite() = default;

  explicit PicoEcsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::pico_ecs

#endif // ECS_BENCHMARKS_PICOECSBENCHMARK_H_
