#ifndef ECS_BENCHMARKS_BASE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_BASE_MORECOMPLEXSYSTEM_H_

#include "System.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include <gsl/gsl-lite.hpp>

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta,
          class PositionComponent = ecs::benchmarks::base::components::PositionComponent,
          class DirectionComponent = ecs::benchmarks::base::components::VelocityComponent,
          class DataComponent = ecs::benchmarks::base::components::DataComponent>
class MoreComplexSystem : public System<EntityManager, TimeDelta> {
public:
  MoreComplexSystem() = default;
  virtual ~MoreComplexSystem() = default;
  MoreComplexSystem(const MoreComplexSystem&) = delete;
  MoreComplexSystem& operator=(const MoreComplexSystem&) = delete;
  MoreComplexSystem(MoreComplexSystem&&) noexcept = default;
  MoreComplexSystem& operator=(MoreComplexSystem&&) noexcept = default;

  static void updateComponents(const PositionComponent& position, DirectionComponent& direction, DataComponent& data) {
    if ((data.thingy % 10) == 0) {
      if (position.x > position.y) {
        direction.x = gsl::narrow_cast<float>(data.rng.range(3, 19)) - 10.0F;
        direction.y = gsl::narrow_cast<float>(data.rng.range(0, 5));
      } else {
        direction.x = gsl::narrow_cast<float>(data.rng.range(0, 5));
        direction.y = gsl::narrow_cast<float>(data.rng.range(3, 19)) - 10.0F;
      }
    }
  }
};

} // namespace ecs::benchmarks::base::systems

#endif