#ifndef ECS_BENCHMARKS_ENTITYX_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTITYX_ENTITYFACTORY_H_

#include <entityx/entityx.h>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::entityx::entities {

    class EntityFactory {
    public:
        using EntityManager = ::entityx::EntityManager;
        using Entity = ::entityx::Entity;

        Entity create(EntityManager &registry);

        void createBulk(EntityManager &registry, std::vector<Entity> &out);

        Entity createMinimal(EntityManager &registry);

        void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        void destory(EntityManager &registry, Entity entity);

        void destoryBulk(EntityManager &registry, std::vector<Entity> &in);

        void clear(EntityManager &registry);


        inline auto getComponentOne(EntityManager &entities, Entity entity) {
            return entities.component<ecs::benchmarks::base::components::PositionComponent>(entity.id());
        }

        inline auto getComponentTwo(EntityManager &entities, Entity entity) {
            return entities.component<ecs::benchmarks::base::components::DirectionComponent>(entity.id());
        }

        inline auto getOptionalComponentThree(EntityManager &entities, Entity entity) {
            return entities.component<ecs::benchmarks::base::components::ComflabulationComponent>(entity.id());
        }
    };

}

#endif