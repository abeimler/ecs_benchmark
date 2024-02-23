#ifndef ECS_BENCHMARKS_OPENECS_APPLICATION_H_
#define ECS_BENCHMARKS_OPENECS_APPLICATION_H_

#include <ecs.h>

#include "base/Application.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::openecs {
class OpenECSApplication {
public:
  using EntityManager = ::ecs::EntityManager;
  using TimeDelta = float;

  OpenECSApplication() : m_systems(m_entities) {}
  explicit OpenECSApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system), m_systems(m_entities) {}
  ~OpenECSApplication() = default;
  OpenECSApplication(const OpenECSApplication&) = delete;
  OpenECSApplication& operator=(const OpenECSApplication&) = delete;
  OpenECSApplication(OpenECSApplication&&) = default;
  OpenECSApplication& operator=(OpenECSApplication&&) = default;

  [[nodiscard]] inline EntityManager& getEntities() { return m_entities; }
  [[nodiscard]] inline const EntityManager& getEntities() const { return m_entities; }


  void init() {
    m_systems.add<systems::MovementSystem>();
    m_systems.add<systems::DataSystem>();
    if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
      m_systems.add<systems::MoreComplexSystem>();
    }
  }

  void uninit() {
    if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
      m_systems.remove<systems::MoreComplexSystem>();
    }
    m_systems.remove<systems::DataSystem>();
    m_systems.remove<systems::MovementSystem>();
  }

  void update(TimeDelta dt) { m_systems.update(dt); }

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseBasicSystems};
  EntityManager m_entities;
  SystemManager m_systems;
};
} // namespace ecs::benchmarks::openecs

#endif // ECS_BENCHMARKS_OPENECS_APPLICATION_H_
