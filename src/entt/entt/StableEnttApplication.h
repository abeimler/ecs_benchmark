#ifndef ECS_BENCHMARKS_ENTT_STABLEAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_STABLEAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"
#include "entt/systems/DamageSystem.h"
#include "entt/systems/DataSystem.h"
#include "entt/systems/HealthSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/RenderSystem.h"
#include "entt/systems/SpriteSystem.h"
#include "entt/systems/stable/StableMovementSystem.h"

namespace ecs::benchmarks::entt {

class StableEnttApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::StableMovementSystem,
                                                systems::DataSystem, systems::MoreComplexSystem, systems::HealthSystem,
                                                systems::DamageSystem, systems::SpriteSystem, systems::RenderSystem> {
public:
  StableEnttApplication() = default;
  explicit StableEnttApplication(base::add_more_complex_system_t add_more_complex_system)
      : Application(add_more_complex_system) {}
  ~StableEnttApplication() override = default;
  StableEnttApplication(const StableEnttApplication&) = delete;
  StableEnttApplication& operator=(const StableEnttApplication&) = delete;
  StableEnttApplication(StableEnttApplication&&) = default;
  StableEnttApplication& operator=(StableEnttApplication&&) = default;
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_STABLEAPPLICATION_H_
