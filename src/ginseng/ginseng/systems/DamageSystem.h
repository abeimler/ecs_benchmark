#ifndef ECS_BENCHMARKS_GINSENG_DAMAGE_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_DAMAGE_MORECOMPLEXSYSTEM_H_

#include "base/systems/DamageSystem.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::systems {

class DamageSystem final : public ecs::benchmarks::base::systems::DamageSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::ginseng::systems

#endif