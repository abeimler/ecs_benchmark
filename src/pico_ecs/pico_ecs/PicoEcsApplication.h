#ifndef ECS_BENCHMARKS_PICO_ECS_APPLICATION_H_
#define ECS_BENCHMARKS_PICO_ECS_APPLICATION_H_

#include <pico_ecs.h>

#include "base/Application.h"

#include "pico_ecs/entities/EntityFactory.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::pico_ecs {
class PicoEcsApplication {
public:
  using EntityManager = ecs::benchmarks::pico_ecs::entities::details::EntityManager;
  using TimeDelta = ecs_dt_t;

  PicoEcsApplication() = default;

  explicit PicoEcsApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}

  ~PicoEcsApplication() = default;

  PicoEcsApplication(const PicoEcsApplication&) = delete;

  PicoEcsApplication& operator=(const PicoEcsApplication&) = delete;

  PicoEcsApplication(PicoEcsApplication&&) = delete;

  PicoEcsApplication& operator=(PicoEcsApplication&&) = delete;

  inline EntityManager& getEntities() { return m_registry; }


  void init() {
    m_movement_system.init(m_registry);
    m_data_system.init(m_registry);
    m_more_complex_system.init(m_registry);
    ecs_enable_system(m_registry.ecs.get(), m_movement_system.id());
    ecs_enable_system(m_registry.ecs.get(), m_data_system.id());
    if (m_add_more_complex_system) {
      ecs_enable_system(m_registry.ecs.get(), m_more_complex_system.id());
    } else {
      ecs_disable_system(m_registry.ecs.get(), m_more_complex_system.id());
    }
  }

  void uninit() {
    /// @TODO: remove systems
  }

  void update(TimeDelta dt) { ecs_update_systems(m_registry.ecs.get(), dt); }

private:
  bool m_add_more_complex_system{false};
  EntityManager m_registry;
  systems::MovementSystem m_movement_system;
  systems::DataSystem m_data_system;
  systems::MoreComplexSystem m_more_complex_system;
};
} // namespace ecs::benchmarks::pico_ecs

#endif // ECS_BENCHMARKS_PICO_ECS_APPLICATION_H_
