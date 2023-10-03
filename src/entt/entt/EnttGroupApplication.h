#ifndef ECS_BENCHMARKS_ENTT_GROUPAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_GROUPAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"

#include "systems/DataSystem.h"
#include "systems/GroupMoreComplexSystem.h"
#include "systems/GroupMovementSystem.h"
#include "systems/MoreComplexSystem.h"

namespace ecs::benchmarks::entt {
class EnttGroupApplication final
    : public ecs::benchmarks::base::Application<::entt::registry, float, systems::GroupMovementSystem,
                                                systems::DataSystem, systems::MoreComplexSystem,
                                                systems::GroupHealthSystem, systems::GroupDamageSystem> {
public:
  EnttGroupApplication() = default;

  explicit EnttGroupApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}

  ~EnttGroupApplication() = default;

  EnttGroupApplication(const EnttGroupApplication&) = delete;

  EnttGroupApplication& operator=(const EnttGroupApplication&) = delete;

  EnttGroupApplication(EnttGroupApplication&&) = default;

  EnttGroupApplication& operator=(EnttGroupApplication&&) = default;
};
} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_GROUPAPPLICATION_H_
