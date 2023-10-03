#ifndef ECS_BENCHMARKS_ENTITYX_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTITYX_ENTITYFACTORY_H_

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/entities/EntityFactory.h"
#include <entityx/entityx.h>

namespace ecs::benchmarks::entityx::entities {

class EntityFactory {
public:
  using EntityManager = ::entityx::EntityManager;
  using Entity = ::entityx::Entity;

  static Entity create(EntityManager& registry);
  static Entity createMinimal(EntityManager& registry);
  static Entity createSingle(EntityManager& registry);
  static Entity createEmpty(EntityManager& registry);

  static void destroy(EntityManager& registry, Entity entity);

  static void clear(EntityManager& registry);


  [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent&
  getComponentOneConst(EntityManager& entities, Entity entity) {
    return *entities.component<const ecs::benchmarks::base::components::PositionComponent>(entity.id());
  }

  [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwoConst(EntityManager& entities, Entity entity) {
    return *entities.component<const ecs::benchmarks::base::components::VelocityComponent>(entity.id());
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent&
  getComponentOne(EntityManager& entities, Entity entity) {
    return *entities.component<ecs::benchmarks::base::components::PositionComponent>(entity.id());
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwo(EntityManager& entities, Entity entity) {
    return *entities.component<ecs::benchmarks::base::components::VelocityComponent>(entity.id());
  }

  [[nodiscard]] static inline auto getOptionalComponentThree(EntityManager& entities, Entity entity) {
    return entities.component<ecs::benchmarks::base::components::DataComponent>(entity.id());
  }

  static inline void removeComponentOne(EntityManager& /*entities*/, Entity entity) {
    entity.remove<ecs::benchmarks::base::components::PositionComponent>();
  }

  static inline void removeComponentTwo(EntityManager& /*entities*/, Entity entity) {
    entity.remove<ecs::benchmarks::base::components::VelocityComponent>();
  }

  static inline void removeComponentThree(EntityManager& /*entities*/, Entity entity) {
    entity.remove<ecs::benchmarks::base::components::DataComponent>();
  }

  static inline auto addComponentOne(EntityManager& /*entities*/, Entity entity) {
    return entity.assign<ecs::benchmarks::base::components::PositionComponent>();
  }
};

} // namespace ecs::benchmarks::entityx::entities

#endif