#ifndef ECS_BENCHMARK_GAMEOBJECT_H
#define ECS_BENCHMARK_GAMEOBJECT_H

#include "base/FrameBuffer.h"
#include <cstddef>

namespace ecs::benchmarks::oop::entities {
class EntityFactory;

class GameObject {
public:
  using game_object_id_t = size_t;

  GameObject() = default;
  GameObject(const GameObject&) = default;
  GameObject(GameObject&&) = default;
  GameObject& operator=(const GameObject&) = default;
  GameObject& operator=(GameObject&&) = default;
  virtual ~GameObject() = default;

  virtual void update(float dt) = 0;

  [[nodiscard]] inline game_object_id_t id() const noexcept { return m_id; }

  [[nodiscard]] inline bool destroyed() const noexcept { return m_destroyed; }
  void destroy() noexcept { m_destroyed = true; }

protected:
  explicit GameObject(game_object_id_t id) : m_id(id) {}

  inline void id(game_object_id_t id) noexcept { m_id = id; }

  friend class EntityFactory;

private:
  game_object_id_t m_id{0};
  bool m_destroyed{false};
};


class RenderableObject {
public:
  virtual ~RenderableObject() = default;

  virtual void render(base::FrameBuffer&) = 0;
};

} // namespace ecs::benchmarks::oop::entities

#endif // ECS_BENCHMARK_GAMEOBJECT_H
