#include "MovableWithDataObject.h"
#include <string>
#include <vector>
#include <numeric>


namespace ecs::benchmarks::oop::entities {

    std::random_device MovableWithDataObject::m_rd;
    std::mt19937 MovableWithDataObject::m_eng(MovableWithDataObject::m_rd());

    void MovableWithDataObject::updatePosition(float dt) {
        // NOTE: copy-paste from MovementSystem
        m_position.x += m_direction.x * dt;
        m_position.y += m_direction.y * dt;
    }

    void MovableWithDataObject::updateData(float dt) {
        // NOTE: copy-paste from DataSystem
        m_data.thingy += 0.0001F * dt;
        m_data.mingy = !m_data.mingy;
        m_data.dingy++;
        m_data.stringy = std::to_string(m_data.dingy);
    }

    void MovableWithDataObject::updateComplexData(float dt) {
        // NOTE: copy-paste from MoreComplexSystem
        std::vector<int> vec;
        for (int i = 0; i < m_data.dingy && i < 100; i++) {
            vec.push_back(i * static_cast<int>(m_data.thingy));
        }

        const auto sum = std::accumulate(std::begin(vec), std::end(vec), 0);
        const auto product = std::accumulate(std::begin(vec), std::end(vec), 1, std::multiplies<>());

        m_data.dingy = sum + product;
        m_data.stringy = std::to_string(m_data.dingy);

        if (m_data.dingy % 10000 == 0) {
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