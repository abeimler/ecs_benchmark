#ifndef ECS_BENCHMARKS_GAIA_ECS_BENCHMARK_H_
#define ECS_BENCHMARKS_GAIA_ECS_BENCHMARK_H_

#include "ECSBenchmark.h"
#include "gaia-ecs/GaiaEcsApplication.h"
#include "gaia-ecs/entities/EntityFactory.h"
#include "gaia-ecs/entities/HeroMonsterEntityFactory.h"
#include "gaia-ecs/systems/DataSystem.h"
#include "gaia-ecs/systems/MoreComplexSystem.h"
#include "gaia-ecs/systems/MovementSystem.h"
#include <utility>


namespace ecs::benchmarks::gaia_ecs {

class GaiaEcsBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"gaia-ecs", GaiaEcsApplication, entities::EntityFactory,
                                                 entities::HeroMonsterEntityFactory> {
public:
  GaiaEcsBenchmarkSuite() = default;

  explicit GaiaEcsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::gaia_ecs

#endif // ECS_BENCHMARKS_GAIA_ECS_BENCHMARK_H_
