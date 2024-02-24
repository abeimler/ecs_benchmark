#ifndef ECS_BENCHMARKS_GAIA_ECS_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_GAIA_ECS_ENTITYFACTORY_H_

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include <gaia.h>
#include <optional>

namespace ecs::benchmarks::gaia_ecs::entities {

class EntityFactory {
public:
  using EntityManager = ::gaia::ecs::World;
  using Entity = ::gaia::ecs::Entity;

  static Entity createEmpty(EntityManager& entities);

  static Entity createSingle(EntityManager& entities);

  static Entity create(EntityManager& entities);

  static Entity createMinimal(EntityManager& entities);

  static void destroy(EntityManager& entities, Entity entity);

  //[[nodiscard]] static inline auto getEntitiesCount(EntityManager& entities) {
  //  return entities.size();
  //}

  [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent&
  getComponentOneConst(EntityManager& entities, Entity entity) {
    return entities.get<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwoConst(EntityManager& entities, Entity entity) {
    return entities.get<ecs::benchmarks::base::components::VelocityComponent>(entity);
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] static inline const ecs::benchmarks::base::components::DataComponent*
  getOptionalComponentThreeConst(EntityManager& entities, Entity entity) {
    return entities.has<ecs::benchmarks::base::components::DataComponent>(entity)
               ? &entities.get<ecs::benchmarks::base::components::DataComponent>(entity)
               : nullptr;
  }


  static inline void removeComponentOne(EntityManager& entities, Entity entity) {
    return entities.del<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  static inline void removeComponentTwo(EntityManager& entities, Entity entity) {
    return entities.del<ecs::benchmarks::base::components::VelocityComponent>(entity);
  }

  static inline void removeComponentThree(EntityManager& entities, Entity entity) {
    return entities.del<ecs::benchmarks::base::components::DataComponent>(entity);
  }

  static inline void addComponentOne(EntityManager& entities, Entity entity) {
    return entities.add<ecs::benchmarks::base::components::PositionComponent>(entity);
  }
};

} // namespace ecs::benchmarks::gaia_ecs::entities

#endif
