#ifndef ECS_BENCHMARKS_FLECSENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_FLECSENTITYBENCHMARK_H_

#include "EntityBenchmark.h"
#include "flecs/entities/EntityFactory.h"
#include <utility>


namespace ecs::benchmarks::flecs {

class FlecsEntityBenchmarkSuite final
    : public ecs::benchmarks::base::EntityBenchmark<"flecs", entities::EntityFactory> {
public:
  FlecsEntityBenchmarkSuite() = default;

  explicit FlecsEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : EntityBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::flecs

#endif // ECS_BENCHMARKS_FLECSENTITYBENCHMARK_H_
