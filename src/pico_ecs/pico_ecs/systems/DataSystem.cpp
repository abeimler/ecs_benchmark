#include "DataSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::pico_ecs::systems {

void DataSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    (void)ecs;
    (void)dt;
    EntityManager& uregistry = *reinterpret_cast<EntityManager*>(udata);

    for (int id = 0; id < entity_count; id++) {
      auto entity_id = entities[id];
      auto& data = *reinterpret_cast<ecs::benchmarks::base::components::DataComponent*>(
          ecs_get(uregistry.ecs.get(), entity_id, uregistry.DataComponent));
      DataSystem::updateData(data, dt);
    }

    return 0;
  };

  /// @NOTE: lets hope registry is still alive :)
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.DataComponent);
}

void DataSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems