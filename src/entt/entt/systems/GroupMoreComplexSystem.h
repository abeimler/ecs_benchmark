#ifndef ECS_BENCHMARKS_ENTT_GROUPMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_GROUPMORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::entt::systems {

class GroupMoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

class GroupHealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

class GroupDamageSystem final : public ecs::benchmarks::base::systems::DamageSystem<::entt::registry, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::entt::systems

#endif