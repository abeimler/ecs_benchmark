#include "OOPApplication.h"
#include <algorithm>

namespace ecs::benchmarks::oop {

void OOPApplication::init() {
  m_entityFactory.add_more_complex_system = m_addMoreComplexSystem;
}

void OOPApplication::uninit() {
}

void OOPApplication::update(TimeDelta dt) {
  /// @TODO: use ranges to filter out destroyed objects (?)
  std::for_each(m_entities.begin(), m_entities.end(), [dt](auto& entity) {
    if (entity != nullptr && !entity->destroyed()) {
      entity->update(dt);
    }
  });
  std::erase_if(m_entities, [](auto& entity) {
    return entity == nullptr || entity->destroyed();
  });
}
} // namespace ecs::benchmarks::oop