#ifndef ECS_BENCHMARKS_ENTT_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTT_ENTITYFACTORY_H_

#include "entt/entt.h"

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::entities {

    class EntityFactory {
    public:
        using EntityManager = ::entt::registry;
        using Entity = ::entt::registry::entity_type;

        static Entity createEmpty(EntityManager &registry);
        static void createEmptyBulk(EntityManager &registry, std::vector<Entity> &out);

        static Entity createSingle(EntityManager &registry);
        static void createSingleBulk(EntityManager &registry, std::vector<Entity> &out);

        static Entity create(EntityManager &registry);
        static void createBulk(EntityManager &registry, std::vector<Entity> &out);

        static Entity createMinimal(EntityManager &registry);
        static void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        static void destroy(EntityManager &registry, Entity entity);
        static void destroyBulk(EntityManager &registry, std::vector<Entity> &entities);


        [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &registry, Entity entity) {
            return registry.get<const ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwoConst(EntityManager &registry, Entity entity) {
            return registry.get<const ecs::benchmarks::base::components::VelocityComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity) {
            return registry.get<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwo(EntityManager &registry, Entity entity) {
            return registry.get<ecs::benchmarks::base::components::VelocityComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity) {
            return registry.try_get<ecs::benchmarks::base::components::DataComponent>(entity);
        }


        static inline auto removeComponentOne(EntityManager &registry, Entity entity) {
            return registry.remove<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        static inline auto removeComponentTwo(EntityManager &registry, Entity entity) {
            return registry.remove<ecs::benchmarks::base::components::VelocityComponent>(entity);
        }

        static inline auto removeComponentThree(EntityManager &registry, Entity entity) {
            return registry.remove<ecs::benchmarks::base::components::DataComponent>(entity);
        }

        static inline auto &addComponentOne(EntityManager &registry, Entity entity) {
            return registry.emplace<ecs::benchmarks::base::components::PositionComponent>(entity);
        }
    };

}

#endif