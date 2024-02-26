#ifndef ECS_BENCHMARKS_GAIA_ECS_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_RENDERSYSTEM_H_

#include "base/systems/RenderSystem.h"
#include <functional>
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class RenderSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::RenderSystem<EntityManager, TimeDelta>;

  /// @Note: gaia-ecs need default constructable
  // RenderSystem() = delete;
  // explicit RenderSystem(base::FrameBuffer& frameBuffer) : m_frameBuffer(frameBuffer) {}
  RenderSystem() = default; ///< @Note: don't forget to set m_frameBuffer reference
  void setFrameBuffer(base::FrameBuffer& frameBuffer) { m_frameBuffer = &frameBuffer; }

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::PositionComponent,
                   ecs::benchmarks::base::components::SpriteComponent>();
  }

  void OnUpdate() override {
    // constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](const ecs::benchmarks::base::components::PositionComponent& position,
                 const ecs::benchmarks::base::components::SpriteComponent& spr) {
      BaseSystem::renderSprite(*m_frameBuffer, position, spr);
    });
  }

private:
  ::gaia::ecs::Query m_q;
  // std::reference_wrapper<base::FrameBuffer> m_frameBuffer;
  base::FrameBuffer* m_frameBuffer;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
