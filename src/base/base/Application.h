#ifndef ECS_BENCHMARKS_BASE_APPLICATION_H_
#define ECS_BENCHMARKS_BASE_APPLICATION_H_

#include <vector>
#include <memory>

#include "systems/System.h"

namespace ecs::benchmarks::base {

    template<class tEntityManager, typename tTimeDelta, class MovementSystem, class DataSystem, class MoreComplexSystem>
    class Application {
    public:
        using EntityManager = tEntityManager;
        using TimeDelta = tTimeDelta;

        Application() = default;

        explicit Application(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}

        virtual ~Application() = default;

        Application(const Application &) = delete;

        Application &operator=(const Application &) = delete;

        Application(Application &&) noexcept = default;

        Application &operator=(Application &&) noexcept = default;

        inline EntityManager &getEntities() noexcept { return m_entities; }

        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
        createMovementSystem(EntityManager &/*entities*/) {
            return std::make_unique<MovementSystem>();
        }

        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
        createDataSystem(EntityManager &/*entities*/) {
            return std::make_unique<DataSystem>();
        }

        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>
        createMoreComplexSystem(EntityManager &/*entities*/) {
            return std::make_unique<MoreComplexSystem>();
        }

        virtual void init() {
            m_systems.emplace_back(createMovementSystem(m_entities));
            m_systems.emplace_back(createDataSystem(m_entities));
            if (m_add_more_complex_system) {
                m_systems.emplace_back(createMoreComplexSystem(m_entities));
            }
        }

        virtual void uninit() {
            m_systems.clear();
        }

        void update(TimeDelta dt) {
            for (auto &system: m_systems) {
                if (system != nullptr) {
                    system->update(m_entities, dt);
                }
            }
        }

    protected:
        EntityManager m_entities;
        std::vector<std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManager, TimeDelta>>> m_systems;
        bool m_add_more_complex_system{false};
    };
}

#endif