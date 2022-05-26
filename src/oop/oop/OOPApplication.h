#ifndef ECS_BENCHMARKS_OOP_APPLICATION_H_
#define ECS_BENCHMARKS_OOP_APPLICATION_H_

#include "base/Application.h"

#include "entities/EntityFactory.h"

namespace ecs::benchmarks::oop {

    class OOPApplication {
    public:
        using EntityManager = entities::EntityFactory::EntityManager;
        using TimeDelta = float;

        OOPApplication() = default;

        explicit OOPApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}

        ~OOPApplication() = default;

        OOPApplication(const OOPApplication &) = delete;

        OOPApplication &operator=(const OOPApplication &) = delete;

        OOPApplication(OOPApplication &&) = default;

        OOPApplication &operator=(OOPApplication &&) = default;

        inline EntityManager &getEntities() noexcept { return m_entities; }

        void init();

        void uninit();

        void update(TimeDelta dt);

    private:

        entities::EntityFactory m_entity_factory;
        EntityManager m_entities;
        bool m_add_more_complex_system;
    };

}

#endif //ECS_BENCHMARKS_OOP_APPLICATION_H_
