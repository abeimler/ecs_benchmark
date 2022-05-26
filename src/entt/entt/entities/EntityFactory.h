#ifndef ECS_BENCHMARKS_ENTT_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTT_ENTITYFACTORY_H_

#include <entt/entt.hpp>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entt::entities {

    class EntityFactory {
    public:
        using EntityManager = ::entt::registry;
        using Entity = ::entt::registry::entity_type;

        static Entity create(EntityManager &registry);

        static void createBulk(EntityManager &registry, std::vector<Entity> &out);

        static Entity createMinimal(EntityManager &registry);

        static void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        static void destroy(EntityManager &registry, Entity entity);

        static void destroyBulk(EntityManager &registry, std::vector<Entity> &in);

        static void clear(EntityManager &registry);


        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity) {
            return registry.get<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManager &registry, Entity entity) {
            return registry.get<ecs::benchmarks::base::components::DirectionComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity) {
            return registry.try_get<ecs::benchmarks::base::components::DataComponent>(entity);
        }
    };

}

#endif