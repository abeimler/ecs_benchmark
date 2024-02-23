#ifndef ECS_BENCHMARKS_PICO_ECS_APPLICATION_H_
#define ECS_BENCHMARKS_PICO_ECS_APPLICATION_H_

#include <pico_ecs.h>

#include "base/Application.h"
#include "pico_ecs/entities/EntityFactory.h"
#include "pico_ecs/systems/DamageSystem.h"
#include "pico_ecs/systems/DataSystem.h"
#include "pico_ecs/systems/HealthSystem.h"
#include "pico_ecs/systems/MoreComplexSystem.h"
#include "pico_ecs/systems/MovementSystem.h"
#include "pico_ecs/systems/RenderSystem.h"
#include "pico_ecs/systems/SpriteSystem.h"

namespace ecs::benchmarks::pico_ecs {

class PicoEcsApplication {
public:
  using EntityManager = ecs::benchmarks::pico_ecs::entities::details::EntityManager;
  using TimeDelta = ecs_dt_t;
  using BaseApplication =
      ecs::benchmarks::base::Application<EntityManager, TimeDelta, systems::MovementSystem, systems::DataSystem,
                                         systems::MoreComplexSystem, systems::HealthSystem, systems::DamageSystem,
                                         systems::SpriteSystem, systems::RenderSystem>;

  PicoEcsApplication()
      : m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight),
        m_renderSystem(m_frameBuffer) {}
  explicit PicoEcsApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system),
        m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight),
        m_renderSystem(m_frameBuffer) {}
  ~PicoEcsApplication() = default;
  PicoEcsApplication(const PicoEcsApplication&) = delete;
  PicoEcsApplication& operator=(const PicoEcsApplication&) = delete;
  PicoEcsApplication(PicoEcsApplication&&) = delete;
  PicoEcsApplication& operator=(PicoEcsApplication&&) = delete;

  inline EntityManager& getEntities() { return m_registry; }

  void init() {
    m_movementSystem.init(m_registry);
    m_dataSystem.init(m_registry);
    m_moreComplexSystem.init(m_registry);
    m_healthSystem.init(m_registry);
    m_damageSystem.init(m_registry);
    m_spriteSystem.init(m_registry);
    m_renderSystem.init(m_registry);

    ecs_enable_system(m_registry.ecs.get(), m_movementSystem.id());
    ecs_enable_system(m_registry.ecs.get(), m_dataSystem.id());
    if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
      ecs_enable_system(m_registry.ecs.get(), m_moreComplexSystem.id());
      ecs_enable_system(m_registry.ecs.get(), m_healthSystem.id());
      ecs_enable_system(m_registry.ecs.get(), m_damageSystem.id());
      ecs_enable_system(m_registry.ecs.get(), m_spriteSystem.id());
      ecs_enable_system(m_registry.ecs.get(), m_renderSystem.id());
    } else {
      ecs_disable_system(m_registry.ecs.get(), m_moreComplexSystem.id());
      ecs_disable_system(m_registry.ecs.get(), m_healthSystem.id());
      ecs_disable_system(m_registry.ecs.get(), m_damageSystem.id());
      ecs_disable_system(m_registry.ecs.get(), m_spriteSystem.id());
      ecs_disable_system(m_registry.ecs.get(), m_renderSystem.id());
    }
  }

  void uninit() {
    /// @TODO: remove systems
  }

  void update(TimeDelta dt) { ecs_update_systems(m_registry.ecs.get(), dt); }

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseBasicSystems};
  base::FrameBuffer m_frameBuffer;
  EntityManager m_registry;
  systems::MovementSystem m_movementSystem;
  systems::DataSystem m_dataSystem;
  systems::MoreComplexSystem m_moreComplexSystem;
  systems::HealthSystem m_healthSystem;
  systems::DamageSystem m_damageSystem;
  systems::SpriteSystem m_spriteSystem;
  systems::RenderSystem m_renderSystem;
};

} // namespace ecs::benchmarks::pico_ecs

#endif // ECS_BENCHMARKS_PICO_ECS_APPLICATION_H_
