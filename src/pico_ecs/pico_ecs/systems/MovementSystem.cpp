#include "MovementSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::pico_ecs::systems {

void MovementSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    (void)ecs;
    (void)dt;
    EntityManager& uregistry = *reinterpret_cast<EntityManager*>(udata);

    for (int id = 0; id < entity_count; id++) {
      auto entity_id = entities[id];
      auto& position = *reinterpret_cast<ecs::benchmarks::base::components::PositionComponent*>(
          ecs_get(uregistry.ecs.get(), entity_id, uregistry.PositionComponent));
      auto& direction = *reinterpret_cast<ecs::benchmarks::base::components::VelocityComponent*>(
          ecs_get(uregistry.ecs.get(), entity_id, uregistry.VelocityComponent));
      MovementSystem::updatePosition(position, direction, dt);
    }

    return 0;
  };

  /// @NOTE: lets hope registry is still alive :)
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.PositionComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.VelocityComponent);
}

void MovementSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems