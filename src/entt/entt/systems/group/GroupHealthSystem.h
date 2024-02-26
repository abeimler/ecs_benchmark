#ifndef ECS_BENCHMARKS_ENTT_HEALTH_GROUPMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_HEALTH_GROUPMORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/HealthSystem.h"

namespace ecs::benchmarks::entt::systems {

class GroupHealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif