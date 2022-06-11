#ifndef ECS_BENCHMARKS_MUSTACHE_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_MUSTACHE_ENTITYFACTORY_H_

#include <mustache/ecs/ecs.hpp>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::mustache::entities {

    class EntityFactory {
    public:
        using EntityManager = ::mustache::EntityManager;
        using Entity = ::mustache::Entity;

        Entity create(EntityManager &registry);

        void createBulk(EntityManager &registry, std::vector<Entity> &out);

        Entity createMinimal(EntityManager &registry);

        void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        void destroy(EntityManager &registry, Entity entity);

        void destroyBulk(EntityManager &registry, std::vector<Entity> &in);

        void clear(EntityManager &registry);


        [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &registry, Entity entity) {
            return *registry.getComponent<const ecs::benchmarks::base::components::PositionComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
        }

        [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwoConst(EntityManager &registry, Entity entity) {
            return *registry.getComponent<const ecs::benchmarks::base::components::VelocityComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity) {
            return *registry.getComponent<ecs::benchmarks::base::components::PositionComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwo(EntityManager &registry, Entity entity) {
            return *registry.getComponent<ecs::benchmarks::base::components::VelocityComponent, ::mustache::FunctionSafety::kUnsafe>(
                    entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity) {
            return registry.getComponent<ecs::benchmarks::base::components::DataComponent>(entity);
        }


        static inline void removeComponentOne(EntityManager &entities, Entity entity) {
            entities.removeComponent<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        static inline void removeComponentTwo(EntityManager &entities, Entity entity) {
            entities.removeComponent<ecs::benchmarks::base::components::VelocityComponent>(entity);
        }

        static inline void removeComponentThree(EntityManager &entities, Entity entity) {
            entities.removeComponent<ecs::benchmarks::base::components::DataComponent>(entity);
        }

        static inline auto &addComponentOne(EntityManager &entities, Entity entity) {
            return entities.assign<ecs::benchmarks::base::components::PositionComponent>(entity);
        }
    };

}

#endif