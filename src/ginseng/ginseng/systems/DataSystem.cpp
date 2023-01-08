#include "DataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::ginseng::systems {

void DataSystem::update(EntityManager& registry, TimeDelta dt) {
  registry.visit([dt](ecs::benchmarks::base::components::DataComponent& data) {
    updateData(data, dt);
  });
}

} // namespace ecs::benchmarks::ginseng::systems