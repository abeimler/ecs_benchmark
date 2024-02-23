#ifndef ECS_BENCHMARKS_GINSENG_APPLICATION_H_
#define ECS_BENCHMARKS_GINSENG_APPLICATION_H_

#include "base/Application.h"
#include "ginseng/systems/DamageSystem.h"
#include "ginseng/systems/DataSystem.h"
#include "ginseng/systems/HealthSystem.h"
#include "ginseng/systems/MoreComplexSystem.h"
#include "ginseng/systems/MovementSystem.h"
#include "ginseng/systems/RenderSystem.h"
#include "ginseng/systems/SpriteSystem.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng {
class GinsengApplication final
    : public ecs::benchmarks::base::Application<::ginseng::database, float, systems::MovementSystem,
                                                systems::DataSystem, systems::MoreComplexSystem, systems::HealthSystem,
                                                systems::DamageSystem, systems::SpriteSystem, systems::RenderSystem> {
public:
  GinsengApplication() = default;
  explicit GinsengApplication(base::add_more_complex_system_t add_more_complex_system)
      : Application(add_more_complex_system) {}
  ~GinsengApplication() = default;
  GinsengApplication(const GinsengApplication&) = delete;
  GinsengApplication& operator=(const GinsengApplication&) = delete;
  GinsengApplication(GinsengApplication&&) = default;
  GinsengApplication& operator=(GinsengApplication&&) = default;
};
} // namespace ecs::benchmarks::ginseng

#endif // ECS_BENCHMARKS_GINSENG_APPLICATION_H_
