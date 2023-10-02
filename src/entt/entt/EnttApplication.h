#ifndef ECS_BENCHMARKS_ENTT_APPLICATION_H_
#define ECS_BENCHMARKS_ENTT_APPLICATION_H_

#include "base/Application.h"
#include "entt.h"
#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::entt {
class EnttApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::MovementSystem, systems::DataSystem,
                                                systems::MoreComplexSystem,
                                                systems::HealthSystem, systems::DamageSystem> {
public:
  EnttApplication() = default;

  explicit EnttApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}

  ~EnttApplication() = default;

  EnttApplication(const EnttApplication&) = delete;

  EnttApplication& operator=(const EnttApplication&) = delete;

  EnttApplication(EnttApplication&&) = default;

  EnttApplication& operator=(EnttApplication&&) = default;
};
} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_APPLICATION_H_
