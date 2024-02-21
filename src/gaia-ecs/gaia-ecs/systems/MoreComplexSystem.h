#ifndef ECS_BENCHMARKS_GAIA_ECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_MORECOMPLEXSYSTEM_H_

#include "base/systems/HeroMonsterSystems.h"
#include "base/systems/MoreComplexSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class MoreComplexSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;

  static int random(int min, int max) {
    std::uniform_int_distribution<int> distr(min, max);
    return distr(m_eng);
  }

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::PositionComponent,
                   ecs::benchmarks::base::components::VelocityComponent&,
                   ecs::benchmarks::base::components::PositionComponent>();
  }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](const ecs::benchmarks::base::components::PositionComponent& position,
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
    });
  }

private:
  ::gaia::ecs::Query m_q;
  static std::random_device m_rd;
  static std::mt19937 m_eng;
};


class HealthSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;

  void OnCreated() override { m_q = world().query().all<ecs::benchmarks::base::components::HealthComponent&>(); }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](ecs::benchmarks::base::components::HealthComponent& health) {
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
    });
  }

private:
  ::gaia::ecs::Query m_q;
};


class DamageSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = double;
  using Entity = ::gaia::ecs::Entity;

  void OnCreated() override {
    m_q = world()
              .query()
              .all<ecs::benchmarks::base::components::HealthComponent,
                   ecs::benchmarks::base::components::DamageComponent&>();
  }
  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](ecs::benchmarks::base::components::HealthComponent& health,
                 const ecs::benchmarks::base::components::DamageComponent& damage) {
      using namespace ecs::benchmarks::base::components;
      // Calculate damage
      const int totalDamage = damage.atk - damage.def;

      if (totalDamage > 0) {
        health.hp -= totalDamage;
      }
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
