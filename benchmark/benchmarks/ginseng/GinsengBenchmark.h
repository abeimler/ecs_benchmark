#ifndef ECS_BENCHMARKS_GINSENGBENCHMARK_H_
#define ECS_BENCHMARKS_GINSENGBENCHMARK_H_

#include "ECSBenchmark.h"
#include "ginseng/GinsengApplication.h"
#include "ginseng/entities/EntityFactory.h"
#include "ginseng/entities/HeroMonsterEntityFactory.h"
#include "ginseng/systems/DataSystem.h"
#include "ginseng/systems/MoreComplexSystem.h"
#include "ginseng/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::ginseng {

class GinsengBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"ginseng", GinsengApplication,
                                                 entities::EntityFactory, entities::HeroMonsterEntityFactory> {
public:
  GinsengBenchmarkSuite() = default;

  explicit GinsengBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::ginseng

#endif // ECS_BENCHMARKS_GINSENGBENCHMARK_H_
