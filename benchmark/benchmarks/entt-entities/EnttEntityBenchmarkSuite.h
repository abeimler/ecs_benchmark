#ifndef ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_

#include "EntityBenchmark.h"
#include "entt/entities/EntityFactory.h"
#include <utility>


namespace ecs::benchmarks::entt {

class EnttEntityBenchmarkSuite final : public ecs::benchmarks::base::EntityBenchmark<"entt", entities::EntityFactory> {
public:
  EnttEntityBenchmarkSuite() = default;

  explicit EnttEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : EntityBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTTENTITYBENCHMARK_H_
