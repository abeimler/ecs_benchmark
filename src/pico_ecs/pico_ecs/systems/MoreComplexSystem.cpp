#include "MoreComplexSystem.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto MoreComplexSystem::updateMoreComplex(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata)
    -> ecs_ret_t {
  (void)ecs;
  (void)dt;
  EntityManager& uregistry = *std::bit_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& position = *std::bit_cast<ecs::benchmarks::base::components::PositionComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.PositionComponent));
    auto& direction = *std::bit_cast<ecs::benchmarks::base::components::VelocityComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.VelocityComponent));
    auto& data = *std::bit_cast<ecs::benchmarks::base::components::DataComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.DataComponent));
    BaseSystem::updateComponents(position, direction, data);
  }

  return 0;
}
void MoreComplexSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return updateMoreComplex(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
  };

  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.PositionComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.VelocityComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.DataComponent);
}
void MoreComplexSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems