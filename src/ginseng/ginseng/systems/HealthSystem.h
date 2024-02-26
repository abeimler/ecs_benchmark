#ifndef ECS_BENCHMARKS_GINSENG_HEALTH_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_HEALTH_MORECOMPLEXSYSTEM_H_

#include "base/systems/HealthSystem.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::systems {

class HealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::ginseng::systems

#endif