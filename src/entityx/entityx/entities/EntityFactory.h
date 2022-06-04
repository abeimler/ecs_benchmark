#ifndef ECS_BENCHMARKS_ENTITYX_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTITYX_ENTITYFACTORY_H_

#include <entityx/entityx.h>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityx::entities {

    class EntityFactory {
    public:
        using EntityManager = ::entityx::EntityManager;
        using Entity = ::entityx::Entity;

        static Entity create(EntityManager &registry);

        static void createBulk(EntityManager &registry, std::vector<Entity> &out);

        static Entity createMinimal(EntityManager &registry);

        static void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        static void destroy(EntityManager &registry, Entity entity);

        static void destroyBulk(EntityManager &registry, std::vector<Entity> &in);

        static void clear(EntityManager &registry);


        [[nodiscard]] static inline auto getComponentOneConst(EntityManager &entities, Entity entity) {
            return entities.component<const ecs::benchmarks::base::components::PositionComponent>(entity.id());
        }
        [[nodiscard]] static inline auto getComponentTwoConst(EntityManager &entities, Entity entity) {
            return entities.component<const ecs::benchmarks::base::components::DirectionComponent>(entity.id());
        }

        [[nodiscard]] static inline auto getComponentOne(EntityManager &entities, Entity entity) {
            return entities.component<ecs::benchmarks::base::components::PositionComponent>(entity.id());
        }

        [[nodiscard]] static inline auto getComponentTwo(EntityManager &entities, Entity entity) {
            return entities.component<ecs::benchmarks::base::components::DirectionComponent>(entity.id());
        }

        [[nodiscard]] static inline auto getOptionalComponentThree(EntityManager &entities, Entity entity) {
            return entities.component<ecs::benchmarks::base::components::DataComponent>(entity.id());
        }

        static inline void removeComponentOne(EntityManager& /*entities*/, Entity entity) {
          entity.remove<ecs::benchmarks::base::components::PositionComponent>();
        }
        static inline auto addComponentOne(EntityManager& /*entities*/, Entity entity) {
          return entity.assign<ecs::benchmarks::base::components::PositionComponent>();
        }
    };

}

#endif