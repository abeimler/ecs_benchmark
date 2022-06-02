#include "MoreComplexSystem.h"
#include "EntitasPP/components/PositionComponent.h"
#include "EntitasPP/components/DirectionComponent.h"
#include "EntitasPP/components/DataComponent.h"

namespace ecs::benchmarks::EntitasPP::systems {

    void MoreComplexSystem::Execute() {
        constexpr auto dt = 1.0F / 60.0F;
        for (auto &e : m_group.lock()->GetEntities()) {
            auto *position = e->Get<EntitasPP::components::PositionComponent>();
            auto *direction = e->Get<EntitasPP::components::DirectionComponent>();
            auto *data = e->Get<EntitasPP::components::DataComponent>();
            updateComponents(*position, *direction, *data, dt);
        }
    }

    void MoreComplexSystem::update(EntityManager &/*entities*/, TimeDelta dt) {
        for (auto &e : m_group.lock()->GetEntities()) {
            auto *position = e->Get<EntitasPP::components::PositionComponent>();
            auto *direction = e->Get<EntitasPP::components::DirectionComponent>();
            auto *data = e->Get<EntitasPP::components::DataComponent>();
            updateComponents(*position, *direction, *data, dt);
        }
    }

}