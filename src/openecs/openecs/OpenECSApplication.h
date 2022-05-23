#ifndef ECS_BENCHMARKS_OPENECS_APPLICATION_H_
#define ECS_BENCHMARKS_OPENECS_APPLICATION_H_

#include <ecs.h>

#include "base/Application.h"

#include "systems/ComflabSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::openecs {
    class OpenECSApplication {
    public:
        using EntityManager = ::ecs::EntityManager;
        using TimeDelta = float;

        OpenECSApplication() : m_systems(m_entities) {};
        explicit OpenECSApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system), m_systems(m_entities)  {}
        ~OpenECSApplication() = default;
        OpenECSApplication(const OpenECSApplication &) = delete;
        OpenECSApplication &operator=(const OpenECSApplication &) = delete;
        OpenECSApplication(OpenECSApplication &&) = default;
        OpenECSApplication &operator=(OpenECSApplication &&) = default;

        inline EntityManager &getEntities() { return m_entities; }
        inline const EntityManager &getEntities() const { return m_entities; }


        void init() {
            m_systems.add<systems::MovementSystem>();
            m_systems.add<systems::ComflabSystem>();
            if (m_add_more_complex_system) {
                m_systems.add<systems::MoreComplexSystem>();
            }
        }

        void uninit() {
            if (m_add_more_complex_system) {
                m_systems.remove<systems::MoreComplexSystem>();
            }
            m_systems.remove<systems::ComflabSystem>();
            m_systems.remove<systems::MovementSystem>();
        }

        void update(TimeDelta dt) {
            m_systems.update(dt);
        }
    private:
        bool m_add_more_complex_system;
        EntityManager m_entities;
        SystemManager m_systems;
    };
}

#endif //ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_
