#ifndef ECS_BENCHMARKS_ENTT_APPLICATION_H_
#define ECS_BENCHMARKS_ENTT_APPLICATION_H_

#include "entt.h"

#include "base/Application.h"
#include "entt/systems/DamageSystem.h"
#include "entt/systems/DataSystem.h"
#include "entt/systems/HealthSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/MovementSystem.h"
#include "entt/systems/RenderSystem.h"
#include "entt/systems/SpriteSystem.h"

namespace ecs::benchmarks::entt {
class EnttApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::MovementSystem, systems::DataSystem,
                                                systems::MoreComplexSystem, systems::HealthSystem,
                                                systems::DamageSystem, systems::SpriteSystem, systems::RenderSystem> {
public:
  EnttApplication() = default;
  explicit EnttApplication(base::add_more_complex_system_t add_more_complex_system)
      : Application(add_more_complex_system) {}
  ~EnttApplication() override = default;
  EnttApplication(const EnttApplication&) = delete;
  EnttApplication& operator=(const EnttApplication&) = delete;
  EnttApplication(EnttApplication&&) = default;
  EnttApplication& operator=(EnttApplication&&) = default;
};
} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_APPLICATION_H_
