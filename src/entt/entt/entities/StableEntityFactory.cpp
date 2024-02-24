#include "StableEntityFactory.h"
#include "base/components/DataComponent.h"
#include "entt/components/StablePositionComponent.h"
#include "entt/components/StableVelocityComponent.h"

namespace ecs::benchmarks::entt::entities {

StableEntityFactory::Entity StableEntityFactory::createEmpty(EntityManager& registry) {
  return registry.create();
}

void StableEntityFactory::createEmptyBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.create(out.begin(), out.end());
}

StableEntityFactory::Entity StableEntityFactory::create(EntityManager& registry) {
  auto ret = registry.create();
  registry.emplace<components::StablePositionComponent>(ret);
  registry.emplace<components::StableVelocityComponent>(ret);
  registry.emplace<ecs::benchmarks::base::components::DataComponent>(ret);
  return ret;
}

void StableEntityFactory::createBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.create(out.begin(), out.end());
  registry.insert<components::StablePositionComponent>(out.begin(), out.end());
  registry.insert<components::StableVelocityComponent>(out.begin(), out.end());
  registry.insert<ecs::benchmarks::base::components::DataComponent>(out.begin(), out.end());
}

StableEntityFactory::Entity StableEntityFactory::createMinimal(EntityManager& registry) {
  auto ret = registry.create();
  registry.emplace<components::StablePositionComponent>(ret);
  registry.emplace<components::StableVelocityComponent>(ret);
  return ret;
}

void StableEntityFactory::createMinimalBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.create(out.begin(), out.end());
  registry.insert<components::StablePositionComponent>(out.begin(), out.end());
  registry.insert<components::StableVelocityComponent>(out.begin(), out.end());
}

StableEntityFactory::Entity StableEntityFactory::createSingle(EntityManager& registry) {
  auto ret = registry.create();
  registry.emplace<ecs::benchmarks::entt::components::StablePositionComponent>(ret);
  return ret;
}

void StableEntityFactory::createSingleBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.create(out.begin(), out.end());
  registry.insert<components::StablePositionComponent>(out.begin(), out.end());
}

void StableEntityFactory::destroy(EntityManager& registry, Entity entity) {
  registry.destroy(entity);
}

void StableEntityFactory::destroyBulk(EntityManager& registry, std::vector<Entity>& entities) {
  registry.destroy(entities.begin(), entities.end());
}

} // namespace ecs::benchmarks::entt::entities
