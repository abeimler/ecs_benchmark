#include "MovableWithDataObject.h"
#include "base/systems/ComflabSystem.h"
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>


namespace ecs::benchmarks::oop::entities {

    std::random_device MovableWithDataObject::m_rd;
    std::mt19937 MovableWithDataObject::m_eng(MovableWithDataObject::m_rd());

    void MovableWithDataObject::updatePosition(float dt) {
        // NOTE: copy-paste from MovementSystem
        m_position.x += m_direction.x * dt;
        m_position.y += m_direction.y * dt;
    }

    void MovableWithDataObject::updateComflab(float dt) {
        // NOTE: copy-paste from ComflabSystem
        m_comflab.thingy += 0.0001F * dt;
        m_comflab.mingy = !m_comflab.mingy;
        m_comflab.dingy++;
        m_comflab.stringy = std::to_string(m_comflab.dingy);
    }

    void MovableWithDataObject::updateData(float dt) {
        // NOTE: copy-paste from MoreComplexSystem
        std::vector<int> vec;
        for (int i = 0; i < m_comflab.dingy && i < 100; i++) {
            vec.push_back(i * static_cast<int>(m_comflab.thingy));
        }

        const auto sum = std::accumulate(std::begin(vec), std::end(vec), 0);
        const auto product = std::accumulate(std::begin(vec), std::end(vec), 1, std::multiplies<>());

        m_comflab.dingy = sum + product;
        m_comflab.stringy = std::to_string(m_comflab.dingy);

        if (m_comflab.dingy % 10000 == 0) {
            if (m_position.x > m_position.y) {
                m_direction.x = static_cast<float>(random(0, 5)) * dt;
                m_direction.y = static_cast<float>(random(0, 10)) * dt;
            } else {
                m_direction.x = static_cast<float>(random(0, 10)) * dt;
                m_direction.y = static_cast<float>(random(0, 5)) * dt;
            }
        }
    }

} // namespace ecs::benchmarks::oop::entities