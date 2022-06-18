#include "ComplexMovableDataObject.h"
#include <vector>


namespace ecs::benchmarks::oop::entities {
    std::random_device ComplexMovableDataObject::m_rd;

    void ComplexMovableDataObject::update(float dt) {
        MovableDataObject::update(dt);

        // NOTE: copy-paste from MoreComplexSystem
        if ((m_data.thingy % 10) == 0) {
            if (m_position.x > m_position.y) {
                m_velocity.x = static_cast<float>(random(-5, 5));
                m_velocity.y = static_cast<float>(random(-10, 10));
            } else {
                m_velocity.x = static_cast<float>(random(-10, 10));
                m_velocity.y = static_cast<float>(random(-5, 5));
            }
        }
    }

    int ComplexMovableDataObject::random(int min, int max) {
        std::uniform_int_distribution<int> distr(min, max);
        return distr(m_eng);
    }

} // namespace ecs::benchmarks::oop::entities