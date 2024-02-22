#ifndef ECS_BENCHMARKS_GAIA_ECS_APPLICATION_H_
#define ECS_BENCHMARKS_GAIA_ECS_APPLICATION_H_

#include "base/Application.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs {

class GaiaEcsApplication {
public:
  using EntityManager = ::gaia::ecs::World;
  using TimeDelta = float;

  GaiaEcsApplication() : m_sm(m_world) {}

  explicit GaiaEcsApplication(bool add_more_complex_system)
      : m_add_more_complex_system(add_more_complex_system), m_sm(m_world) {}

  ~GaiaEcsApplication() = default;

  GaiaEcsApplication(const GaiaEcsApplication&) = delete;

  GaiaEcsApplication& operator=(const GaiaEcsApplication&) = delete;

  GaiaEcsApplication(GaiaEcsApplication&&) = default;

  GaiaEcsApplication& operator=(GaiaEcsApplication&&) = default;

  [[nodiscard]] inline EntityManager& getEntities() { return m_world; }

  [[nodiscard]] inline const EntityManager& getEntities() const { return m_world; }


  void init() {
    m_sm.add<systems::MovementSystem>();
    m_sm.add<systems::DataSystem>();
    if (m_add_more_complex_system) {
      m_sm.add<systems::MoreComplexSystem>();
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

#endif // ECS_BENCHMARKS_GAIA_ECS_APPLICATION_H_
