#ifndef ECS_BENCHMARKS_ENTITASPP_APPLICATION_H_
#define ECS_BENCHMARKS_ENTITASPP_APPLICATION_H_

#include <EntitasPP/Pool.hpp>
#include <EntitasPP/SystemContainer.hpp>

#include "base/Application.h"

namespace ecs::benchmarks::EntitasPP {

    class EntitasPPApplication {
    public:
        using EntityManager = ::EntitasPP::Pool;
        using TimeDelta = float;

        EntitasPPApplication() = default;

        explicit EntitasPPApplication(bool add_more_complex_system) : m_add_more_complex_system(
                add_more_complex_system) {}

        inline EntityManager &getEntities() { return this->m_pool; }

        inline const EntityManager &getEntities() const { return this->m_pool; }

        void init();

        void uninit();

        void update(TimeDelta dt);

    private:
        bool m_add_more_complex_system{false};
        ::EntitasPP::Pool m_pool;
        ::EntitasPP::SystemContainer m_systems;
    };

}

#endif //ECS_BENCHMARKS_ENTITASPP_APPLICATION_H_
