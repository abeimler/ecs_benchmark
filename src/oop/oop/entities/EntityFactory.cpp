#include "EntityFactory.h"
#include "ComplexGameObject.h"
#include "MovableDataObject.h"
#include "MovableObject.h"
#include <algorithm>
#include <vector>

namespace ecs::benchmarks::oop::entities {

class DummyObject : public GameObject {
public:
  DummyObject() = default;
  DummyObject(const DummyObject&) = default;
  DummyObject(DummyObject&&) = default;
  DummyObject& operator=(const DummyObject&) = default;
  DummyObject& operator=(DummyObject&&) = default;
  ~DummyObject() override = default;

  void update(float /*dt*/) override {}
};

EntityFactory::Entity EntityFactory::create(EntityManager& registry) {
  auto& ret = (add_more_complex_system == base::add_more_complex_system_t::UseMoreComplexSystems)
                  ? registry.game_objects.emplace_back(std::make_shared<ComplexGameObject>())
                  : registry.game_objects.emplace_back(std::make_unique<MovableDataObject>());
  ret->id(registry.game_objects.size());
  if (add_more_complex_system == base::add_more_complex_system_t::UseMoreComplexSystems) {
    registry.render_objects[ret->id()] = std::dynamic_pointer_cast<RenderableObject>(ret);
  }
  return ret.get();
}

void EntityFactory::createBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.game_objects.reserve(registry.game_objects.size() + out.size());
  for (size_t i = 0; i < out.size(); i++) {
    auto& ret = (add_more_complex_system == base::add_more_complex_system_t::UseMoreComplexSystems)
                    ? registry.game_objects.emplace_back(std::make_unique<ComplexGameObject>())
                    : registry.game_objects.emplace_back(std::make_unique<MovableDataObject>());
    ret->id(registry.game_objects.size());
    if (add_more_complex_system == base::add_more_complex_system_t::UseMoreComplexSystems) {
      registry.render_objects[ret->id()] = std::dynamic_pointer_cast<RenderableObject>(ret);
    }
  }
}

EntityFactory::Entity EntityFactory::createMinimal(EntityManager& registry) {
  auto& ret = registry.game_objects.emplace_back(std::make_unique<MovableObject>());
  ret->id(registry.game_objects.size());
  return ret.get();
}

void EntityFactory::createMinimalBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.game_objects.reserve(registry.game_objects.size() + out.size());
  for (size_t i = 0; i < out.size(); i++) {
    auto& ret = registry.game_objects.emplace_back(std::make_unique<MovableObject>());
    ret->id(registry.game_objects.size());
  }
}

EntityFactory::Entity EntityFactory::createEmpty(EntityManager& registry) {
  auto& ret = registry.game_objects.emplace_back(std::make_unique<DummyObject>());
  ret->id(registry.game_objects.size());
  return ret.get();
}

void EntityFactory::createEmptyBulk(EntityManager& registry, std::vector<Entity>& out) {
  registry.game_objects.reserve(registry.game_objects.size() + out.size());
  for (size_t i = 0; i < out.size(); i++) {
    auto& ret = registry.game_objects.emplace_back(std::make_unique<DummyObject>());
    ret->id(registry.game_objects.size());
  }
}

void EntityFactory::destroy(EntityManager& registry, Entity entity) {
  if (entity != nullptr && entity->id() > 0) {
    registry.game_objects[entity->id() - 1]->destroy();
  }
}

void EntityFactory::destroyBulk(EntityManager& /*registry*/, std::vector<Entity>& in) {
  std::for_each(in.begin(), in.end(), [&](const auto& ptr) {
    ptr->destroy();
  });
}

void EntityFactory::remove(EntityManager& registry, Entity entity) {
  for (auto it = registry.render_objects.begin(); it != registry.render_objects.end();) {
    if (it->first == entity->id())
      it = registry.render_objects.erase(it);
    else
      ++it;
  }
  if (entity != nullptr && entity->id() > 0) {
    registry.game_objects.erase(std::next(registry.game_objects.begin(), entity->id() - 1));
  }
}

void EntityFactory::removeBulk(EntityManager& registry, std::vector<Entity>& in) {
  std::erase_if(registry.game_objects, [&](const auto& ptr) {
    auto ret = std::any_of(in.begin(), in.end(), [&](const auto& it) {
      return it == ptr.get();
    });
    if (ret) {
      for (auto it = registry.render_objects.begin(); it != registry.render_objects.end();) {
        if (it->first == ptr->id())
          it = registry.render_objects.erase(it);
        else
          ++it;
      }
    }
    return ret;
  });
}

void EntityFactory::clear(EntityManager& registry) {
  registry.game_objects.clear();
  registry.render_objects.clear();
}

} // namespace ecs::benchmarks::oop::entities
