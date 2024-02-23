#ifndef ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_FLECS_MORECOMPLEXSYSTEM_H_

#include "flecs/custom_flecs.h"

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"

namespace ecs::benchmarks::flecs::systems {

class MoreComplexSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;

  static int random(int min, int max) {
    std::uniform_int_distribution<int> distr(min, max);
    return distr(m_eng);
  }

  inline static const auto update = [](::flecs::iter& /*it*/, size_t /*index*/,
                                       const ecs::benchmarks::base::components::PositionComponent& position,
                                       ecs::benchmarks::base::components::VelocityComponent& direction,
                                       const ecs::benchmarks::base::components::DataComponent& data) {
    if ((data.thingy % 10) == 0) {
      if (position.x > position.y) {
        direction.x = static_cast<float>(random(-5, 5));
        direction.y = static_cast<float>(random(-10, 10));
      } else {
        direction.x = static_cast<float>(random(-10, 10));
        direction.y = static_cast<float>(random(-5, 5));
      }
    }
  };

private:
  static std::random_device m_rd;
  static std::mt19937 m_eng;
};


class HealthSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;

  inline static const auto update = [](ecs::benchmarks::base::components::HealthComponent& health) {
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
  };
};


class DamageSystem {
public:
  using TimeDelta = float;
  using Entity = ::flecs::entity;

  inline static const auto update = [](ecs::benchmarks::base::components::HealthComponent& health,
                                       const ecs::benchmarks::base::components::DamageComponent& damage) {
    using namespace ecs::benchmarks::base::components;
    // Calculate damage
    const int totalDamage = damage.atk - damage.def;

    if (totalDamage > 0) {
      health.hp -= totalDamage;
    }
  };
};

} // namespace ecs::benchmarks::flecs::systems

#endif
