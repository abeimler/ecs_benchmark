#ifndef ECS_BENCHMARKS_OOP_MOVABLEWITHDATAOBJECT_H_
#define ECS_BENCHMARKS_OOP_MOVABLEWITHDATAOBJECT_H_

#include <random>

#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::oop::entities {

    class MovableWithDataObject {
    public:
        void updatePosition(float dt);

        void updateData(float dt);

        void updateComplexData(float dt);

        inline ecs::benchmarks::base::components::PositionComponent &position() noexcept { return m_position; }

        inline const ecs::benchmarks::base::components::PositionComponent &position() const noexcept {
            return m_position;
        }

        inline ecs::benchmarks::base::components::DirectionComponent &direction() noexcept { return m_direction; }

        inline const ecs::benchmarks::base::components::DirectionComponent &direction() const noexcept {
            return m_direction;
        }

        inline ecs::benchmarks::base::components::DataComponent &data() noexcept { return m_data; }

        inline const ecs::benchmarks::base::components::DataComponent &data() const noexcept {
            return m_data;
        }

    private:
        ecs::benchmarks::base::components::PositionComponent m_position;
        ecs::benchmarks::base::components::DirectionComponent m_direction;
        ecs::benchmarks::base::components::DataComponent m_data;

        static int random(int min, int max) {
            std::uniform_int_distribution<int> distr(min, max);
            return distr(m_eng);
        }

        static std::random_device m_rd;
        static std::mt19937 m_eng;
    };

}

#endif