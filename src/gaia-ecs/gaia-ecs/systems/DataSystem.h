#ifndef ECS_BENCHMARKS_GAIA_ECS_DATASYSTEM_H_
#define ECS_BENCHMARKS_GAIA_ECS_DATASYSTEM_H_

#include "base/systems/DataSystem.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <gaia.h>
#include <gsl-lite/gsl-lite.hpp>
#include <string>

namespace ecs::benchmarks::gaia_ecs::systems {

class DataSystem final : public ::gaia::ecs::System {
public:
  using TimeDelta = float;
  using Entity = ::gaia::ecs::Entity;
  using EntityManager = ::gaia::ecs::World;
  using BaseSystem = ecs::benchmarks::base::systems::DataSystem<EntityManager, TimeDelta>;

  void OnCreated() override { m_q = world().query().all<ecs::benchmarks::base::components::DataComponent&>(); }

  void OnUpdate() override {
    constexpr TimeDelta dt = 1.0F / 60.0F;
    m_q.each([&](ecs::benchmarks::base::components::DataComponent& data) {
      BaseSystem::updateData(data, dt);
    });
  }

private:
  ::gaia::ecs::Query m_q;
};

} // namespace ecs::benchmarks::gaia_ecs::systems

#endif
