#ifndef ECS_BENCHMARKS_FLECS_APPLICATION_H_
#define ECS_BENCHMARKS_FLECS_APPLICATION_H_

#include "base/Application.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::flecs {
    class FlecsApplication {
    public:
        using EntityManager = ::flecs::world;
        using TimeDelta = float;

        FlecsApplication() = default;

        explicit FlecsApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}

        ~FlecsApplication() = default;

        FlecsApplication(const FlecsApplication &) = delete;

        FlecsApplication &operator=(const FlecsApplication &) = delete;

        FlecsApplication(FlecsApplication &&) = default;

        FlecsApplication &operator=(FlecsApplication &&) = default;

        [[nodiscard]] inline EntityManager &getEntities() { return m_world; }

        [[nodiscard]] inline const EntityManager &getEntities() const { return m_world; }


        void init() {
            m_world.system<ecs::benchmarks::base::components::PositionComponent, const ecs::benchmarks::base::components::DirectionComponent>()
                    .each(systems::MovementSystem::update);
            m_world.system<ecs::benchmarks::base::components::DataComponent>()
                    .each(systems::DataSystem::update);
            if (m_add_more_complex_system) {
                m_world.system<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::DataComponent>()
                        .each(systems::MoreComplexSystem::update);
            }
        }

        void uninit() {
            /// @TODO: remove system for better clean up
        }

        void update(TimeDelta dt) {
            m_world.progress(dt);
        }

    private:
        bool m_add_more_complex_system{false};
        EntityManager m_world;
    };
}

#endif //ECS_BENCHMARKS_FLECS_APPLICATION_H_
