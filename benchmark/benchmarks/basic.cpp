#include "basic.h"

namespace ecs::benchmarks::base {

void BEDefaultArguments(benchmark::internal::Benchmark* b) {
  b->ArgsProduct({
      benchmark::CreateRange(MIN_ENTITIES_RANGE, MAX_ENTITIES_RANGE, /*multi=*/2),
  });
}

void BESmallArguments(benchmark::internal::Benchmark* b) {
  b->ArgsProduct({
      benchmark::CreateRange(MIN_ENTITIES_RANGE, SMALL_MAX_ENTITIES_RANGE, /*multi=*/2),
  });
}

} // namespace ecs::benchmarks::base