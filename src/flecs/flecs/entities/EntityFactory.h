#ifndef ECS_BENCHMARKS_FLECS_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_FLECS_ENTITYFACTORY_H_

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/entities/EntityFactory.h"
#include "flecs/custom_flecs.h"

namespace ecs::benchmarks::flecs::entities {

class EntityFactory {
public:
  using EntityManager = ::flecs::world;
  using Entity = ::flecs::entity;

  static Entity createEmpty(EntityManager& entities);
  static void createEmptyBulk(EntityManager& registry, size_t nentities);

  static Entity createSingle(EntityManager& entities);
  static void createSingleBulk(EntityManager& registry, size_t nentities);

  static Entity create(EntityManager& entities);
  static void createBulk(EntityManager& registry, size_t nentities);

  static Entity createMinimal(EntityManager& entities);
  static void createMinimalBulk(EntityManager& registry, size_t nentities);

  static void destroy(EntityManager& entities, Entity entity);
  static void destroyBulk(EntityManager& registry, std::vector<Entity>& entities);

  template <class C>
  [[nodiscard]] static inline auto getComponentCount(EntityManager& entities) {
    return entities.count<C>();
  }


  [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent&
  getComponentOneConst(EntityManager& /*entities*/, Entity entity) {
    return *entity.get<ecs::benchmarks::base::components::PositionComponent>();
  }

  [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwoConst(EntityManager& /*entities*/, Entity entity) {
    return *entity.get<ecs::benchmarks::base::components::VelocityComponent>();
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent&
  getComponentOne(EntityManager& /*entities*/, Entity entity) {
    return *entity.get_mut<ecs::benchmarks::base::components::PositionComponent>();
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwo(EntityManager& /*entities*/, Entity entity) {
    return *entity.get_mut<ecs::benchmarks::base::components::VelocityComponent>();
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent*
  getOptionalComponentThree(EntityManager& /*entities*/, Entity entity) {
    return entity.has<ecs::benchmarks::base::components::DataComponent>()
               ? entity.get_mut<ecs::benchmarks::base::components::DataComponent>()
               : nullptr;
  }


  static inline auto& removeComponentOne(EntityManager& /*entities*/, Entity entity) {
    return entity.remove<ecs::benchmarks::base::components::PositionComponent>();
  }

  static inline auto& removeComponentTwo(EntityManager& /*entities*/, Entity entity) {
    return entity.remove<ecs::benchmarks::base::components::VelocityComponent>();
  }

  static inline auto& removeComponentThree(EntityManager& /*entities*/, Entity entity) {
    return entity.remove<ecs::benchmarks::base::components::DataComponent>();
  }

  static inline auto& addComponentOne(EntityManager& /*entities*/, Entity entity) {
    return entity.add<ecs::benchmarks::base::components::PositionComponent>();
  }
};

} // namespace ecs::benchmarks::flecs::entities

#endif
