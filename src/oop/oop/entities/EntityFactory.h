#ifndef ECS_BENCHMARKS_OOP_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_OOP_ENTITYFACTORY_H_

#include <vector>
#include <memory>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"
#include "GameObject.h"
#include "MovableObject.h"
#include "MovableDataObject.h"

namespace ecs::benchmarks::oop::entities {

    class EntityFactory {
    public:
        using EntityManager = std::vector<std::unique_ptr<GameObject>>;
        using Entity = GameObject *;

        bool add_more_complex_system{false};

        Entity create(EntityManager &registry);

        void createBulk(EntityManager &registry, std::vector<Entity> &out);

        Entity createMinimal(EntityManager &registry);

        void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        void destroy(EntityManager &registry, Entity entity);

        void destroyBulk(EntityManager &registry, std::vector<Entity> &in);

        void clear(EntityManager &registry);


        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &/*registry*/,
                        MovableObject &entity) {
            return entity.position();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwo(EntityManager &/*registry*/,
                        MovableObject &entity) {
            return entity.velocity();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &/*registry*/, MovableDataObject &entity) {
            return &entity.data();
        }

    };

}

#endif