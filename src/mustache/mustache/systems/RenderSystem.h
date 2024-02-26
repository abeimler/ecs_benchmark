#ifndef ECS_BENCHMARKS_MUSTACHE_SPRITE_RENDERSYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_SPRITE_RENDERSYSTEM_H_

/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>

#include "base/FrameBuffer.h"
#include "base/systems/RenderSystem.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::systems {

class RenderSystem final : public ::mustache::System<RenderSystem>,
                           ecs::benchmarks::base::systems::RenderSystem<::mustache::World, float> {
public:
  using Entity = ::mustache::Entity;

  RenderSystem() = delete;
  explicit RenderSystem(base::FrameBuffer& frameBuffer)
      : ecs::benchmarks::base::systems::RenderSystem<::mustache::World, float>(frameBuffer) {}

  void update(::mustache::World& world, TimeDelta dt) override;
  void onUpdate(::mustache::World& world) override;
};

} // namespace ecs::benchmarks::mustache::systems

#endif