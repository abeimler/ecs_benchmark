#ifndef ECS_BENCHMARKS_GINSENG_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_RENDERSYSTEM_H_

#include "base/systems/RenderSystem.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::systems {

class RenderSystem final : public ecs::benchmarks::base::systems::RenderSystem<::ginseng::database, float> {
public:
  RenderSystem() = delete;
  explicit RenderSystem(base::FrameBuffer& frameBuffer)
      : ecs::benchmarks::base::systems::RenderSystem<::ginseng::database, float>(frameBuffer) {}

  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::ginseng::systems

#endif