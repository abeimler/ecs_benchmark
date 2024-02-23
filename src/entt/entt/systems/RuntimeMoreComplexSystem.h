#ifndef ECS_BENCHMARKS_ENTT_RUNTIMEMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_ENTT_RUNTIMEMORECOMPLEXSYSTEM_H_

#include "entt/entt.h"

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::entt::systems {

class RuntimeMoreComplexSystem final
    : public ecs::benchmarks::base::systems::MoreComplexSystem<::entt::registry, float> {
public:
  void init(EntityManager& entities) override;

  void update(EntityManager& registry, TimeDelta dt) override;

private:
  ::entt::runtime_view m_view{};
};

class RuntimeHealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::entt::registry, float> {
public:
  void init(EntityManager& entities) override;

  void update(EntityManager& registry, TimeDelta dt) override;

private:
  ::entt::runtime_view m_view{};
};

class RuntimeDamageSystem final : public ecs::benchmarks::base::systems::DamageSystem<::entt::registry, float> {
public:
  void init(EntityManager& entities) override;

  void update(EntityManager& registry, TimeDelta dt) override;

private:
  ::entt::runtime_view m_view{};
};

} // namespace ecs::benchmarks::entt::systems

#endif