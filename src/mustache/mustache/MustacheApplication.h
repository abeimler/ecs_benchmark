#ifndef ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_
#define ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_

#include <mustache/ecs/ecs.hpp>

#include "base/Application.h"

#include "systems/ComflabSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::mustache {
    class MustacheApplication {
    public:
        using EntityManager = ::mustache::EntityManager;
        using TimeDelta = float;

        MustacheApplication() = default;
        explicit MustacheApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}
        ~MustacheApplication() = default;
        MustacheApplication(const MustacheApplication &) = delete;
        MustacheApplication &operator=(const MustacheApplication &) = delete;
        MustacheApplication(MustacheApplication &&) = default;
        MustacheApplication &operator=(MustacheApplication &&) = default;

        inline EntityManager &getEntities() { return m_world.entities(); }


        void init() {
            m_world.systems().addSystem<systems::MovementSystem>();
            m_world.systems().addSystem<systems::ComflabSystem>();
            if (m_add_more_complex_system) {
                m_world.systems().addSystem<systems::MoreComplexSystem>();
            }
            m_world.init();
        }

        void uninit() {
            /// @FIXME: remove system/uninit, SIGSEGV (Segmentation fault), reorderingSystems
            /*
            if (m_add_more_complex_system) {
                m_world.systems().removeSystem<systems::MoreComplexSystem>();
            }
            m_world.systems().removeSystem<systems::ComflabSystem>();
            m_world.systems().removeSystem<systems::MovementSystem>();
             */
        }

        void update(TimeDelta /*dt*/) {
            m_world.update();
        }
    private:
        bool m_add_more_complex_system;
        ::mustache::World m_world;
    };
}

#endif //ECS_BENCHMARKS_MUSTACHE_APPLICATION_H_
