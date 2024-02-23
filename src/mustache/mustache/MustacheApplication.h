#ifndef ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_
#define ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_

/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>

#include "base/Application.h"
#include "mustache/systems/DamageSystem.h"
#include "mustache/systems/DataSystem.h"
#include "mustache/systems/HealthSystem.h"
#include "mustache/systems/MoreComplexSystem.h"
#include "mustache/systems/MovementSystem.h"
#include "mustache/systems/RenderSystem.h"
#include "mustache/systems/SpriteSystem.h"
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache {
class MustacheApplication {
public:
  using TimeDelta = float;
  using EntityManager = ::mustache::EntityManager;
  using BaseApplication =
      ecs::benchmarks::base::Application<EntityManager, TimeDelta, systems::MovementSystem, systems::DataSystem,
                                         systems::MoreComplexSystem, systems::HealthSystem, systems::DamageSystem,
                                         systems::SpriteSystem, systems::RenderSystem>;

  MustacheApplication() : m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight) {}
  explicit MustacheApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system),
        m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight) {}
  ~MustacheApplication() = default;
  MustacheApplication(const MustacheApplication&) = delete;
  MustacheApplication& operator=(const MustacheApplication&) = delete;
  MustacheApplication(MustacheApplication&&) = default;
  MustacheApplication& operator=(MustacheApplication&&) = default;

  inline EntityManager& getEntities() { return m_world.entities(); }

  void init() {
    m_world.systems().addSystem<systems::MovementSystem>();
    m_world.systems().addSystem<systems::DataSystem>();
    if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
      m_world.systems().addSystem<systems::MoreComplexSystem>();
      m_world.systems().addSystem<systems::HealthSystem>();
      m_world.systems().addSystem<systems::DamageSystem>();
      m_world.systems().addSystem<systems::SpriteSystem>();
      m_world.systems().addSystem<systems::RenderSystem>(m_frameBuffer);
    }
    m_world.init();
  }

  void uninit() {
    /// @FIXME: remove system/uninit, SIGSEGV (Segmentation fault), reorderingSystems
    /*
    if (m_add_more_complex_system) {
        m_world.systems().removeSystem<systems::MoreComplexSystem>();
    }
    m_world.systems().removeSystem<systems::DataSystem>();
    m_world.systems().removeSystem<systems::MovementSystem>();
    m_world.systems().removeSystem<systems::HealthSystem>();
    m_world.systems().removeSystem<systems::DamageSystem>();
     */
  }

  void update(TimeDelta /*dt*/) { m_world.update(); }

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseBasicSystems};
  base::FrameBuffer m_frameBuffer;
  ::mustache::World m_world;
};
} // namespace ecs::benchmarks::mustache

#endif // ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_
