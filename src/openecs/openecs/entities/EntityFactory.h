#ifndef ECS_BENCHMARKS_OPENECS_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_OPENECS_ENTITYFACTORY_H_

#include <ecs.h>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::openecs::entities {

    class EntityFactory {
    public:
        using EntityManager = ::ecs::EntityManager;
        using Entity = ::ecs::Entity;

        auto create(EntityManager &entities) {
            return entities.create_with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::DataComponent>();
        }

        void createBulk(EntityManager &entities, std::vector<Entity> &out);

        auto createMinimal(EntityManager &entities) {
            return entities.create_with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent>();
        }

        void createMinimalBulk(EntityManager &entities, std::vector<Entity> &out);

        void destory(EntityManager &entities, Entity entity);

        void destoryBulk(EntityManager &entities, std::vector<Entity> &in);

        void clear(EntityManager &entities);


        inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &/*entities*/, Entity entity) {
            return entity.get<ecs::benchmarks::base::components::PositionComponent>();
        }

        inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManager &/*entities*/, Entity entity) {
            return entity.get<ecs::benchmarks::base::components::DirectionComponent>();
        }

        inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &/*entities*/, Entity entity) {
            return entity.has<ecs::benchmarks::base::components::DataComponent>()
                   ? &entity.get<ecs::benchmarks::base::components::DataComponent>() : nullptr;
        }
    };

}

#endif