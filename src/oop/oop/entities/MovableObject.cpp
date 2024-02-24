#include "MovableObject.h"
#include "base/systems/MovementSystem.h"

namespace ecs::benchmarks::oop::entities {
void MovableObject::update(float dt) {
  // NOTE: copy-paste from MovementSystem
  m_position.x += m_direction.x * dt;
  m_position.y += m_direction.y * dt;
}
} // namespace ecs::benchmarks::oop::entities