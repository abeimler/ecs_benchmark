#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAMORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAMORECOMPLEXSYSTEM_H_

#include "base/systems/HeroMonsterSystems.h"
#include "base/systems/MoreComplexSystem.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include "gaia-ecs/components/SoAVelocityComponent.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs::systems {

class SoAMoreComplexSystem final : public ::gaia::ecs::System {
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
              .all<components::SoAPositionComponent, components::SoAVelocityComponent&,
                   ecs::benchmarks::base::components::DataComponent>();
  }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0 / 60.0;
    m_q.each([&](::gaia::ecs::Iter iter) {
      // Position
      auto vp = iter.view<components::SoAPositionComponent>(); // read-only access to PositionSoA
      auto px = vp.get<0>();                                   // continuous block of "x" from PositionSoA
      auto py = vp.get<1>();                                   // continuous block of "y" from PositionSoA

      // Velocity
      auto vv = iter.view_mut<components::SoAVelocityComponent>(); // read-write access to VelocitySoA
      auto vx = vv.set<0>();                                       // continuous block of "x" from VelocitySoA
      auto vy = vv.set<1>();                                       // continuous block of "y" from VelocitySoA

      // Data
      auto vd = iter.view<ecs::benchmarks::base::components::DataComponent>();

      GAIA_EACH(iter) {
        if ((vd[i].thingy % 10) == 0) {
          if (px[i] > py[i]) {
            vx[i] = static_cast<float>(random(-5, 5));
            vy[i] = static_cast<float>(random(-10, 10));
          } else {
            vx[i] = static_cast<float>(random(-10, 10));
            vy[i] = static_cast<float>(random(-5, 5));
          }
        }
      }
    });
  }

private:
  ::gaia::ecs::Query m_q;
  static std::random_device m_rd;
  static std::mt19937 m_eng;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
