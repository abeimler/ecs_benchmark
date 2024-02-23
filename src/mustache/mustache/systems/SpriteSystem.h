#ifndef ECS_BENCHMARKS_MUSTACHE_SPRITE_SPRITESYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_SPRITE_SPRITESYSTEM_H_

/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>

#include "base/systems/SpriteSystem.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::systems {

class SpriteSystem final : public ::mustache::System<SpriteSystem>,
                           ecs::benchmarks::base::systems::SpriteSystem<::mustache::World, float> {
public:
  using Entity = ::mustache::Entity;

  void update(::mustache::World& world, TimeDelta dt) override;

  void onUpdate(::mustache::World& world) override;
};

} // namespace ecs::benchmarks::mustache::systems

#endif