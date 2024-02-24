#ifndef ECS_BENCHMARKS_ENTT_STABLERUNTIMEAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_STABLERUNTIMEAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"
#include "entt/systems/RenderSystem.h"
#include "entt/systems/SpriteSystem.h"
#include "entt/systems/runtime/RuntimeDamageSystem.h"
#include "entt/systems/runtime/RuntimeDataSystem.h"
#include "entt/systems/runtime/RuntimeHealthSystem.h"
#include "entt/systems/runtime/RuntimeMoreComplexSystem.h"
#include "entt/systems/stable/StableRuntimeMovementSystem.h"

namespace ecs::benchmarks::entt {

class StableEnttRuntimeApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::StableRuntimeMovementSystem,
                                                systems::RuntimeDataSystem, systems::RuntimeMoreComplexSystem,
                                                systems::RuntimeHealthSystem, systems::RuntimeDamageSystem,
                                                systems::SpriteSystem, systems::RenderSystem> {
public:
  StableEnttRuntimeApplication() = default;
  explicit StableEnttRuntimeApplication(base::add_more_complex_system_t add_more_complex_system)
      : Application(add_more_complex_system) {}
  ~StableEnttRuntimeApplication() = default;
  StableEnttRuntimeApplication(const StableEnttRuntimeApplication&) = delete;
  StableEnttRuntimeApplication& operator=(const StableEnttRuntimeApplication&) = delete;
  StableEnttRuntimeApplication(StableEnttRuntimeApplication&&) = default;
  StableEnttRuntimeApplication& operator=(StableEnttRuntimeApplication&&) = default;
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_STABLERUNTIMEAPPLICATION_H_
