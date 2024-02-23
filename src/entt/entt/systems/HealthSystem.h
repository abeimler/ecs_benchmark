#ifndef ECS_BENCHMARKS_ENTT_HEALTH_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_HEALTH_MORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/DamageSystem.h"
#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::entt::systems {

class HealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif