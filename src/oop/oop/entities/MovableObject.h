#ifndef ECS_BENCHMARKS_OOP_MOVABLEOBJECT_H_
#define ECS_BENCHMARKS_OOP_MOVABLEOBJECT_H_

#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::oop::entities {

    class MovableObject {
    public:
        void update(float dt);

        [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent &
        position() noexcept { return m_position; }

        inline const ecs::benchmarks::base::components::PositionComponent &position() const noexcept {
            return m_position;
        }

        [[nodiscard]] inline ecs::benchmarks::base::components::DirectionComponent &
        direction() noexcept { return m_direction; }

        [[nodiscard]] inline const ecs::benchmarks::base::components::DirectionComponent &direction() const noexcept {
            return m_direction;
        }

    private:
        ecs::benchmarks::base::components::PositionComponent m_position;
        ecs::benchmarks::base::components::DirectionComponent m_direction;
    };

}

#endif