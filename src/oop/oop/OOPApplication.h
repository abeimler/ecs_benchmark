#ifndef ECS_BENCHMARKS_OOP_APPLICATION_H_
#define ECS_BENCHMARKS_OOP_APPLICATION_H_

#include "base/Application.h"

#include "entities/EntityFactory.h"
#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::oop {

    class OOPApplication {
    public:
        using EntityManagerMO = entities::EntityFactory::EntityManagerMO;
        using EntityManagerMDO = entities::EntityFactory::EntityManagerMDO;
        using TimeDelta = float;

        OOPApplication() = default;

        explicit OOPApplication(bool add_more_complex_system) : m_add_more_complex_system(add_more_complex_system) {}

        ~OOPApplication() = default;

        OOPApplication(const OOPApplication &) = delete;

        OOPApplication &operator=(const OOPApplication &) = delete;

        OOPApplication(OOPApplication &&) = default;

        OOPApplication &operator=(OOPApplication &&) = default;

        inline EntityManagerMO &getMOEntities() noexcept { return m_entities_mo; }

        inline EntityManagerMDO &getMDOEntities() noexcept { return m_entities_mdo; }

        void init();

        void uninit();

        void update(TimeDelta dt);

    private:
        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManagerMO, TimeDelta>> createMovementMOSystem() {
            return std::make_unique<systems::MovementMOSystem>();
        }

        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManagerMDO, TimeDelta>> createMovementMDOSystem() {
            return std::make_unique<systems::MovementMDOSystem>();
        }

        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManagerMDO, TimeDelta>> createDataSystem() {
            return std::make_unique<systems::DataSystem>();
        }

        std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManagerMDO, TimeDelta>> createMoreComplexSystem() {
            return std::make_unique<systems::MoreComplexSystem>();
        }

        EntityManagerMO m_entities_mo;
        EntityManagerMDO m_entities_mdo;
        std::vector<std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManagerMO, TimeDelta>>> m_systems_mo;
        std::vector<std::unique_ptr<ecs::benchmarks::base::systems::System<EntityManagerMDO, TimeDelta>>> m_systems_mdo;
        bool m_add_more_complex_system;
    };

}

#endif //ECS_BENCHMARKS_ENTT_APPLICATION_H_
