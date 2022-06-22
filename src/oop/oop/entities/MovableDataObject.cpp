#include "MovableDataObject.h"
#include <string>
#include <vector>
#include <numeric>


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
        m_data.stringy = std::to_string(m_data.dingy);
    }

} // namespace ecs::benchmarks::oop::entities