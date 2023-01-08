#include "EntityFactory.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::flecs::entities {

EntityFactory::Entity EntityFactory::create(EntityManager& entities) {
  return entities.entity()
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>()
      .add<ecs::benchmarks::base::components::DataComponent>();
}

EntityFactory::Entity EntityFactory::createSingle(EntityManager& entities) {
  return entities.entity().add<ecs::benchmarks::base::components::PositionComponent>();
}

EntityFactory::Entity EntityFactory::createMinimal(EntityManager& entities) {
  return entities.entity()
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>();
}

EntityFactory::Entity EntityFactory::createEmpty(EntityManager& entities) {
  return entities.entity();
}

void EntityFactory::destroy(EntityManager& /*entities*/, Entity entity) {
  entity.destruct();
}
} // namespace ecs::benchmarks::flecs::entities
