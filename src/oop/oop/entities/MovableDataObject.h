#ifndef ECS_BENCHMARKS_OOP_MOVABLEWITHDATAOBJECT_H_
#define ECS_BENCHMARKS_OOP_MOVABLEWITHDATAOBJECT_H_

#include <random>

#include "GameObject.h"
#include "MovableObject.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::oop::entities {

    class MovableDataObject : public MovableObject {
    public:
        MovableDataObject() = default;

        MovableDataObject(const MovableDataObject &) = default;

        MovableDataObject(MovableDataObject &&) = default;

        MovableDataObject &operator=(const MovableDataObject &) = default;

        MovableDataObject &operator=(MovableDataObject &&) = default;

        virtual ~MovableDataObject() = default;

        void updatePosition(float dt);

        virtual void update(float dt) override;

        [[nodiscard]] inline ecs::benchmarks::base::components::DataComponent &data() noexcept { return m_data; }

        [[nodiscard]] inline const ecs::benchmarks::base::components::DataComponent &data() const noexcept {
            return m_data;
        }

    protected:
        ecs::benchmarks::base::components::DataComponent m_data;
    };

}

#endif