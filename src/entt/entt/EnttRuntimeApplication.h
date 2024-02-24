#ifndef ECS_BENCHMARKS_ENTT_RUNTIMEAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_RUNTIMEAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"
#include "entt/systems/RenderSystem.h"
#include "entt/systems/SpriteSystem.h"
#include "entt/systems/runtime/RuntimeDamageSystem.h"
#include "entt/systems/runtime/RuntimeDataSystem.h"
#include "entt/systems/runtime/RuntimeHealthSystem.h"
#include "entt/systems/runtime/RuntimeMoreComplexSystem.h"
#include "entt/systems/runtime/RuntimeMovementSystem.h"

namespace ecs::benchmarks::entt {
class EnttRuntimeApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::RuntimeMovementSystem,
                                                systems::RuntimeDataSystem, systems::RuntimeMoreComplexSystem,
                                                systems::RuntimeHealthSystem, systems::RuntimeDamageSystem,
                                                systems::SpriteSystem, systems::RenderSystem> {
public:
  EnttRuntimeApplication() = default;
  explicit EnttRuntimeApplication(base::add_more_complex_system_t add_more_complex_system)
      : Application(add_more_complex_system) {}
  ~EnttRuntimeApplication() = default;
  EnttRuntimeApplication(const EnttRuntimeApplication&) = delete;
  EnttRuntimeApplication& operator=(const EnttRuntimeApplication&) = delete;
  EnttRuntimeApplication(EnttRuntimeApplication&&) = default;
  EnttRuntimeApplication& operator=(EnttRuntimeApplication&&) = default;
};

} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_RUNTIMEAPPLICATION_H_
