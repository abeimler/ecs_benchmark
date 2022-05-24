#include "OOPApplication.h"

namespace ecs::benchmarks::oop {

    void OOPApplication::init() {
        m_systems_mo.emplace_back(createMovementMOSystem());
        m_systems_mdo.emplace_back(createMovementMDOSystem());
        m_systems_mdo.emplace_back(createComflabSystem());
        if (m_add_more_complex_system) {
            m_systems_mdo.emplace_back(createMoreComplexSystem());
        }
    }

    void OOPApplication::uninit() {
        m_systems_mdo.clear();
        m_systems_mo.clear();
    }

    void OOPApplication::update(TimeDelta dt) {
        for (auto &system: this->m_systems_mo) {
            if (system != nullptr) {
                system->update(m_entities_mo, dt);
            }
        }
        for (auto &system: this->m_systems_mdo) {
            if (system != nullptr) {
                system->update(m_entities_mdo, dt);
            }
        }
    }
}