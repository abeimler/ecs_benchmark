#ifndef ECS_BENCHMARKS_GINSENG_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GINSENG_MORECOMPLEXSYSTEM_H_

#include "base/systems/MoreComplexSystem.h"
#include "base/systems/HeroMonsterSystems.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::systems {

class MoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

class HealthSystem final : public ecs::benchmarks::base::systems::HealthSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

class DamageSystem final : public ecs::benchmarks::base::systems::DamageSystem<::ginseng::database, float> {
public:
  void update(EntityManager& registry, TimeDelta dt) override;
};

} // namespace ecs::benchmarks::ginseng::systems

#endif