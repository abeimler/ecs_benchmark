#ifndef ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
#define ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_

#include "ECSBenchmark.h"
#include "mustache/MustacheApplication.h"
#include "mustache/entities/EntityFactory.h"
#include "mustache/systems/DataSystem.h"
#include "mustache/systems/MoreComplexSystem.h"
#include "mustache/systems/MovementSystem.h"
#include <utility>

namespace ecs::benchmarks::mustache {

class MustacheBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"mustache", MustacheApplication, entities::EntityFactory> {
public:
  MustacheBenchmarkSuite() = default;

  explicit MustacheBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::mustache

#endif // ECS_BENCHMARKS_MUSTACHEBENCHMARK_H_
