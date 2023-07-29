#ifndef ECS_BENCHMARKS_MUSTACHE_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_MUSTACHE_ENTITYFACTORY_H_

#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/entities/EntityFactory.h"
/// @FIXME: uint32_t for found in "mustache/ecs/system.hpp"
#include <cstdint>
#include <mustache/ecs/ecs.hpp>

namespace ecs::benchmarks::mustache::entities {

template <bool tdestroy_now = true>
class EntityFactoryImpl {
private:
  inline static constexpr bool destroy_now = tdestroy_now;

public:
  using EntityManager = ::mustache::EntityManager;
  using Entity = ::mustache::Entity;

  auto create(EntityManager& registry) {
    return registry.create<ecs::benchmarks::base::components::PositionComponent,
                           ecs::benchmarks::base::components::VelocityComponent,
                           ecs::benchmarks::base::components::DataComponent>();
  }

  auto createMinimal(EntityManager& registry) {
    return registry.create<ecs::benchmarks::base::components::PositionComponent,
                           ecs::benchmarks::base::components::VelocityComponent>();
  }

  auto createEmpty(EntityManager& registry) { return registry.create(); }

  auto createSingle(EntityManager& registry) {
    return registry.create<ecs::benchmarks::base::components::PositionComponent>();
  }

  void destroy(EntityManager& registry, Entity entity) {
    if constexpr (destroy_now) {
      registry.destroyNow(entity);
    } else {
      registry.destroy(entity);
    }
  }

  void clear(EntityManager& registry) { registry.clear(); }


  [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent&
  getComponentOneConst(EntityManager& registry, Entity entity) {
    return *registry.getComponent<const ecs::benchmarks::base::components::PositionComponent,
                                  ::mustache::FunctionSafety::kUnsafe>(entity);
  }

  [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwoConst(EntityManager& registry, Entity entity) {
    return *registry.getComponent<const ecs::benchmarks::base::components::VelocityComponent,
                                  ::mustache::FunctionSafety::kUnsafe>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent&
  getComponentOne(EntityManager& registry, Entity entity) {
    return *registry.getComponent<ecs::benchmarks::base::components::PositionComponent,
                                  ::mustache::FunctionSafety::kUnsafe>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwo(EntityManager& registry, Entity entity) {
    return *registry.getComponent<ecs::benchmarks::base::components::VelocityComponent,
                                  ::mustache::FunctionSafety::kUnsafe>(entity);
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent*
  getOptionalComponentThree(EntityManager& registry, Entity entity) {
    return registry.getComponent<ecs::benchmarks::base::components::DataComponent>(entity);
  }


  static inline void removeComponentOne(EntityManager& entities, Entity entity) {
    entities.removeComponent<ecs::benchmarks::base::components::PositionComponent>(entity);
  }

  static inline void removeComponentTwo(EntityManager& entities, Entity entity) {
    entities.removeComponent<ecs::benchmarks::base::components::VelocityComponent>(entity);
  }

  static inline void removeComponentThree(EntityManager& entities, Entity entity) {
    entities.removeComponent<ecs::benchmarks::base::components::DataComponent>(entity);
  }

  static inline auto& addComponentOne(EntityManager& entities, Entity entity) {
    return entities.assign<ecs::benchmarks::base::components::PositionComponent>(entity);
  }
};

using EntityFactory = EntityFactoryImpl<true>;
} // namespace ecs::benchmarks::mustache::entities

#endif