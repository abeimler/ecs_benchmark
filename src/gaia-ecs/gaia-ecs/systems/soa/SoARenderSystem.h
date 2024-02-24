#ifndef ECS_BENCHMARKS_GAIA_ECS_SOARENDERSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOARENDERSYSTEM_H_

#include "base/systems/RenderSystem.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include <functional>
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class SoARenderSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::RenderSystem<EntityManager, TimeDelta>;

  /// @Note: gaia-ecs need default constructable
  // SoARenderSystem() = delete;
  // explicit SoARenderSystem(base::FrameBuffer& frameBuffer) : m_frameBuffer(frameBuffer) {}
  SoARenderSystem() = default; ///< @Note: don't forget to set m_frameBuffer reference
  void setFrameBuffer(base::FrameBuffer& frameBuffer) { m_frameBuffer = &frameBuffer; }

  void OnCreated() override {
    m_q = world().query().all<components::SoAPositionComponent, ecs::benchmarks::base::components::SpriteComponent>();
  }

  void OnUpdate() override {
    // constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](::gaia::ecs::Iter iter) {
      // Position
      auto vp = iter.view<components::SoAPositionComponent>(); // read-only access to PositionSoA
      auto px = vp.get<0>();                                   // continuous block of "x" from PositionSoA
      auto py = vp.get<1>();                                   // continuous block of "y" from PositionSoA

      // Sprite
      auto vs = iter.view<ecs::benchmarks::base::components::SpriteComponent>();

      /// @Note: code from RenderSystem::renderSprite
      GAIA_EACH(iter) m_frameBuffer->draw(gsl::narrow_cast<int>(px[i]), gsl::narrow_cast<int>(py[i]), vs[i].character);
    });
  }

private:
  ::gaia::ecs::Query m_q;
  // std::reference_wrapper<base::FrameBuffer> m_frameBuffer;
  base::FrameBuffer* m_frameBuffer{nullptr};
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
