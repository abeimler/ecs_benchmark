#ifndef ECS_BENCHMARKS_MUSTACHE_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_MUSTACHE_ENTITYFACTORY_H_

#include <mustache/ecs/ecs.hpp>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/ComflabulationComponent.h"

namespace ecs::benchmarks::mustache::entities {

    class EntityFactory {
    public:
        using EntityManager = ::mustache::EntityManager;
        using Entity = ::mustache::Entity;

        Entity create(EntityManager &registry);

        void createBulk(EntityManager &registry, std::vector<Entity> &out);

        Entity createMinimal(EntityManager &registry);

        void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        void destory(EntityManager &registry, Entity entity);

        void destoryBulk(EntityManager &registry, std::vector<Entity> &in);

        void clear(EntityManager &registry);


        inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity) {
            return *registry.getComponent<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManager &registry, Entity entity) {
            return *registry.getComponent<ecs::benchmarks::base::components::DirectionComponent>(entity);
        }

        inline ecs::benchmarks::base::components::ComflabulationComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity) {
            return registry.getComponent<ecs::benchmarks::base::components::ComflabulationComponent>(entity);
        }
    };

}

#endif