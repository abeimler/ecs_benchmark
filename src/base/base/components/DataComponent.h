#ifndef ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_
#define ECS_BENCHMARKS_BASE_COMPONENTS_DATACOMPONENT_H_

#include "base/random.h"
#include <cstdint>

namespace ecs::benchmarks::base::components {

struct DataComponent {
  inline static constexpr uint32_t DefaultSeed = 340383L;

  int thingy{0};
  double dingy{0.0};
  bool mingy{false};

  uint32_t seed{DefaultSeed};
  random_xoshiro128 rng;
  uint32_t numgy;

  DataComponent() : rng(seed), numgy(rng()) {}
};

} // namespace ecs::benchmarks::base::components

#endif