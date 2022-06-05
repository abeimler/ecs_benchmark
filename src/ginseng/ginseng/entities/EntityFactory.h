#ifndef ECS_BENCHMARKS_GINSENG_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_GINSENG_ENTITYFACTORY_H_

#include <ginseng/ginseng.hpp>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/DirectionComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::ginseng::entities {

    class EntityFactory {
    public:
        using EntityManager = ::ginseng::database;
        using Entity = ::ginseng::database::ent_id;
        using Component = ::ginseng::database::com_id;

        static Entity create(EntityManager &registry);

        static void createBulk(EntityManager &registry, std::vector<Entity> &out);

        static Entity createMinimal(EntityManager &registry);

        static void createMinimalBulk(EntityManager &registry, std::vector<Entity> &out);

        static void destroy(EntityManager &registry, Entity entity);

        static void destroyBulk(EntityManager &registry, std::vector<Entity> &in);

        static void clear(EntityManager &registry);


        /// @FIXME: SIGSEGV (Segmentation fault), can't use const ?
        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::PositionComponent>(entity);
        }
        [[nodiscard]] static inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwoConst(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::DirectionComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::PositionComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DirectionComponent &
        getComponentTwo(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::DirectionComponent>(entity);
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &registry, Entity entity) {
            return registry.get_component<ecs::benchmarks::base::components::DataComponent *>(entity);
        }

        static inline void removeComponentOne(EntityManager& registry, Entity entity) {
            registry.remove_component<ecs::benchmarks::base::components::PositionComponent>(entity);
        }
        static inline auto addComponentOne(EntityManager& registry, Entity entity) {
            return registry.add_component(entity, ecs::benchmarks::base::components::PositionComponent{});
        }
    };

}

#endif