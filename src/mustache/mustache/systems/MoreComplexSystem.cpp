#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::mustache::systems {

void MoreComplexSystem::update(::mustache::World& world, TimeDelta /*dt*/) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent& position,
          ecs::benchmarks::base::components::VelocityComponent& direction,
          ecs::benchmarks::base::components::DataComponent& data) {
        updateComponents(position, direction, data);
      },
      run_mode);
}
void MoreComplexSystem::onUpdate(::mustache::World& world) {
  //constexpr auto dt = 1.0F / 60.0F;
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [&](Entity /*entity*/, ecs::benchmarks::base::components::PositionComponent& position,
          ecs::benchmarks::base::components::VelocityComponent& direction,
          ecs::benchmarks::base::components::DataComponent& data) {
        updateComponents(position, direction, data);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems