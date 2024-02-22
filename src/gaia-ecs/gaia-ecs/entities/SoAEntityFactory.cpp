#include "SoAEntityFactory.h"

#include "base/components/DataComponent.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include "gaia-ecs/components/SoAVelocityComponent.h"

namespace ecs::benchmarks::gaia_ecs::entities {

SoAEntityFactory::Entity SoAEntityFactory::createEmpty(EntityManager& entities) {
  return entities.add();
}

SoAEntityFactory::Entity SoAEntityFactory::createSingle(EntityManager& entities) {
  auto e = entities.add();
  entities.add<components::SoAPositionComponent>(e);
  return e;
}

SoAEntityFactory::Entity SoAEntityFactory::create(EntityManager& entities) {
  auto e = entities.add();
  entities.bulk(e)
      .add<components::SoAPositionComponent>()
      .add<components::SoAVelocityComponent>()
      .add<ecs::benchmarks::base::components::DataComponent>();
  return e;
}

SoAEntityFactory::Entity SoAEntityFactory::createMinimal(EntityManager& entities) {
  auto e = entities.add();
  entities.bulk(e).add<components::SoAPositionComponent>().add<components::SoAVelocityComponent>();
  return e;
}

void SoAEntityFactory::destroy(EntityManager& entities, Entity entity) {
  entities.del(entity);
}

} // namespace ecs::benchmarks::gaia_ecs::entities
