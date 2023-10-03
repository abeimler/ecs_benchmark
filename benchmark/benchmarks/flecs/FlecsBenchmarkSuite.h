#ifndef ECS_BENCHMARKS_FLECSBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSBENCHMARK_H_

#include "ECSBenchmark.h"
#include "flecs/FlecsApplication.h"
#include "flecs/entities/EntityFactory.h"
#include "flecs/entities/HeroMonsterEntityFactory.h"
#include "flecs/systems/DataSystem.h"
#include "flecs/systems/MoreComplexSystem.h"
#include "flecs/systems/MovementSystem.h"
#include <utility>


namespace ecs::benchmarks::flecs {

class FlecsBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"flecs", FlecsApplication, entities::EntityFactory,
                                                 entities::HeroMonsterEntityFactory> {
public:
  FlecsBenchmarkSuite() = default;

  explicit FlecsBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options) : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::flecs

#endif // ECS_BENCHMARKS_OPENECSBENCHMARK_H_
