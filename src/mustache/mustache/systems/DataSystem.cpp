#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::mustache::systems {

void DataSystem::update(::mustache::World& world, TimeDelta dt) {
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [dt](Entity /*entity*/, ecs::benchmarks::base::components::DataComponent& data) {
        updateData(data, dt);
      },
      run_mode);
}

void DataSystem::onUpdate(::mustache::World& world) {
  constexpr float dt = 1.0F / 60.0F;
  constexpr auto run_mode = ::mustache::JobRunMode::kCurrentThread;
  world.entities().forEach(
      [](Entity /*entity*/, ecs::benchmarks::base::components::DataComponent& data) {
        updateData(data, dt);
      },
      run_mode);
}

} // namespace ecs::benchmarks::mustache::systems