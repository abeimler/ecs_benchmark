#ifndef ECS_BENCHMARKS_OOP_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_OOP_ENTITYFACTORY_H_

#include "GameObject.h"
#include "MovableDataObject.h"
#include "MovableObject.h"
#include "base/Application.h"
#include "base/components/DataComponent.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/entities/EntityFactory.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace ecs::benchmarks::oop::entities {

struct EntityManager {
  std::vector<std::shared_ptr<GameObject>> game_objects;
  std::unordered_map<GameObject::game_object_id_t, std::shared_ptr<RenderableObject>> render_objects;
};

class EntityFactory {
public:
  using Entity = GameObject*;
  using EntityManager = EntityManager;

  base::add_more_complex_system_t add_more_complex_system{base::add_more_complex_system_t::UseBasicSystems};

  Entity createEmpty(EntityManager& registry);
  void createEmptyBulk(EntityManager& registry, std::vector<Entity>& out);

  Entity create(EntityManager& registry);
  void createBulk(EntityManager& registry, std::vector<Entity>& out);

  Entity createMinimal(EntityManager& registry);
  void createMinimalBulk(EntityManager& registry, std::vector<Entity>& out);

  void destroy(EntityManager& registry, Entity entity);
  void destroyBulk(EntityManager& registry, std::vector<Entity>& in);

  void remove(EntityManager& registry, Entity entity);
  void removeBulk(EntityManager& registry, std::vector<Entity>& in);

  void clear(EntityManager& registry);


  [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent&
  getComponentOne(EntityManager& /*registry*/, MovableObject& entity) {
    return entity.position();
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent&
  getComponentTwo(EntityManager& /*registry*/, MovableObject& entity) {
    return entity.velocity();
  }

  [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent*
  getOptionalComponentThree(EntityManager& /*registry*/, MovableDataObject& entity) {
    return &entity.data();
  }
};

} // namespace ecs::benchmarks::oop::entities

#endif