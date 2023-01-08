#ifndef ECS_BENCHMARKS_PICO_ECS_MOVEMENTSYSTEM_H_
#define ECS_BENCHMARKS_PICO_ECS_MOVEMENTSYSTEM_H_

#include <pico_ecs.h>

#include "pico_ecs/entities/EntityFactory.h"
#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::pico_ecs::systems {

class MovementSystem final : public ecs::benchmarks::base::systems::MovementSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager, ecs_dt_t> {
public:
  void init(EntityManager& /*registry*/) override;
  void update(EntityManager &registry, TimeDelta dt) override;

  inline ecs_id_t id() const noexcept { return m_system; }

private:
  ecs_id_t m_system;
};

}

#endif