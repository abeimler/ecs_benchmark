#ifndef ECS_BENCHMARKS_MUSTACHE_DAMAGE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_DAMAGE_MORECOMPLEXSYSTEM_H_

/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>

#include "base/systems/DamageSystem.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::systems {

class DamageSystem final : public ::mustache::System<DamageSystem>,
                           ecs::benchmarks::base::systems::DamageSystem<::mustache::World, float> {
public:
  using Entity = ::mustache::Entity;

  void update(::mustache::World& world, TimeDelta dt) override;

  void onUpdate(::mustache::World& world) override;
};

} // namespace ecs::benchmarks::mustache::systems

#endif