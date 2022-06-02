#include "EntitasPPApplication.h"
#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::EntitasPP {
    void EntitasPPApplication::init() {
        m_systems.Add(m_pool.CreateSystem<systems::MovementSystem>());
        m_systems.Add(m_pool.CreateSystem<systems::DataSystem>());
        if (m_add_more_complex_system) {
            m_systems.Add(m_pool.CreateSystem<systems::MoreComplexSystem>());
        }
        m_systems.Initialize();
    }

    void EntitasPPApplication::uninit() {
        m_pool.ClearGroups();
        m_systems.ClearReactiveSystems();
    }

    void EntitasPPApplication::update(TimeDelta /*dt*/) {
        m_systems.Execute();
    }
}