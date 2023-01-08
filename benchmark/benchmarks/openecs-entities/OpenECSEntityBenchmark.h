#ifndef ECS_BENCHMARKS_OPENECSENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_OPENECSENTITYBENCHMARK_H_

#include "EntityBenchmark.h"
#include "openecs/entities/EntityFactory.h"
#include <utility>

namespace ecs::benchmarks::openecs {

class OpenECSEntityBenchmarkSuite final
    : public ecs::benchmarks::base::EntityBenchmark<"openecs", entities::EntityFactory> {
public:
  OpenECSEntityBenchmarkSuite() = default;

  explicit OpenECSEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : EntityBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::openecs

#endif // ECS_BENCHMARKS_OPENECSENTITYBENCHMARK_H_
