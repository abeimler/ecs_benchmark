#ifndef ECS_BENCHMARKS_OOP_COMPLEXMOVABLEWITHDATAOBJECT_H_
#define ECS_BENCHMARKS_OOP_COMPLEXMOVABLEWITHDATAOBJECT_H_

#include "MovableDataObject.h"

namespace ecs::benchmarks::oop::entities {

    class ComplexMovableDataObject : public MovableDataObject {
    public:
        ComplexMovableDataObject() : m_eng(m_rd()) {}

        ComplexMovableDataObject(const ComplexMovableDataObject &) = default;

        ComplexMovableDataObject(ComplexMovableDataObject &&) = default;

        ComplexMovableDataObject &operator=(const ComplexMovableDataObject &) = default;

        ComplexMovableDataObject &operator=(ComplexMovableDataObject &&) = default;

        virtual ~ComplexMovableDataObject() = default;

        virtual void update(float dt) override;

    private:
        int random(int min, int max);

        static std::random_device m_rd;
        std::mt19937 m_eng;
    };

}

#endif