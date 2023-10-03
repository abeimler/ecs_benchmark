#ifndef ECS_BENCHMARKS_ENTT_STABLERUNTIMEAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_STABLERUNTIMEAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"
#include "systems/RuntimeDataSystem.h"
#include "systems/RuntimeMoreComplexSystem.h"
#include "systems/StableRuntimeMovementSystem.h"

namespace ecs::benchmarks::entt {
class StableEnttRuntimeApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::StableRuntimeMovementSystem,
                                                systems::RuntimeDataSystem, systems::RuntimeMoreComplexSystem,
                                                systems::RuntimeHealthSystem, systems::RuntimeDamageSystem> {
public:
  StableEnttRuntimeApplication() = default;
  explicit StableEnttRuntimeApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}
  ~StableEnttRuntimeApplication() = default;
  StableEnttRuntimeApplication(const StableEnttRuntimeApplication&) = delete;
  StableEnttRuntimeApplication& operator=(const StableEnttRuntimeApplication&) = delete;
  StableEnttRuntimeApplication(StableEnttRuntimeApplication&&) = default;
  StableEnttRuntimeApplication& operator=(StableEnttRuntimeApplication&&) = default;
};
} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_STABLERUNTIMEAPPLICATION_H_
