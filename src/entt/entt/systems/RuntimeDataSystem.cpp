#include "RuntimeDataSystem.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::systems {

void RuntimeDataSystem::init(EntityManager& registry) {
  m_view.iterate(registry.storage<ecs::benchmarks::base::components::DataComponent>());
}

void RuntimeDataSystem::update(EntityManager& registry, TimeDelta dt) {
  m_view.each([&registry, dt](auto entity) {
    auto& data = registry.get<ecs::benchmarks::base::components::DataComponent>(entity);
    updateData(data, dt);
  });
}

} // namespace ecs::benchmarks::entt::systems