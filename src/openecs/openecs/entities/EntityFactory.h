#ifndef ECS_BENCHMARKS_OPENECS_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_OPENECS_ENTITYFACTORY_H_

#include <ecs.h>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::openecs::entities {

    struct FullEntity final : public ::ecs::EntityAlias<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent> {
        FullEntity() {
            add<ecs::benchmarks::base::components::PositionComponent>();
            add<ecs::benchmarks::base::components::VelocityComponent>();
            add<ecs::benchmarks::base::components::DataComponent>();
        }
    };
    struct MinimalEntity final : public ::ecs::EntityAlias<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent> {
        MinimalEntity() {
            add<ecs::benchmarks::base::components::PositionComponent>();
            add<ecs::benchmarks::base::components::VelocityComponent>();
        }
    };
    struct SingleEntity final : public ::ecs::EntityAlias<ecs::benchmarks::base::components::PositionComponent> {
        SingleEntity() {
            add<ecs::benchmarks::base::components::PositionComponent>();
        }
    };


    class EntityFactory {
    public:
        using EntityManager = ::ecs::EntityManager;
        using Entity = ::ecs::Entity;

        static auto create(EntityManager &entities) {
            return entities.create<FullEntity>();
        }
        static void createBulk(EntityManager &entities, size_t nentities) {
            entities.create(nentities, [](Entity entity) {
                entity.add<ecs::benchmarks::base::components::PositionComponent>();
                entity.add<ecs::benchmarks::base::components::VelocityComponent>();
                entity.add<ecs::benchmarks::base::components::DataComponent>();
            });
        }
        static auto createMinimal(EntityManager &entities) {
            return entities.create<MinimalEntity>();
        }
        static void createMinimalBulk(EntityManager &entities, size_t nentities) {
            entities.create(nentities, [](Entity entity) {
                entity.add<ecs::benchmarks::base::components::PositionComponent>();
                entity.add<ecs::benchmarks::base::components::VelocityComponent>();
            });
        }
        static auto createEmpty(EntityManager &entities) {
            return entities.create();
        }
        static void createEmptyBulk(EntityManager &entities, size_t nentities) {
            entities.create(nentities);
        }
        static auto createSingle(EntityManager &entities) {
            return entities.create<SingleEntity>();
        }
        static void createSingleBulk(EntityManager &entities, size_t nentities) {
            entities.create(nentities, [](Entity entity) {
                entity.add<ecs::benchmarks::base::components::PositionComponent>();
            });
        }

        static void destroy(EntityManager &entities, Entity entity);


        // get component as const not supported ?
        [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &/*entities*/, Entity& entity) {
            return entity.get<ecs::benchmarks::base::components::PositionComponent>();
        }

        [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwoConst(EntityManager &/*entities*/, Entity& entity) {
            return entity.get<ecs::benchmarks::base::components::VelocityComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &/*entities*/, Entity& entity) {
            return entity.get<ecs::benchmarks::base::components::PositionComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwo(EntityManager &/*entities*/, Entity& entity) {
            return entity.get<ecs::benchmarks::base::components::VelocityComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &/*entities*/, Entity& entity) {
            return entity.has<ecs::benchmarks::base::components::DataComponent>()
                   ? &entity.get<ecs::benchmarks::base::components::DataComponent>() : nullptr;
        }

        static inline void removeComponentOne(EntityManager & /*entities*/, Entity& entity) {
            entity.remove<ecs::benchmarks::base::components::PositionComponent>();
        }

        static inline void removeComponentTwo(EntityManager & /*entities*/, Entity& entity) {
            entity.remove<ecs::benchmarks::base::components::VelocityComponent>();
        }

        static inline void removeComponentThree(EntityManager & /*entities*/, Entity entity) {
            entity.remove<ecs::benchmarks::base::components::DataComponent>();
        }

        static inline auto &addComponentOne(EntityManager & /*entities*/, Entity entity) {
            return entity.add<ecs::benchmarks::base::components::PositionComponent>();
        }
        static inline auto& addComponentTwo(EntityManager& /*entities*/, Entity entity) {
          return entity.add<ecs::benchmarks::base::components::VelocityComponent>();
        }
        static inline auto& addComponentThree(EntityManager& /*entities*/, Entity entity) {
          return entity.add<ecs::benchmarks::base::components::DataComponent>();
        }
    };

}

#endif