#include "DataSystem.h"
#include "EntitasPP/components/DataComponent.h"

namespace ecs::benchmarks::EntitasPP::systems {

    void DataSystem::Execute() {
        constexpr auto dt = 1.0F / 60.0F;
        for (auto &e : m_group.lock()->GetEntities()) {
            auto *data = e->Get<EntitasPP::components::DataComponent>();
            updateData(*data, dt);
        }
    }

    void DataSystem::update(EntityManager &/*entities*/, TimeDelta dt) {
        for (auto &e : m_group.lock()->GetEntities()) {
            auto *data = e->Get<EntitasPP::components::DataComponent>();
            updateData(*data, dt);
        }
    }

}