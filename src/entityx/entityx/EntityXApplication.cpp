#include "EntityXApplication.h"
#include "entityx/systems/DataSystem.h"
#include "entityx/systems/MoreComplexSystem.h"
#include "entityx/systems/MovementSystem.h"
#include "entityx/systems/DamageSystem.h"
#include "entityx/systems/HealthSystem.h"
#include "entityx/systems/SpriteSystem.h"

namespace ecs::benchmarks::entityx {

void EntityXApplication::init() {
  systems.add<systems::MovementSystem>();
  systems.add<systems::DataSystem>();
  if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
    systems.add<systems::MoreComplexSystem>();
    systems.add<systems::HealthSystem>();
    systems.add<systems::DamageSystem>();
    systems.add<systems::SpriteSystem>();
  }
  systems.configure();
}

void EntityXApplication::uninit() {
}

void EntityXApplication::update(TimeDelta dt) {
  systems.update<systems::MovementSystem>(dt);
  systems.update<systems::DataSystem>(dt);
  if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
    systems.update<systems::MoreComplexSystem>(dt);
    systems.update<systems::HealthSystem>(dt);
    systems.update<systems::DamageSystem>(dt);
    systems.update<systems::SpriteSystem>(dt);
  }
}
} // namespace ecs::benchmarks::entityx