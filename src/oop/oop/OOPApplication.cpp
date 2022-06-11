#include "OOPApplication.h"
#include <algorithm>

namespace ecs::benchmarks::oop {

    void OOPApplication::init() {
        m_entity_factory.add_more_complex_system = m_add_more_complex_system;
    }

    void OOPApplication::uninit() {
    }

    void OOPApplication::update(TimeDelta dt) {
        std::for_each(m_entities.begin(), m_entities.end(), [dt](auto &entity) {
            if (entity != nullptr) {
                entity->update(dt);
            }
        });
    }
}