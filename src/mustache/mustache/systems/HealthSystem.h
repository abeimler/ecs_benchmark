#ifndef ECS_BENCHMARKS_MUSTACHE_HEALTH_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_HEALTH_MORECOMPLEXSYSTEM_H_

/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>

#include "base/systems/HealthSystem.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::systems {

class HealthSystem final : public ::mustache::System<HealthSystem>,
                           ecs::benchmarks::base::systems::HealthSystem<::mustache::World, float> {
public:
  using Entity = ::mustache::Entity;

  void update(::mustache::World& world, TimeDelta dt) override;

  void onUpdate(::mustache::World& world) override;
};

} // namespace ecs::benchmarks::mustache::systems

#endif