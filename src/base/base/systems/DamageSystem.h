#ifndef ECS_BENCHMARKS_BASE_DAMAGE_HEROMONSTERSYSTEMS_H_
#define ECS_BENCHMARKS_BASE_DAMAGE_HEROMONSTERSYSTEMS_H_

#include "System.h"
#include "base/components/HeroMonsterComponents.h"
#include <algorithm>

namespace ecs::benchmarks::base::systems {

template <class EntityManager, typename TimeDelta>
class DamageSystem : public System<EntityManager, TimeDelta> {
public:
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

    if (health.hp > 0 && totalDamage > 0) {
      health.hp = std::max(health.hp - totalDamage, 0);
    }
  }
};

} // namespace ecs::benchmarks::base::systems

#endif