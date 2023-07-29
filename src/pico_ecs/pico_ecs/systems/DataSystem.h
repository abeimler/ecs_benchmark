#ifndef ECS_BENCHMARKS_PICO_ECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_PICO_ECS_DATASYSTEM_H_

#include "base/systems/DataSystem.h"
#include "pico_ecs/entities/EntityFactory.h"
#include <pico_ecs.h>

namespace ecs::benchmarks::pico_ecs::systems {

class DataSystem final
    : public ecs::benchmarks::base::systems::DataSystem<ecs::benchmarks::pico_ecs::entities::details::EntityManager,
                                                        ecs_dt_t> {
public:
  void init(EntityManager& /*registry*/) override;
  void update(EntityManager& registry, TimeDelta dt) override;

  [[nodiscard]] inline ecs_id_t id() const noexcept { return m_system; }

private:
  ecs_id_t m_system;
};

} // namespace ecs::benchmarks::pico_ecs::systems

#endif