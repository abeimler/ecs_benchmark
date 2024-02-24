#include "SpriteSystem.h"
#include "base/components/HeroMonsterComponents.h"
#include "base/components/SpriteComponent.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto SpriteSystem::updateSprite(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t {
  (void)ecs;
  (void)dt;
  EntityManager& uregistry = *std::bit_cast<EntityManager*>(udata);

  for (auto entity_id : entities) {
    auto& spr = *std::bit_cast<::ecs::benchmarks::base::components::SpriteComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.SpriteComponent));
    const auto& player = *std::bit_cast<::ecs::benchmarks::base::components::PlayerComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.PlayerComponent));
    const auto& health = *std::bit_cast<::ecs::benchmarks::base::components::HealthComponent*>(
        ecs_get(uregistry.ecs.get(), entity_id, uregistry.HealthComponent));
    BaseSystem::updateSprite(spr, player, health);
  }

  return 0;
}

void SpriteSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return updateSprite(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
  };

  /// @NOTE: lets hope registry is still alive :)
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &registry);
  ecs_require_component(registry.ecs.get(), m_system, registry.SpriteComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.PlayerComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.HealthComponent);
}

void SpriteSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems