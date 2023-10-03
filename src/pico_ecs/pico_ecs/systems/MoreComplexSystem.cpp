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
  details::MoreComplexSystemContext& context = *std::bit_cast<details::MoreComplexSystemContext*>(udata);

  assert(context.registry);
  assert(context.system);

  for (auto entity_id : entities) {
    auto& position = *std::bit_cast<ecs::benchmarks::base::components::PositionComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->PositionComponent));
    auto& direction = *std::bit_cast<ecs::benchmarks::base::components::VelocityComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->VelocityComponent));
    auto& data = *std::bit_cast<ecs::benchmarks::base::components::DataComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->DataComponent));
    context.system->updateComponents(position, direction, data);
  }

  return 0;
}
void MoreComplexSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return updateMoreComplex(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
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
void MoreComplexSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}


auto HealthSystem::updateHealth(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t {
  (void)ecs;
  (void)dt;
  EntityManager& uregistry = *std::bit_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& health = *std::bit_cast<ecs::benchmarks::base::components::HealthComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.HealthComponent));
    ::ecs::benchmarks::base::systems::HealthSystem<EntityManager, TimeDelta>::updateHealth(health);
  }

  return 0;
}
void HealthSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return updateHealth(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
  };

  /// @NOTE: lets hope registry is still alive :)
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.HealthComponent);
}
void HealthSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

auto DamageSystem::updateDamage(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t {
  (void)ecs;
  (void)dt;
  EntityManager& uregistry = *std::bit_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& health = *std::bit_cast<ecs::benchmarks::base::components::HealthComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.HealthComponent));
    const auto& damage = *std::bit_cast<ecs::benchmarks::base::components::DamageComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.DamageComponent));
    ::ecs::benchmarks::base::systems::DamageSystem<EntityManager, TimeDelta>::updateDamage(health, damage);
  }

  return 0;
}
void DamageSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return updateDamage(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
  };

  /// @NOTE: lets hope registry is still alive :)
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.HealthComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.DamageComponent);
}
void DamageSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems