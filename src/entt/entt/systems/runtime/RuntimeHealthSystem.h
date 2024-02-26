#ifndef ECS_BENCHMARKS_ENTT_HEALTH_RUNTIMEMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_HEALTH_RUNTIMEMORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/HealthSystem.h"

namespace ecs::benchmarks::entt::systems {

class RuntimeHealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::entt::registry, float> {
public:
  void init(EntityManager& entities) override;

  void update(EntityManager& registry, TimeDelta dt) override;

private:
  ::entt::runtime_view m_view{};
};

} // namespace ecs::benchmarks::entt::systems

#endif