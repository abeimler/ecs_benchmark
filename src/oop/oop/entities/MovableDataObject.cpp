#include "MovableDataObject.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <gsl-lite/gsl-lite.hpp>
#include <string>
#include <vector>


namespace ecs::benchmarks::oop::entities {

void MovableDataObject::updatePosition(float dt) {
  MovableObject::update(dt);
}

void MovableDataObject::update(float dt) {
  MovableObject::update(dt);
  m_data.thingy = (m_data.thingy + 1) % 1'000'000;
  m_data.dingy += 0.0001 * gsl::narrow_cast<double>(dt);
  m_data.mingy = !m_data.mingy;
  m_data.numgy = m_data.rng();
}

} // namespace ecs::benchmarks::oop::entities
