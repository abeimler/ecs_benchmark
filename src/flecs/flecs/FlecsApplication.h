#ifndef ECS_BENCHMARKS_FLECS_APPLICATION_H_
#define ECS_BENCHMARKS_FLECS_APPLICATION_H_

#include "flecs/custom_flecs.h"

#include "base/Application.h"
#include "base/FrameBuffer.h"
#include "flecs/systems/DamageSystem.h"
#include "flecs/systems/DataSystem.h"
#include "flecs/systems/HealthSystem.h"
#include "flecs/systems/MoreComplexSystem.h"
#include "flecs/systems/MovementSystem.h"
#include "flecs/systems/RenderSystem.h"
#include "flecs/systems/SpriteSystem.h"

namespace ecs::benchmarks::flecs {
class FlecsApplication {
public:
  using EntityManager = ::flecs::world;
  using TimeDelta = float;
  using BaseApplication =
      ecs::benchmarks::base::Application<EntityManager, TimeDelta, systems::MovementSystem, systems::DataSystem,
                                         systems::MoreComplexSystem, systems::HealthSystem, systems::DamageSystem,
                                         systems::SpriteSystem, systems::RenderSystem>;

  FlecsApplication() : m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight) {}
  explicit FlecsApplication(base::add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system),
        m_frameBuffer(BaseApplication::FrameBufferWidth, BaseApplication::FrameBufferHeight) {}
  ~FlecsApplication() = default;
  FlecsApplication(const FlecsApplication&) = delete;
  FlecsApplication& operator=(const FlecsApplication&) = delete;
  FlecsApplication(FlecsApplication&&) = default;
  FlecsApplication& operator=(FlecsApplication&&) = default;

  [[nodiscard]] inline EntityManager& getEntities() { return m_world; }
  [[nodiscard]] inline const EntityManager& getEntities() const { return m_world; }

  void init() {
    m_world
        .system<ecs::benchmarks::base::components::PositionComponent,
                const ecs::benchmarks::base::components::VelocityComponent>()
        .run(systems::MovementSystem::update);
    m_world.system<ecs::benchmarks::base::components::DataComponent>().run(systems::DataSystem::update);
    if (m_addMoreComplexSystem == base::add_more_complex_system_t::UseMoreComplexSystems) {
      m_world
          .system<const ecs::benchmarks::base::components::PositionComponent,
                  ecs::benchmarks::base::components::VelocityComponent,
                  ecs::benchmarks::base::components::DataComponent>()
          .each(systems::MoreComplexSystem::update);
      m_world.system<ecs::benchmarks::base::components::HealthComponent>().each(systems::HealthSystem::update);
      m_world
          .system<ecs::benchmarks::base::components::HealthComponent,
                  const ecs::benchmarks::base::components::DamageComponent>()
          .each(systems::DamageSystem::update);
      m_world
          .system<ecs::benchmarks::base::components::SpriteComponent,
                  const ecs::benchmarks::base::components::PlayerComponent,
                  const ecs::benchmarks::base::components::HealthComponent>()
          .each(systems::SpriteSystem::update);
      m_world
          .system<const ecs::benchmarks::base::components::PositionComponent,
                  const ecs::benchmarks::base::components::SpriteComponent>()
          .each([this](const ecs::benchmarks::base::components::PositionComponent& position,
                       const ecs::benchmarks::base::components::SpriteComponent& spr) {
            systems::RenderSystem::update(m_frameBuffer, position, spr);
          });
    }
  }

  void uninit() {
    /// @TODO: remove system for better clean up
  }

  void update(TimeDelta dt) { m_world.progress(dt); }

private:
  base::add_more_complex_system_t m_addMoreComplexSystem{base::add_more_complex_system_t::UseBasicSystems};
  base::FrameBuffer m_frameBuffer;
  EntityManager m_world;
};
} // namespace ecs::benchmarks::flecs

#endif // ECS_BENCHMARKS_FLECS_APPLICATION_H_
