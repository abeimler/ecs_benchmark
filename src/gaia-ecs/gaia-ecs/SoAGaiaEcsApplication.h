#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAAPPLICATION_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAAPPLICATION_H_

#include "base/Application.h"

#include "gaia-ecs/systems/DamageSystem.h"
#include "gaia-ecs/systems/DataSystem.h"
#include "gaia-ecs/systems/HealthSystem.h"
#include "gaia-ecs/systems/SpriteSystem.h"
#include "gaia-ecs/systems/soa/SoAMoreComplexSystem.h"
#include "gaia-ecs/systems/soa/SoAMovementSystem.h"
#include "gaia-ecs/systems/soa/SoARenderSystem.h"
#include <gaia.h>

namespace ecs::benchmarks::gaia_ecs {

class SoAGaiaEcsApplication {
public:
  using EntityManager = ::gaia::ecs::World;
  using TimeDelta = float;
  using BaseApplication =
      ecs::benchmarks::base::Application<EntityManager, TimeDelta, systems::SoAMovementSystem, systems::DataSystem,
                                         systems::SoAMoreComplexSystem, systems::HealthSystem, systems::DamageSystem,
                                         systems::SpriteSystem, systems::SoARenderSystem>;

  SoAGaiaEcsApplication()
      : m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight), m_sm(m_world) {}

  explicit SoAGaiaEcsApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system),
        m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight), m_sm(m_world) {}

  ~SoAGaiaEcsApplication() = default;
  SoAGaiaEcsApplication(const SoAGaiaEcsApplication&) = delete;
  SoAGaiaEcsApplication& operator=(const SoAGaiaEcsApplication&) = delete;
  SoAGaiaEcsApplication(SoAGaiaEcsApplication&&) = delete;
  SoAGaiaEcsApplication& operator=(SoAGaiaEcsApplication&&) = delete;

  [[nodiscard]] inline EntityManager& getEntities() { return m_world; }
  [[nodiscard]] inline const EntityManager& getEntities() const { return m_world; }

  void init() {
    m_sm.add<systems::SoAMovementSystem>();
    m_sm.add<systems::DataSystem>();
    if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
      m_sm.add<systems::SoAMoreComplexSystem>();
      m_sm.add<systems::HealthSystem>();
      m_sm.add<systems::DamageSystem>();
      m_sm.add<systems::SpriteSystem>();
      auto* renderSystem = m_sm.add<systems::SoARenderSystem>();
      renderSystem->setFrameBuffer(m_frameBuffer);
    }
  }

  void uninit() { m_sm.clear(); }

  void update(TimeDelta /*dt*/) { m_sm.update(); }

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseMoreComplexSystems};
  base::FrameBuffer m_frameBuffer;
  EntityManager m_world;
  ::gaia::ecs::SystemManager m_sm;
};

} // namespace ecs::benchmarks::gaia_ecs

#endif // ECS_BENCHMARKS_GAIA_ECS_APPLICATION_H_
