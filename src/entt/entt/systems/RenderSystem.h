#ifndef ECS_BENCHMARKS_ENTT_RENDER_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_RENDER_MORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/FrameBuffer.h"
#include "base/systems/DamageSystem.h"
#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"
#include "base/systems/RenderSystem.h"
#include "base/systems/SpriteSystem.h"

namespace ecs::benchmarks::entt::systems {

class RenderSystem final : public ecs::benchmarks::base::systems::RenderSystem<::entt::registry, float> {
public:
  RenderSystem() = delete;
  explicit RenderSystem(base::FrameBuffer& frameBuffer)
      : ecs::benchmarks::base::systems::RenderSystem<::entt::registry, float>(frameBuffer) {}

  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif