#ifndef ECS_BENCHMARKS_OOP_MOVABLEOBJECT_H_
#define ECS_BENCHMARKS_OOP_MOVABLEOBJECT_H_

#include "GameObject.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"

namespace ecs::benchmarks::oop::entities {

    class MovableObject : public GameObject {
    public:
        MovableObject() = default;

        MovableObject(const MovableObject &) = default;

        MovableObject(MovableObject &&) = default;

        MovableObject &operator=(const MovableObject &) = default;

        MovableObject &operator=(MovableObject &&) = default;

        virtual ~MovableObject() = default;

        virtual void update(float dt) override;

        [[nodiscard]] inline ecs::benchmarks::base::components::PositionComponent &
        position() noexcept { return m_position; }

        [[nodiscard]] inline const ecs::benchmarks::base::components::PositionComponent &position() const noexcept {
            return m_position;
        }

        [[nodiscard]] inline ecs::benchmarks::base::components::VelocityComponent &
        velocity() noexcept { return m_velocity; }

        [[nodiscard]] inline const ecs::benchmarks::base::components::VelocityComponent &velocity() const noexcept {
            return m_velocity;
        }

    protected:
        ecs::benchmarks::base::components::PositionComponent m_position;
        ecs::benchmarks::base::components::VelocityComponent m_velocity;
    };

}

#endif