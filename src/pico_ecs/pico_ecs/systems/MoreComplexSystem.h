#ifndef ECS_BENCHMARKS_PICO_ECS_MORECOMPLEXSYSTEM_H_
#define ECS_BENCHMARKS_PICO_ECS_MORECOMPLEXSYSTEM_H_

#include "base/systems/HealthSystem.h"
#include "base/systems/MoreComplexSystem.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <pico_ecs.h>
#include <span>

namespace ecs::benchmarks::pico_ecs::systems {

namespace details {

struct MoreComplexSystemContext {
  ecs::benchmarks::pico_ecs::entities::details::EntityManager* registry{nullptr};
  ecs::benchmarks::base::systems::MoreComplexSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                    ecs_dt_t>* system{nullptr};
};

} // namespace details

class MoreComplexSystem final : public ecs::benchmarks::base::systems::MoreComplexSystem<
                                    ecs::benchmarks::pico_ecs::entities::details::EntityManager, ecs_dt_t> {
public:
  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_id_t id() const noexcept { return m_system; }

private:
  ecs_id_t m_system;
  details::MoreComplexSystemContext m_context;

  static auto updateMoreComplex(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t;
};

class HealthSystem final
    : public ecs::benchmarks::base::systems::HealthSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                          ecs_dt_t> {
public:
  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_id_t id() const noexcept { return m_system; }

private:
  ecs_id_t m_system;

  static auto updateHealth(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t;
};

class DamageSystem final
    : public ecs::benchmarks::base::systems::DamageSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                          ecs_dt_t> {
public:
  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_id_t id() const noexcept { return m_system; }

private:
  ecs_id_t m_system;

  static auto updateDamage(ecs_t* ecs, std::span<ecs_id_t> entities, ecs_dt_t dt, void* udata) -> ecs_ret_t;
};

} // namespace ecs::benchmarks::pico_ecs::systems

#endif