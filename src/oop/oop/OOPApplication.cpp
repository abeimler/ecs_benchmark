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
  std::for_each(m_entities.game_objects.begin(), m_entities.game_objects.end(), [&](auto& entity) {
    if (entity != nullptr && !entity->destroyed()) {
      entity->update(dt);
    }
  });
  std::erase_if(m_entities.game_objects, [&](auto& entity) {
    const auto ret = entity == nullptr || entity->destroyed();
    if (ret) {
      for (auto it = m_entities.render_objects.begin(); it != m_entities.render_objects.end();)
      {
        if (it->first == entity->id())
          it = m_entities.render_objects.erase(it);
        else
          ++it;
      }
    }
    return ret;
  });
  std::for_each(m_entities.render_objects.begin(), m_entities.render_objects.end(), [&](auto& entity) {
    if (entity.second != nullptr) {
      entity.second->render(m_frameBuffer);
    }
  });
}
} // namespace ecs::benchmarks::oop