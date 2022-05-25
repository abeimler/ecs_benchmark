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

        static EntityMDO create(EntityManagerMDO &registry);

        static void createBulk(EntityManagerMDO &registry, std::vector<EntityMDO> &out);

        static EntityMO createMinimal(EntityManagerMO &registry);

        static void createMinimalBulk(EntityManagerMO &registry, std::vector<EntityMO> &out);

        static void destroy(EntityManagerMO &registry, EntityMO entity);

        static void destroyBulk(EntityManagerMO &registry, std::vector<EntityMO> &in);

        static void destroy(EntityManagerMDO &registry, EntityMDO entity);

        static void destroyBulk(EntityManagerMDO &registry, std::vector<EntityMDO> &in);

        static void clear(EntityManagerMO &registry);

        static void clear(EntityManagerMDO &registry);


        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManagerMO &/*registry*/,
                        MovableObject &entity) {
            return entity.position();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManagerMO &/*registry*/,
                        MovableObject &entity) {
            return entity.direction();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManagerMDO &/*registry*/, MovableWithDataObject &entity) {
            return &entity.data();
        }
    };

}

#endif