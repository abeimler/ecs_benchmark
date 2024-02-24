#ifndef ECS_BENCHMARKS_ENTT_GROUPAPPLICATION_H_
#define ECS_BENCHMARKS_ENTT_GROUPAPPLICATION_H_

#include "entt.h"

#include "base/Application.h"
#include "entt/systems/DataSystem.h"
#include "entt/systems/MoreComplexSystem.h"
#include "entt/systems/RenderSystem.h"
#include "entt/systems/SpriteSystem.h"
#include "entt/systems/group/GroupDamageSystem.h"
#include "entt/systems/group/GroupHealthSystem.h"
#include "entt/systems/group/GroupMoreComplexSystem.h"
#include "entt/systems/group/GroupMovementSystem.h"
#include "entt/systems/group/GroupSpriteSystem.h"

namespace ecs::benchmarks::entt {
class EnttGroupApplication final
    : public ecs::benchmarks::base::Application<
          ::entt::registry, float, systems::GroupMovementSystem, systems::DataSystem, systems::GroupMoreComplexSystem,
          systems::GroupHealthSystem, systems::GroupDamageSystem, systems::GroupSpriteSystem, systems::RenderSystem> {
public:
  EnttGroupApplication() = default;
  explicit EnttGroupApplication(base::add_more_complex_system_t add_more_complex_system)
      : Application(add_more_complex_system) {}
  ~EnttGroupApplication() = default;
  EnttGroupApplication(const EnttGroupApplication&) = delete;
  EnttGroupApplication& operator=(const EnttGroupApplication&) = delete;
  EnttGroupApplication(EnttGroupApplication&&) = default;
  EnttGroupApplication& operator=(EnttGroupApplication&&) = default;
};
} // namespace ecs::benchmarks::entt

#endif // ECS_BENCHMARKS_ENTT_GROUPAPPLICATION_H_
