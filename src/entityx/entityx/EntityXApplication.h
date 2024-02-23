#ifndef ECS_BENCHMARKS_ENTITYX_APPLICATION_H_
#define ECS_BENCHMARKS_ENTITYX_APPLICATION_H_

#include "base/Application.h"
#include "base/FrameBuffer.h"
#include "entityx/systems/DataSystem.h"
#include "entityx/systems/MoreComplexSystem.h"
#include "entityx/systems/MovementSystem.h"
#include "entityx/systems/DamageSystem.h"
#include "entityx/systems/HealthSystem.h"
#include "entityx/systems/SpriteSystem.h"
#include "entityx/systems/RenderSystem.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx {

class EntityXApplication final : public ::entityx::EntityX {
public:
  using EntityManager = ::entityx::EntityManager;
  using TimeDelta = ::entityx::TimeDelta;
  using BaseApplication = base::Application<EntityManager, TimeDelta, systems::MovementSystem, systems::DataSystem, systems::MoreComplexSystem,
                                            systems::HealthSystem, systems::DamageSystem,
                                            systems::SpriteSystem, systems::RenderSystem>;

  EntityXApplication() = delete;
  explicit EntityXApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system)
      , m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight) {}

  inline EntityManager& getEntities() { return this->entities; }
  inline const EntityManager& getEntities() const { return this->entities; }

  void init();
  void uninit();
  void update(TimeDelta dt);

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseBasicSystems};
  base::FrameBuffer m_frameBuffer;
};

} // namespace ecs::benchmarks::entityx

#endif // ECS_BENCHMARKS_ENTITYX_APPLICATION_H_
