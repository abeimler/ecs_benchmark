#ifndef ECS_BENCHMARKS_ENTITASPP_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTITASPP_ENTITYFACTORY_H_

#include <memory>
#include <functional>

#include <EntitasPP/Entity.hpp>
#include <EntitasPP/Pool.hpp>

#include "base/entities/EntityFactory.h"
#include "EntitasPP/components/PositionComponent.h"
#include "EntitasPP/components/DirectionComponent.h"
#include "EntitasPP/components/DataComponent.h"

namespace ecs::benchmarks::EntitasPP::entities {

    class EntityFactory {
    public:
        using EntityManager = ::EntitasPP::Pool;
        using Entity = ::EntitasPP::EntityPtr;

        static Entity create(EntityManager &pool);

        static void createBulk(EntityManager &pool, std::vector<Entity> &out);

        static Entity createMinimal(EntityManager &pool);

        static void createMinimalBulk(EntityManager &pool, std::vector<Entity> &out);

        static void destroy(EntityManager &pool, Entity entity);

        static void destroyBulk(EntityManager &pool, std::vector<Entity> &in);

        static void clear(EntityManager &pool);


        [[nodiscard]] static inline auto getComponentOne(EntityManager &/*pool*/, Entity entity) {
            return entity->Add<components::PositionComponent>();
        }

        [[nodiscard]] static inline auto getComponentTwo(EntityManager &/*pool*/, Entity entity) {
            return entity->Add<components::DirectionComponent>();
        }

        [[nodiscard]] static inline auto getOptionalComponentThree(EntityManager &/*pool*/, Entity entity) {
            return entity->Add<components::DataComponent>();
        }

        static inline auto removeComponentOne(EntityManager& /*pool*/, Entity entity) {
            return entity->Remove<components::PositionComponent>();
        }
        static inline auto addComponentOne(EntityManager& /*pool*/, Entity entity) {
            return entity->Add<components::PositionComponent>();
        }
    };

}

#endif