#include "EntityFactory.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::ginseng::entities {

EntityFactory::Entity EntityFactory::create(EntityManager& registry) {
  auto ret = registry.create_entity();
  registry.add_component(ret, ecs::benchmarks::base::components::PositionComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::VelocityComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::DataComponent{});
  return ret;
}

EntityFactory::Entity EntityFactory::createMinimal(EntityManager& registry) {
  auto ret = registry.create_entity();
  registry.add_component(ret, ecs::benchmarks::base::components::PositionComponent{});
  registry.add_component(ret, ecs::benchmarks::base::components::VelocityComponent{});
  return ret;
}

EntityFactory::Entity EntityFactory::createEmpty(EntityManager& registry) {
  return registry.create_entity();
}

EntityFactory::Entity EntityFactory::createSingle(EntityManager& registry) {
  auto ret = registry.create_entity();
  registry.add_component(ret, ecs::benchmarks::base::components::PositionComponent{});
  return ret;
}

void EntityFactory::destroy(EntityManager& registry, Entity entity) {
  registry.destroy_entity(entity);
}
} // namespace ecs::benchmarks::ginseng::entities
