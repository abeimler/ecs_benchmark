#ifndef ECS_BENCHMARKS_MUSTACHE_DATASYSTEM_H_
#define ECS_BENCHMARKS_MUSTACHE_DATASYSTEM_H_

#include "base/systems/DataSystem.h"
/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::systems {

class DataSystem final : public ::mustache::System<DataSystem>,
                         ecs::benchmarks::base::systems::DataSystem<::mustache::World, float> {
public:
  using Entity = ::mustache::Entity;

  void update(::mustache::World& world, TimeDelta dt) override;

  void onUpdate(::mustache::World& world) override;
};

} // namespace ecs::benchmarks::mustache::systems

#endif