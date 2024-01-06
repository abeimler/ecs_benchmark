#ifndef ECS_BENCHMARKS_GINSENG_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_GINSENG_ENTITYFACTORY_H_

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/entities/EntityFactory.h"
#include <ginseng/ginseng.hpp>

namespace ecs::benchmarks::ginseng::entities {

class EntityFactory {
public:
  using EntityManager = ::ginseng::database;
  using Entity = ::ginseng::database::ent_id;
  using Component = ::ginseng::database::com_id;

  static Entity create(EntityManager& registry);
  static Entity createMinimal(EntityManager& registry);
  static Entity createEmpty(EntityManager& registry);
  static Entity createSingle(EntityManager& registry);

  static void destroy(EntityManager& registry, Entity entity);

  [[nodiscard]] static inline auto getEntitiesCount(EntityManager& registry) { return registry.size(); }

  [[nodiscard]] static inline bool valid(EntityManager& registry, Entity entity) { return registry.exists(entity); }


  /// @FIXME: SIGSEGV (Segmentation fault), can't use const ? (std::as_const(registry))
  [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent&
  getComponentOneConst(EntityManager& registry, Entity entity) {
    return registry.get_component<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwoConst(EntityManager& registry, Entity entity) {
    return registry.get_component<ecs::benchmarks::base::components::VelocityComponent>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent&
  getComponentOne(EntityManager& registry, Entity entity) {
    return registry.get_component<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwo(EntityManager& registry, Entity entity) {
    return registry.get_component<ecs::benchmarks::base::components::VelocityComponent>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent*
  getOptionalComponentThree(EntityManager& registry, Entity entity) {
    return registry.get_component<ecs::benchmarks::base::components::DataComponent*>(entity);
  }

  static inline void removeComponentOne(EntityManager& registry, Entity entity) {
    registry.remove_component<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  static inline void removeComponentTwo(EntityManager& registry, Entity entity) {
    registry.remove_component<ecs::benchmarks::base::components::VelocityComponent>(entity);
  }

  static inline void removeComponentThree(EntityManager& registry, Entity entity) {
    registry.remove_component<ecs::benchmarks::base::components::DataComponent>(entity);
  }

  static inline auto addComponentOne(EntityManager& registry, Entity entity) {
    return registry.add_component(entity, ecs::benchmarks::base::components::PositionComponent{});
  }
};

} // namespace ecs::benchmarks::ginseng::entities

#endif