#ifndef ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::flecs::systems {

class MoreComplexSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;

  static int random(int min, int max) {
    std::uniform_int_distribution<int> distr(min, max);
    return distr(m_eng);
  }

  inline static const auto update = [](::flecs::iter& /*it*/, size_t /*index*/,
                                       ecs::benchmarks::base::components::PositionComponent& position,
                                       ecs::benchmarks::base::components::VelocityComponent& direction,
                                       ecs::benchmarks::base::components::DataComponent& data) {
    // const TimeDelta dt = it.delta_time();
    if ((data.thingy % 10) == 0) {
      if (position.x > position.y) {
        direction.x = static_cast<float>(random(-5, 5));
        direction.y = static_cast<float>(random(-10, 10));
      } else {
        direction.x = static_cast<float>(random(-10, 10));
        direction.y = static_cast<float>(random(-5, 5));
      }
    }
  };

private:
  static std::random_device m_rd;
  static std::mt19937 m_eng;
};

} // namespace ecs::benchmarks::flecs::systems

#endif