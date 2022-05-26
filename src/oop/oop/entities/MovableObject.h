#ifndef ECS_BENCHMARKS_OOP_MOVABLEOBJECT_H_
#define ECS_BENCHMARKS_OOP_MOVABLEOBJECT_H_

#include "GameObject.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"

namespace ecs::benchmarks::oop::entities {

    class MovableObject : public GameObject {
    public:
        MovableObject() = default;
        MovableObject(const MovableObject&) = default;
        MovableObject(MovableObject&&) = default;
        MovableObject& operator=(const MovableObject&) = default;
        MovableObject& operator=(MovableObject&&) = default;
        virtual ~MovableObject() = default;

        virtual void update(float dt) override;

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

    protected:
        ecs::benchmarks::base::components::PositionComponent m_position;
        ecs::benchmarks::base::components::DirectionComponent m_direction;
    };

}

#endif