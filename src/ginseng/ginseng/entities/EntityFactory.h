#ifndef ECS_BENCHMARKS_GINSENG_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_GINSENG_ENTITYFACTORY_H_

#include <ginseng/ginseng.hpp>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::ginseng::entities {

    class EntityFactory {
    public:
        using EntityManager = ::ginseng::database;
        using Entity = ::ginseng::database::ent_id;
        using Component = ::ginseng::database::com_id;

        Entity create(EntityManager &registry);

        void createBulk(EntityManager &registry, std::vector<Entity> &out);

        Entity createMinimal(EntityManager &registry);

        void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        void destory(EntityManager &registry, Entity entity);

        void destoryBulk(EntityManager &registry, std::vector<Entity> &in);

        void clear(EntityManager &registry);


        inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::DirectionComponent>(entity);
        }

        inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::DataComponent *>(entity);
        }
    };

}

#endif