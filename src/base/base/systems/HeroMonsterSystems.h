#ifndef ECS_BENCHMARKS_BASE_HEROMONSTERSYSTEMS_H_
#define ECS_BENCHMARKS_BASE_HEROMONSTERSYSTEMS_H_

#include "System.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta>
class HealthSystem : public System<EntityManager, TimeDelta> {
public:
  // virtual dtor and the rule of 6
  HealthSystem() = default;
  virtual ~HealthSystem() = default;
  HealthSystem(const HealthSystem&) = delete;
  HealthSystem& operator=(const HealthSystem&) = delete;
  HealthSystem(HealthSystem&&) noexcept = default;
  HealthSystem& operator=(HealthSystem&&) noexcept = default;

  static void updateHealth(ecs::benchmarks::base::components::HealthComponent& health) {
    using namespace ecs::benchmarks::base::components;
    if (health.hp <= 0) {
      health.hp = 0;
      health.status = StatusEffect::Dead;
    } else if (health.hp > health.maxhp) {
      health.hp = health.maxhp;
    } else if (health.status == StatusEffect::Dead && health.hp == 0) {
      health.hp = health.maxhp;
      health.status = StatusEffect::Spawn;
    } else {
      health.status = StatusEffect::Alive;
    }
  }
};

template <class EntityManager, typename TimeDelta>
class DamageSystem : public System<EntityManager, TimeDelta> {
public:
  // virtual dtor and the rule of 6
  DamageSystem() = default;
  virtual ~DamageSystem() = default;
  DamageSystem(const DamageSystem&) = delete;
  DamageSystem& operator=(const DamageSystem&) = delete;
  DamageSystem(DamageSystem&&) noexcept = default;
  DamageSystem& operator=(DamageSystem&&) noexcept = default;

  static void updateDamage(ecs::benchmarks::base::components::HealthComponent& health,
                           const ecs::benchmarks::base::components::DamageComponent& damage) {
    using namespace ecs::benchmarks::base::components;
    // Calculate damage
    const int totalDamage = damage.atk - damage.def;

    if (totalDamage > 0) {
      health.hp -= totalDamage;
    }
  }
};

} // namespace ecs::benchmarks::base::systems

#endif