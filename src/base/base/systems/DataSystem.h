#ifndef ECS_BENCHMARKS_BASE_DATASYSTEM_H_
#define ECS_BENCHMARKS_BASE_DATASYSTEM_H_

#include "System.h"
#include "base/components/DataComponent.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <gsl-lite/gsl-lite.hpp>
#include <string>

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta,
          class DataComponent = ecs::benchmarks::base::components::DataComponent>
class DataSystem : public System<EntityManager, TimeDelta> {
public:
  DataSystem() = default;
  virtual ~DataSystem() = default;
  DataSystem(const DataSystem&) = delete;
  DataSystem& operator=(const DataSystem&) = delete;
  DataSystem(DataSystem&&) noexcept = default;
  DataSystem& operator=(DataSystem&&) noexcept = default;

  static void updateData(DataComponent& data, TimeDelta dt) {
    data.thingy = (data.thingy + 1) % 1'000'000;
    data.dingy += 0.0001 * gsl::narrow_cast<double>(dt);
    data.mingy = !data.mingy;
    data.numgy = data.rng();
  }
};

} // namespace ecs::benchmarks::base::systems

#endif