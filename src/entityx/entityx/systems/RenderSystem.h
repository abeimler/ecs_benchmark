#ifndef ECS_BENCHMARKS_ENTITYX_RENDER_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTITYX_RENDER_MORECOMPLEXSYSTEM_H_

#include "base/FrameBuffer.h"
#include "base/systems/RenderSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::systems {

class RenderSystem final : public ::entityx::System<RenderSystem>,
                           base::systems::RenderSystem<::entityx::EntityManager, float> {
public:
  using EventManager = ::entityx::EventManager;

  RenderSystem() = delete;
  explicit RenderSystem(base::FrameBuffer& frameBuffer)
      : ecs::benchmarks::base::systems::RenderSystem<::entityx::EntityManager, float>(frameBuffer) {}

  void update(EntityManager& entities, EventManager& events, TimeDelta dt) override;
  void update(EntityManager& entities, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entityx::systems

#endif