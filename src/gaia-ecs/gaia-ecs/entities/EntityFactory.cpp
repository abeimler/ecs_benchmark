#include "EntityFactory.h"

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::gaia_ecs::entities {

EntityFactory::Entity EntityFactory::createEmpty(EntityManager& entities) {
  return entities.add();
}

void EntityFactory::createEmptyBulk(EntityManager& entities, size_t nentities) {
  entities.add_n(static_cast<uint32_t>(nentities));
}

EntityFactory::Entity EntityFactory::createSingle(EntityManager& entities) {
  auto e = entities.add();
  entities.add<ecs::benchmarks::base::components::PositionComponent>(e);
  return e;
}

void EntityFactory::createSingleBulk(EntityManager& entities, size_t nentities) {
  auto e = entities.add();
  entities.add<ecs::benchmarks::base::components::PositionComponent>(e);
  entities.add_n(e, static_cast<uint32_t>(nentities-1U));
}

EntityFactory::Entity EntityFactory::create(EntityManager& entities) {
  auto e = entities.add();
  entities.build(e)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>()
      .add<ecs::benchmarks::base::components::DataComponent>();
  return e;
}

void EntityFactory::createBulk(EntityManager& entities, size_t nentities) {
  auto e = entities.add();
  entities.build(e)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>()
      .add<ecs::benchmarks::base::components::DataComponent>();
  entities.add_n(e, static_cast<uint32_t>(nentities-1U));
}

EntityFactory::Entity EntityFactory::createMinimal(EntityManager& entities) {
  auto e = entities.add();
  entities.build(e)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>();
  return e;
}

void EntityFactory::createMinimalBulk(EntityManager& entities, size_t nentities) {
  auto e = entities.add();
  entities.build(e)
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>();
  entities.add_n(e, static_cast<uint32_t>(nentities-1U));
}

void EntityFactory::destroy(EntityManager& entities, Entity entity) {
  entities.del(entity);
}

void EntityFactory::destroyBulk(EntityManager& entities, std::vector<Entity>& entities_vec) {
  for (auto entity : entities_vec) {
    entities.del(entity);
  }
}

} // namespace ecs::benchmarks::gaia_ecs::entities
