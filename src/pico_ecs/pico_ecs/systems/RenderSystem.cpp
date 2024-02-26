#include "RenderSystem.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include "base/components/VelocityComponent.h"
#include <bit>
#include <cassert>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

auto RenderSystem::renderSprite(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t {
  (void)ecs;
  (void)dt;
  details::RenderSystemContext& context = *std::bit_cast<details::RenderSystemContext*>(udata);

  for (auto entity_id : entities) {
    const auto& position = *std::bit_cast<::ecs::benchmarks::base::components::PositionComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->PositionComponent));
    const auto& sprite = *std::bit_cast<::ecs::benchmarks::base::components::SpriteComponent*>(
        ecs_get(context.registry->ecs.get(), entity_id, context.registry->SpriteComponent));
    context.system->renderSprite(position, sprite);
  }

  return 0;
}

void RenderSystem::init(EntityManager& registry) {
  auto system_update = [](ecs_t* ecs, ecs_id_t* entities, int entity_count, ecs_dt_t dt, void* udata) -> ecs_ret_t {
    assert(entity_count >= 0);
    return renderSprite(ecs, std::span{entities, static_cast<size_t>(entity_count)}, dt, udata);
  };

  m_context = details::RenderSystemContext{
      .registry = &registry,
      .system = this,
  };
  m_system = ecs_register_system(registry.ecs.get(), system_update, nullptr, nullptr, &m_context);
  ecs_require_component(registry.ecs.get(), m_system, registry.PositionComponent);
  ecs_require_component(registry.ecs.get(), m_system, registry.SpriteComponent);
}

void RenderSystem::update(EntityManager& registry, TimeDelta dt) {
  ecs_update_system(registry.ecs.get(), m_system, dt);
}

} // namespace ecs::benchmarks::pico_ecs::systems