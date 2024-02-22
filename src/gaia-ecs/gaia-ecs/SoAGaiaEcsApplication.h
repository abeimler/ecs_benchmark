#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAAPPLICATION_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAAPPLICATION_H_

#include "base/Application.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/SoAMoreComplexSystem.h"
#include "systems/SoAMovementSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs {

class SoAGaiaEcsApplication {
public:
  using EntityManager = ::gaia::ecs::World;
  using TimeDelta = float;

  SoAGaiaEcsApplication() : m_sm(m_world) {}

  explicit SoAGaiaEcsApplication(bool add_more_complex_system)
      : m_add_more_complex_system(add_more_complex_system), m_sm(m_world) {}

  ~SoAGaiaEcsApplication() = default;

  SoAGaiaEcsApplication(const SoAGaiaEcsApplication&) = delete;

  SoAGaiaEcsApplication& operator=(const SoAGaiaEcsApplication&) = delete;

  SoAGaiaEcsApplication(SoAGaiaEcsApplication&&) = default;

  SoAGaiaEcsApplication& operator=(SoAGaiaEcsApplication&&) = default;

  [[nodiscard]] inline EntityManager& getEntities() { return m_world; }

  [[nodiscard]] inline const EntityManager& getEntities() const { return m_world; }


  void init() {
    m_sm.add<systems::SoAMovementSystem>();
    m_sm.add<systems::DataSystem>();
    if (m_add_more_complex_system) {
      m_sm.add<systems::SoAMoreComplexSystem>();
      m_sm.add<systems::HealthSystem>();
      m_sm.add<systems::DamageSystem>();
    }
  }

  void uninit() {
    /// @TODO: remove system for better clean up
  }

  void update(TimeDelta dt) { m_sm.update(); }

private:
  bool m_add_more_complex_system{false};
  EntityManager m_world;
  ::gaia::ecs::SystemManager m_sm;
};
} // namespace ecs::benchmarks::gaia_ecs

#endif // ECS_BENCHMARKS_GAIA_ECS_SOAAPPLICATION_H_
