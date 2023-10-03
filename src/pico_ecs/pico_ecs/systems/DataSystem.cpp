#include "DataSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto DataSystem::updateData(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t {
  (void)ecs;
  (void)dt;
  EntityManager& uregistry = *std::bit_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& data = *std::bit_cast<::ecs::benchmarks::base::components::DataComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.DataComponent));
    ::ecs::benchmarks::base::systems::DataSystem<EntityManager, TimeDelta>::updateData(data, dt);
  }

  return 0;
}

void DataSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return updateData(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
  };

  /// @NOTE: lets hope registry is still alive :)
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.DataComponent);
}

void DataSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems