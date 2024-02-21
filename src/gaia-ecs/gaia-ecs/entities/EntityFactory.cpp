#include "EntityFactory.h"

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::gaia_ecs::entities {

EntityFactory::Entity EntityFactory::createEmpty(EntityManager& entities) {
  return entities.add();
}

EntityFactory::Entity EntityFactory::createSingle(EntityManager& entities) {
  auto e = entities.add();
  entities.add<ecs::benchmarks::base::components::PositionComponent>(e);
  return e;
}

EntityFactory::Entity EntityFactory::create(EntityManager& entities) {
  auto e = entities.add();
  entities.bulk(e)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>()
      .add<ecs::benchmarks::base::components::DataComponent>();
  return e;
}

EntityFactory::Entity EntityFactory::createMinimal(EntityManager& entities) {
  auto e = entities.add();
  entities.bulk(e)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>();
  return e;
}

void EntityFactory::destroy(EntityManager& entities, Entity entity) {
  entities.del(entity);
}

} // namespace ecs::benchmarks::gaia_ecs::entities
