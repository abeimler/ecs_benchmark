#ifndef ECS_BENCHMARKS_BASE_APPLICATION_H_
#define ECS_BENCHMARKS_BASE_APPLICATION_H_

#include "FrameBuffer.h"
#include "base/systems/System.h"
#include <cstdint>
#include <gsl/gsl-lite.hpp>
#include <memory>

namespace ecs::benchmarks::base {

enum class add_more_complex_system_t : bool { UseBasicSystems = false, UseMoreComplexSystems = true };

template <class tEntityManager, typename tTimeDelta, class MovementSystem, class DataSystem, class MoreComplexSystem,
          class HealthSystem, class DamageSystem, class SpriteSystem, class RenderSystem>
class Application {
public:
  using EntityManager = tEntityManager;
  using TimeDelta = tTimeDelta;

  inline static constexpr uint32_t FrameBufferWidth = 320;
  inline static constexpr uint32_t FrameBufferHeight = 240;
  inline static constexpr size_t FrameBufferSize =
      gsl::narrow_cast<size_t>(FrameBufferWidth) * gsl::narrow_cast<size_t>(FrameBufferHeight);

  Application() : m_frameBuffer(FrameBufferWidth, FrameBufferHeight) {}
  explicit Application(add_more_complex_system_t add_more_complex_system)
      : m_addMoreComplexSystem(add_more_complex_system), m_frameBuffer(FrameBufferWidth, FrameBufferHeight) {}

  virtual ~Application() = default;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) noexcept = default;
  Application& operator=(Application&&) noexcept = default;

  inline EntityManager& getEntities() noexcept { return m_entities; }

  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createMovementSystem(EntityManager& /*entities*/) {
    return std::make_unique<MovementSystem>();
  }

  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createDataSystem(EntityManager& /*entities*/) {
    return std::make_unique<DataSystem>();
  }

  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createMoreComplexSystem(EntityManager& /*entities*/) {
    return std::make_unique<MoreComplexSystem>();
  }

  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createHealthSystem(EntityManager& /*entities*/) {
    return std::make_unique<HealthSystem>();
  }
  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createDamageSystem(EntityManager& /*entities*/) {
    return std::make_unique<DamageSystem>();
  }

  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createSpriteSystem(EntityManager& /*entities*/) {
    return std::make_unique<SpriteSystem>();
  }
  std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
  createRenderSystem(EntityManager& /*entities*/) {
    return std::make_unique<RenderSystem>(m_frameBuffer);
  }

  virtual void init() {
    m_systems.emplace_back(createMovementSystem(m_entities));
    m_systems.emplace_back(createDataSystem(m_entities));
    if (m_addMoreComplexSystem == add_more_complex_system_t::UseMoreComplexSystems) {
      m_systems.emplace_back(createMoreComplexSystem(m_entities));
      m_systems.emplace_back(createHealthSystem(m_entities));
      m_systems.emplace_back(createDamageSystem(m_entities));
      m_systems.emplace_back(createSpriteSystem(m_entities));
      m_systems.emplace_back(createRenderSystem(m_entities));
    }

    for (auto& system : m_systems) {
      system->init(m_entities);
    }
  }

  virtual void uninit() { m_systems.clear(); }

  void update(TimeDelta dt) {
    for (auto& system : m_systems) {
      if (system != nullptr) {
        system->update(m_entities, dt);
      }
    }
  }

protected:
  add_more_complex_system_t m_addMoreComplexSystem{add_more_complex_system_t::UseBasicSystems};
  FrameBuffer m_frameBuffer;
  EntityManager m_entities;
  std::vector<std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>> m_systems;
};

} // namespace ecs::benchmarks::base

#endif