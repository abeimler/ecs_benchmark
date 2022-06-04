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

        static auto create(EntityManager &entities) {
            return entities.create_with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent, ecs::benchmarks::base::components::DataComponent>();
        }

        static void createBulk(EntityManager &entities, std::vector<Entity> &out);

        static auto createMinimal(EntityManager &entities) {
            return entities.create_with<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::DirectionComponent>();
        }

        static void createMinimalBulk(EntityManager &entities, std::vector<Entity> &out);

        static void destroy(EntityManager &entities, Entity entity);

        static void destroyBulk(EntityManager &entities, std::vector<Entity> &in);

        static void clear(EntityManager &entities);


        [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &/*entities*/, Entity entity) {
            return std::as_const(entity).get<ecs::benchmarks::base::components::PositionComponent>();
        }
        [[nodiscard]] static inline const ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwoConst(EntityManager &/*entities*/, Entity entity) {
            return std::as_const(entity).get<ecs::benchmarks::base::components::DirectionComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &/*entities*/, Entity entity) {
            return entity.get<ecs::benchmarks::base::components::PositionComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManager &/*entities*/, Entity entity) {
            return entity.get<ecs::benchmarks::base::components::DirectionComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &/*entities*/, Entity entity) {
            return entity.has<ecs::benchmarks::base::components::DataComponent>()
                   ? &entity.get<ecs::benchmarks::base::components::DataComponent>() : nullptr;
        }

        static inline void removeComponentOne(EntityManager& /*entities*/, Entity entity) {
          entity.remove<ecs::benchmarks::base::components::PositionComponent>();
        }
        static inline auto& addComponentOne(EntityManager& /*entities*/, Entity entity) {
          return entity.add<ecs::benchmarks::base::components::PositionComponent>();
        }
    };

}

#endif