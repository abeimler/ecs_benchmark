#ifndef ECS_BENCHMARKS_ENTITYPLUS_APPLICATION_H_
#define ECS_BENCHMARKS_ENTITYPLUS_APPLICATION_H_

#include <entityplus/entity.h>

#include "base/Application.h"
#include "entityplus/entities/EntityFactory.h"

#include "systems/DataSystem.h"
#include "systems/MoreComplexSystem.h"
#include "systems/MovementSystem.h"

namespace ecs::benchmarks::entityplus {

    class EntityPlusApplication final
            : public ecs::benchmarks::base::Application<entityplus::entities::EntityFactory::EntityManager, float, systems::MovementSystem, systems::DataSystem, systems::MoreComplexSystem> {
    public:
        EntityPlusApplication() = default;

        explicit EntityPlusApplication(bool add_more_complex_system) : Application(add_more_complex_system) {}

        ~EntityPlusApplication() = default;

        EntityPlusApplication(const EntityPlusApplication &) = delete;

        EntityPlusApplication &operator=(const EntityPlusApplication &) = delete;

        EntityPlusApplication(EntityPlusApplication &&) = default;

        EntityPlusApplication &operator=(EntityPlusApplication &&) = default;
    };
}

#endif //ECS_BENCHMARKS_ENTITYPLUS_APPLICATION_H_
