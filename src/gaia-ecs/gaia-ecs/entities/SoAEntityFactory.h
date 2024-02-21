#ifndef ECS_BENCHMARKS_GAIA_ECS_SOAENTITYFACTORY_H_
#define ECS_BENCHMARKS_GAIA_ECS_SOAENTITYFACTORY_H_

#include "base/components/DataComponent.h"
#include "gaia-ecs/components/SoAPositionComponent.h"
#include "gaia-ecs/components/SoAVelocityComponent.h"
#include <gaia.h>
#include <optional>

namespace ecs::benchmarks::gaia_ecs::entities {

class SoAEntityFactory {
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

  [[nodiscard]] static inline const components::SoAPositionComponent&
  getComponentOneConst(EntityManager& entities, Entity entity) {
    return entities.get<components::SoAPositionComponent>(entity);
  }

  [[nodiscard]] static inline const components::SoAVelocityComponent&
  getComponentTwoConst(EntityManager& entities, Entity entity) {
    return entities.get<components::SoAVelocityComponent>(entity);
  }

  [[nodiscard]] static inline const components::SoAPositionComponent&
  getComponentOne(EntityManager& entities, Entity entity) {
    return entities.get<components::SoAPositionComponent>(entity);
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] static inline components::SoAVelocityComponent&
  getComponentTwo(EntityManager& entities, Entity entity) {
    return *const_cast<components::SoAVelocityComponent*>(
        &entities.get<components::SoAVelocityComponent>(entity));
  }

  /// @FIXME: get component as non-const
  [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent*
  getOptionalComponentThree(EntityManager& entities, Entity entity) {
    return entities.has<ecs::benchmarks::base::components::DataComponent>(entity)
               ? const_cast<ecs::benchmarks::base::components::DataComponent*>(
                     &entities.get<ecs::benchmarks::base::components::DataComponent>(entity))
               : nullptr;
  }


  static inline void removeComponentOne(EntityManager& entities, Entity entity) {
    return entities.del<components::SoAPositionComponent>(entity);
  }

  static inline void removeComponentTwo(EntityManager& entities, Entity entity) {
    return entities.del<components::SoAVelocityComponent>(entity);
  }

  static inline void removeComponentThree(EntityManager& entities, Entity entity) {
    return entities.del<ecs::benchmarks::base::components::DataComponent>(entity);
  }

  static inline void addComponentOne(EntityManager& entities, Entity entity) {
    return entities.add<components::SoAPositionComponent>(entity);
  }
};

} // namespace ecs::benchmarks::gaia_ecs::entities

#endif
