#ifndef ECS_BENCHMARKS_OOP_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_OOP_ENTITYFACTORY_H_

#include <vector>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"
#include "MovableObject.h"
#include "MovableWithDataObject.h"

namespace ecs::benchmarks::oop::entities {

    class EntityFactory {
    public:
        using EntityManagerMO = std::vector<MovableObject>;
        using EntityMO = MovableObject *;
        using EntityManagerMDO = std::vector<MovableWithDataObject>;
        using EntityMDO = MovableWithDataObject *;

        EntityMDO create(EntityManagerMDO &registry);

        void createBulk(EntityManagerMDO &registry, std::vector<EntityMDO> &out);

        EntityMO createMinimal(EntityManagerMO &registry);

        void createMinimalBulk(EntityManagerMO &registry, std::vector<EntityMO> &out);

        void destory(EntityManagerMO &registry, EntityMO entity);

        void destoryBulk(EntityManagerMO &registry, std::vector<EntityMO> &in);

        void destory(EntityManagerMDO &registry, EntityMDO entity);

        void destoryBulk(EntityManagerMDO &registry, std::vector<EntityMDO> &in);

        void clear(EntityManagerMO &registry);

        void clear(EntityManagerMDO &registry);


        inline ecs::benchmarks::base::components::PositionComponent &getComponentOne(EntityManagerMO &registry,
                                                                                     MovableObject &entity) {
            return entity.position();
        }

        inline ecs::benchmarks::base::components::DirectionComponent &getComponentTwo(EntityManagerMO &registry,
                                                                                      MovableObject &entity) {
            return entity.direction();
        }

        inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManagerMDO &registry, MovableWithDataObject &entity) {
            return &entity.data();
        }
    };

}

#endif