#ifndef ECS_BENCHMARKS_BASE_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_BASE_RENDERSYSTEM_H_

#include "System.h"
#include "base/FrameBuffer.h"
#include "base/components/PositionComponent.h"
#include "base/components/SpriteComponent.h"
#include <functional>

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta>
class RenderSystem : public System<EntityManager, TimeDelta> {
public:
  RenderSystem() = delete;
  explicit RenderSystem(FrameBuffer& frameBuffer) : m_frameBuffer(frameBuffer) {}
  virtual ~RenderSystem() = default;
  RenderSystem(const RenderSystem&) = delete;
  RenderSystem& operator=(const RenderSystem&) = delete;
  RenderSystem(RenderSystem&&) noexcept = default;
  RenderSystem& operator=(RenderSystem&&) noexcept = default;

  template <class tFrameBuffer>
  static void renderSprite(tFrameBuffer& frameBuffer,
                           const ecs::benchmarks::base::components::PositionComponent& position,
                           const ecs::benchmarks::base::components::SpriteComponent& spr) {
    frameBuffer.draw(gsl::narrow_cast<int>(position.x), gsl::narrow_cast<int>(position.y), spr.character);
  }
  void renderSprite(const ecs::benchmarks::base::components::PositionComponent& position,
                    const ecs::benchmarks::base::components::SpriteComponent& spr) {
    renderSprite(m_frameBuffer.get(), position, spr);
  }

protected:
  std::reference_wrapper<FrameBuffer> m_frameBuffer;
};

} // namespace ecs::benchmarks::base::systems

#endif