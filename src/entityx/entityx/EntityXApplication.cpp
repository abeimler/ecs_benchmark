#include "EntityXApplication.h"

namespace ecs::benchmarks::entityx {
void EntityXApplication::init() {
  systems.add<systems::MovementSystem>();
  systems.add<systems::DataSystem>();
  if (m_add_more_complex_system) {
    systems.add<systems::MoreComplexSystem>();
  }
  systems.configure();
}

void EntityXApplication::uninit() {
}

void EntityXApplication::update(TimeDelta dt) {
  systems.update<systems::MovementSystem>(dt);
  systems.update<systems::DataSystem>(dt);
  if (m_add_more_complex_system) {
    systems.update<systems::MoreComplexSystem>(dt);
  }
}
} // namespace ecs::benchmarks::entityx