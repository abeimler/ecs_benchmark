#include "EntityFactory.h"

#include <gsl/gsl-lite.hpp>

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::flecs::entities {

EntityFactory::Entity EntityFactory::createEmpty(EntityManager& entities) {
  return entities.entity();
}

void EntityFactory::createEmptyBulk(EntityManager& registry, size_t nentities) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(nentities);
  ecs_bulk_init(registry, &desc);
}

/*void EntityFactory::createEmptyBulk(EntityManager& registry, std::vector<Entity>& out) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(out.size());
  const ecs_entity_t *entities = ecs_bulk_init(registry, &desc);
  for (size_t i = 0; i < out.size(); ++i) {
    out[i] = Entity{registry, entities[i]};
  }
}*/

EntityFactory::Entity EntityFactory::createSingle(EntityManager& entities) {
  return entities.entity()
      .add<ecs::benchmarks::base::components::PositionComponent>();
}

void EntityFactory::createSingleBulk(EntityManager& registry, size_t nentities) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(nentities);
  desc.ids[0] = registry.id<ecs::benchmarks::base::components::PositionComponent>();
  ecs_bulk_init(registry, &desc);
}

/*void EntityFactory::createSingleBulk(EntityManager& registry, std::vector<Entity>& out) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(out.size());
  desc.ids[0] = registry.id<ecs::benchmarks::base::components::PositionComponent>();
  const ecs_entity_t *entities = ecs_bulk_init(registry, &desc);
  for (size_t i = 0; i < out.size(); ++i) {
    out[i] = Entity{registry, entities[i]};
  }
}*/

EntityFactory::Entity EntityFactory::create(EntityManager& entities) {
  return entities.entity()
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>()
      .add<ecs::benchmarks::base::components::DataComponent>();
}

void EntityFactory::createBulk(EntityManager& registry, size_t nentities) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(nentities);
  desc.ids[0] = registry.id<ecs::benchmarks::base::components::PositionComponent>();
  desc.ids[1] = registry.id<ecs::benchmarks::base::components::VelocityComponent>();
  desc.ids[2] = registry.id<ecs::benchmarks::base::components::DataComponent>();
  ecs_bulk_init(registry, &desc);
}

/*void EntityFactory::createBulk(EntityManager& registry, std::vector<Entity>& out) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(out.size());
  desc.ids[0] = registry.id<ecs::benchmarks::base::components::PositionComponent>();
  desc.ids[1] = registry.id<ecs::benchmarks::base::components::VelocityComponent>();
  desc.ids[2] = registry.id<ecs::benchmarks::base::components::DataComponent>();
  const ecs_entity_t *entities = ecs_bulk_init(registry, &desc);
  for (size_t i = 0; i < out.size(); ++i) {
    out[i] = Entity{registry, entities[i]};
  }
}*/

EntityFactory::Entity EntityFactory::createMinimal(EntityManager& entities) {
  return entities.entity()
      .add<ecs::benchmarks::base::components::PositionComponent>()
      .add<ecs::benchmarks::base::components::VelocityComponent>();
}

void EntityFactory::createMinimalBulk(EntityManager& registry, size_t nentities) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(nentities);
  desc.ids[0] = registry.id<ecs::benchmarks::base::components::PositionComponent>();
  desc.ids[1] = registry.id<ecs::benchmarks::base::components::VelocityComponent>();
  ecs_bulk_init(registry, &desc);
}

/*void EntityFactory::createMinimalBulk(EntityManager& registry, std::vector<Entity>& out) {
  ecs_bulk_desc_t desc{0};
  desc.count = gsl::narrow_cast<int32_t>(out.size());
  desc.ids[0] = registry.id<ecs::benchmarks::base::components::PositionComponent>();
  desc.ids[1] = registry.id<ecs::benchmarks::base::components::VelocityComponent>();
  const ecs_entity_t *entities = ecs_bulk_init(registry, &desc);
  for (size_t i = 0; i < out.size(); ++i) {
    out[i] = Entity{registry, entities[i]};
  }
}*/

void EntityFactory::destroy(EntityManager& /*entities*/, Entity entity) {
  entity.destruct();
}

void EntityFactory::destroyBulk(EntityManager& /*registry*/, std::vector<Entity>& entities) {
  for (auto& entity : entities) {
    entity.destruct();
  }
}
} // namespace ecs::benchmarks::flecs::entities
