#ifndef ECS_BENCHMARKS_BASE_HEALTHSYSTEM_HEROMONSTERSYSTEMS_H_
#define ECS_BENCHMARKS_BASE_HEALTHSYSTEM_HEROMONSTERSYSTEMS_H_

#include "System.h"
#include "base/components/HeroMonsterComponents.h"

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta>
class HealthSystem : public System<EntityManager, TimeDelta> {
public:
  HealthSystem() = default;
  virtual ~HealthSystem() = default;
  HealthSystem(const HealthSystem&) = delete;
  HealthSystem& operator=(const HealthSystem&) = delete;
  HealthSystem(HealthSystem&&) noexcept = default;
  HealthSystem& operator=(HealthSystem&&) noexcept = default;

  static void updateHealth(ecs::benchmarks::base::components::HealthComponent& health) {
    using namespace ecs::benchmarks::base::components;
    if (health.hp <= 0 && health.status != StatusEffect::Dead) {
      health.hp = 0;
      health.status = StatusEffect::Dead;
    } else if (health.status == StatusEffect::Dead && health.hp == 0) {
      health.hp = health.maxhp;
      health.status = StatusEffect::Spawn;
    } else if (health.hp >= health.maxhp && health.status != StatusEffect::Alive) {
      health.hp = health.maxhp;
      health.status = StatusEffect::Alive;
    } else {
      health.status = StatusEffect::Alive;
    }
  }
};

} // namespace ecs::benchmarks::base::systems

#endif