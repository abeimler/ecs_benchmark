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
  // NOTE: copy-paste from DataSystem
  m_data.thingy++;
  m_data.dingy += 0.0001 * static_cast<double>(dt);
  m_data.mingy = !m_data.mingy;
  /// @FIXME(pico_ecs): SIGSEGV (Segmentation fault), can't copy string ... support for components with dynamic memory
  /// (std::string) ?
  // m_data.stringy = fmt::format(FMT_STRING("{:4.2f}"), m_data.dingy);
  std::string stringy = fmt::format(FMT_STRING("{:4.2f}"), m_data.dingy);
  std::char_traits<char>::copy(m_data.stringy, stringy.data(), std::min(stringy.length(), m_data.StringyMaxLength));
}

} // namespace ecs::benchmarks::oop::entities