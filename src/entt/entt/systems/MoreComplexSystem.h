#ifndef ECS_BENCHMARKS_ENTT_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_MORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/DamageSystem.h"
#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::entt::systems {

class MoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif