#include "MoreComplexSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"
#include <cassert>

namespace ecs::benchmarks::pico_ecs::systems {

void MoreComplexSystem::init(EntityManager &registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    (void)ecs;
    (void)dt;
    details::MoreComplexSystemContext& context = *reinterpret_cast<details::MoreComplexSystemContext*>(udata);

    assert(context.registry);
    assert(context.system);

    for (int id = 0; id < entity_count; id++) {
      auto entity_id = entities[id];
      auto& position = *reinterpret_cast<ecs::benchmarks::base::components::PositionComponent*>(ecs_get(context.registry->ecs.get(), entity_id, context.registry->PositionComponent));
      auto& direction = *reinterpret_cast<ecs::benchmarks::base::components::VelocityComponent*>(ecs_get(context.registry->ecs.get(), entity_id, context.registry->VelocityComponent));
      auto& data = *reinterpret_cast<ecs::benchmarks::base::components::DataComponent*>(ecs_get(context.registry->ecs.get(), entity_id, context.registry->DataComponent));
      context.system->updateComponents(position, direction, data);
    }

    return 0;
  };

  /// @NOTE: lets hope registry is still alive :)
  m_context = details::MoreComplexSystemContext{
      .registry = &registry,
      .system = this,
  };
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &m_context);
  ecs_require_component(registry.ecs.get(), m_system, registry.PositionComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.VelocityComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.DataComponent);
}

void MoreComplexSystem::update(EntityManager &registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

}