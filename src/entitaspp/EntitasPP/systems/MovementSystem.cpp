#include "MovementSystem.h"
#include "EntitasPP/components/PositionComponent.h"
#include "EntitasPP/components/DirectionComponent.h"

namespace ecs::benchmarks::EntitasPP::systems {

    void MovementSystem::Execute() {
        constexpr auto dt = 1.0F / 60.0F;
        for (auto &e : m_group.lock()->GetEntities()) {
            auto *position = e->Get<EntitasPP::components::PositionComponent>();
            auto *direction = e->Get<EntitasPP::components::DirectionComponent>();
            updatePosition(*position, *direction, dt);
        }
    }

    void MovementSystem::update(EntityManager &/*entities*/, TimeDelta dt) {
        for (auto &e : m_group.lock()->GetEntities()) {
            auto *position = e->Get<EntitasPP::components::PositionComponent>();
            auto *direction = e->Get<EntitasPP::components::DirectionComponent>();
            updatePosition(*position, *direction, dt);
        }
    }

}