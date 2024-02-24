#ifndef ECS_BENCHMARKS_ENTT_DAMAGE_GROUPMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_DAMAGE_GROUPMORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/DamageSystem.h"

namespace ecs::benchmarks::entt::systems {

class GroupDamageSystem final : public ecs::benchmarks::base::systems::DamageSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif