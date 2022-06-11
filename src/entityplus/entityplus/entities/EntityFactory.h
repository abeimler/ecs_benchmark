#ifndef ECS_BENCHMARKS_ENTITYPLUS_ENTITYFACTORY_H_
#define ECS_BENCHMARKS_ENTITYPLUS_ENTITYFACTORY_H_

#include <entityplus/entity.h>

#include "base/entities/EntityFactory.h"
#include "base/components/PositionComponent.h"
#include "base/components/VelocityComponent.h"
#include "base/components/DataComponent.h"

namespace ecs::benchmarks::entityplus::components {
    struct OneTwo{};
    struct OneTwoThree{};
}

namespace ecs::benchmarks::entityplus::entities {

    class EntityFactory {
    public:
        using CompList = ::entityplus::component_list<ecs::benchmarks::base::components::PositionComponent, ecs::benchmarks::base::components::VelocityComponent, ecs::benchmarks::base::components::DataComponent>;
        using TagList = ::entityplus::tag_list<components::OneTwo, components::OneTwoThree>;
        using EntityManager = ::entityplus::entity_manager<CompList, TagList>;
        using Entity = EntityManager::entity_t;

        static Entity create(EntityManager &entityManager);

        static void createBulk(EntityManager &entityManager, std::vector<Entity> &out);

        static Entity createMinimal(EntityManager &entityManager);

        static void createMinimalBulk(EntityManager &entityManager, std::vector<Entity> &out);

        static void destroy(EntityManager &entityManager, Entity entity);

        static void destroyBulk(EntityManager &entityManager, std::vector<Entity> &in);

        static void clear(EntityManager &entityManager);


        [[nodiscard]] static inline const ecs::benchmarks::base::components::PositionComponent &
        getComponentOneConst(EntityManager &/*entityManager*/, Entity entity) {
            /// @NOTE: hast not const correctness, https://github.com/Yelnats321/EntityPlus/issues/21
            return entity.get_component<ecs::benchmarks::base::components::PositionComponent>();
        }

        [[nodiscard]] static inline const ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwoConst(EntityManager &/*entityManager*/, Entity entity) {
            return entity.get_component<ecs::benchmarks::base::components::VelocityComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::PositionComponent &
        getComponentOne(EntityManager &/*entityManager*/, Entity entity) {
            return entity.get_component<ecs::benchmarks::base::components::PositionComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::VelocityComponent &
        getComponentTwo(EntityManager &/*entityManager*/, Entity entity) {
            return entity.get_component<ecs::benchmarks::base::components::VelocityComponent>();
        }

        [[nodiscard]] static inline ecs::benchmarks::base::components::DataComponent *
        getOptionalComponentThree(EntityManager &/*entityManager*/, Entity entity) {
            return entity.has_component<ecs::benchmarks::base::components::DataComponent>() ? &entity.get_component<ecs::benchmarks::base::components::DataComponent>() : nullptr;
        }


        static inline auto removeComponentOne(EntityManager &/*entityManager*/, Entity entity) {
            return entity.remove_component<ecs::benchmarks::base::components::PositionComponent>();
        }

        static inline auto removeComponentTwo(EntityManager &/*entityManager*/, Entity entity) {
            return entity.remove_component<ecs::benchmarks::base::components::VelocityComponent>();
        }

        static inline auto removeComponentThree(EntityManager &/*entityManager*/, Entity entity) {
            return entity.remove_component<ecs::benchmarks::base::components::DataComponent>();
        }

        static inline auto addComponentOne(EntityManager &/*entityManager*/, Entity entity) {
            return entity.add_component<ecs::benchmarks::base::components::PositionComponent>();
        }
    };

}

#endif