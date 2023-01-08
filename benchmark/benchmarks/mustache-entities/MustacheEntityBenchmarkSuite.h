#ifndef ECS_BENCHMARKS_MUSTACHEENTITYBENCHMARK_H_
#define ECS_BENCHMARKS_MUSTACHEENTITYBENCHMARK_H_

#include "ECSBenchmark.h"
#include "mustache/MustacheApplication.h"
#include "mustache/entities/EntityFactory.h"
#include <utility>

namespace ecs::benchmarks::mustache {

class MustacheEntityBenchmarkSuite final
    : public ecs::benchmarks::base::ECSBenchmark<"mustache", MustacheApplication, entities::EntityFactory,
                                                 /*include_entity_benchmarks= */ true // application is needed to get
                                                                                      // entity manager
                                                 > {
public:
  MustacheEntityBenchmarkSuite() = default;

  explicit MustacheEntityBenchmarkSuite(ecs::benchmarks::base::ESCBenchmarkOptions options)
      : ECSBenchmark(std::move(options)) {}
};

} // namespace ecs::benchmarks::mustache

#endif // ECS_BENCHMARKS_MUSTACHEENTITYBENCHMARK_H_
