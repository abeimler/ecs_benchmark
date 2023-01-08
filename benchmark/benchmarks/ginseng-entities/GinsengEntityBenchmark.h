#ifndef ECS_BENCHMARKS_GINSENGENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_GINSENGENTITYBENCHMARK_H_

#include "EntityBenchmark.h"
#include "ginseng/entities/EntityFactory.h"
#include <utility>

namespace ecs::benchmarks::ginseng {

class GinsengEntityBenchmark final : public ecs::benchmarks::base::EntityBenchmark<"ginseng", entities::EntityFactory> {
public:
  GinsengEntityBenchmark() = default;

  explicit GinsengEntityBenchmark(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : EntityBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::ginseng

#endif // ECS_BENCHMARKS_GINSENGENTITYBENCHMARK_H_
